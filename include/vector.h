#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>

/*! \namespace sc
    \brief namespace to differ from std
*/
namespace sc{
	
	/*! \class Vector
    	\brief means like std::vector

    	With this class we try to implement our own vector.
	*/
	template< typename T >
	class vector{

		protected:
			//=== Alias
			typedef size_t size_type; //!< Type of size.
			static constexpr size_type initial_capacity=0; //!< Default value is 0.
			static constexpr size_type initial_size=0; //!< Default value is 0.

		public:
			class my_iterator;

			//=== Constructors
			/// Default constructor
			vector( )
				: m_capacity{initial_capacity}, m_size{initial_size}, arr{new T[initial_capacity]}
			{/*empty*/}

			/// Constructor with a defined size
			explicit vector( size_type count )
				: m_capacity{count}, m_size{initial_size}, arr{new T[count]}
			{/*empty*/}

			/// First last copy constructor
			template< typename InputIt >
			vector( InputIt first, InputIt last )
				: m_capacity{(size_type)(last - first)}, m_size{(size_type)(last - first)}, arr{new T[m_capacity]}
			{
				size_type count{0};
				while(first != last)
					arr[count++] = *(first++);
			}

			/// Copy constructor
			vector( const vector& other )
				: m_capacity{other.capacity()}, m_size{other.size()}, arr{new T[m_capacity]}
			{
				for( size_type i{0u} ; i < m_size ; i++ )
					arr[i] = other.arr[i];
			}

			/// std::initializer_list copy constructor
			vector( std::initializer_list<T> ilist )
				: m_capacity{ilist.size()}, m_size{ilist.size()}, arr{new T[m_capacity]}
			{
				size_type count{0};
				for( const int& e : ilist )
					arr[count++] = e;
			}

			/// Destructor
			~vector( )
			{
				delete arr;
			}

			//=== Iterators
			my_iterator begin()
			{
				my_iterator iter(&arr[0]);
				return iter;
			}
			my_iterator end()
			{
				my_iterator iter(&arr[m_size]);
				return iter;
			}
			my_iterator cbegin() const;
			my_iterator cend() const;


		public:
			//=== Methods
			/// Return the size of array.
			size_type size( ) const
			{return this->m_size;}

			/// Delete all array elements;
			void clear( )
			{
				delete arr;

				this->m_size = initial_size;
				this->arr = new T[m_capacity];
			}

			/// Checks if the array is empty
			bool empty( )
			{return m_size == initial_size;}

			void push_front( const T & value );

			void push_back( const T & value )
			{
				if( m_size == m_capacity )
				{
					if( m_capacity != 0 )
						reserve( m_capacity * 2 );
					else
						reserve( 1 );
				}

				arr[m_size] = value;
				m_size++;
			}

			void pop_back( )
			{
				m_size--;
			}

			void pop_front( )
			{
				vector<T> aux = *this;
				delete arr;

				this->m_size--;
				this->arr = new T[m_capacity];

				for( size_type i{0u}; i < m_size; i++ )
				{
					arr[i] = aux[i];
				}
			}

			const T & back( ) const;

			const T & front( ) const;

			void assign( size_type count, const T & value );

			/// Return the object at the index position.
			T & operator[]( size_type pos )
			{return arr[pos];}

			T & at( size_type pos )
			{
				if( not (pos < m_size and pos >= 0) )
					throw std::out_of_range("error in at(): out of range");
				else
					return arr[pos];
			}

			/// Return the capacity of array.
			size_type capacity( ) const
			{return m_capacity;}

			/// Realoc the storage to new_cap
			void reserve( size_type new_cap )
			{
				if( new_cap <= m_capacity )
					return;

				vector<T> aux = *this;

				delete arr;
				this->m_capacity = new_cap;
				this->arr = new T[m_capacity];

				for( size_type i{0u} ; i < m_size ; i++ )
					arr[i] = aux[i];
			}

			/// Desaloc unused storage
			void shrink_to_fit( )
			{
				if( m_size == m_capacity )
					return;

				vector<T> aux = *this;
				
				delete arr;
				this->m_capacity = m_size;
				this->arr = new T[m_capacity];

				for( size_type i{0u} ; i < m_size ; i++ )
					arr[i] = aux[i];
			}			

		public:
			//=== Operators overload
			/// Operator= overload for vectors
			vector& operator=( const vector& other )
			{
				if( m_size != initial_size )
					delete arr;

				this->m_capacity = other.capacity();
				this->m_size = other.size();
				this->arr = new T[m_capacity];

				for( size_type i{0u} ; i < m_size ; i++ )
					arr[i] = other.arr[i];

				return *this;
			}

			/// Operator= overload for initializer_list
			vector& operator=( std::initializer_list<T> ilist )
			{
				if( m_size != initial_size )
					delete arr;

				this->m_capacity = ilist.size() * 2;
				this->m_size = ilist.size();
				this->arr = new T[m_capacity];

				size_type count{0};
				for( const int& e : ilist )
					arr[count++] = e;

				return *this;
			}

			/// Operator== overload for vectors comparison
			bool operator==( const vector& rhs )
			{
				if( this->m_size == rhs.size() )
				{
					for(int i=0; i<(int)this->m_size; i++)
					{
						if(this->arr[i] != rhs.arr[i]) return false;
					}
					return true;
				}
				else return false;
			}

			/// Operator!= overload for vectors comparison
			bool operator!=( const vector& rhs )
			{
				if( this->m_size == rhs.size() )
				{
					for(int i=0; i<(int)this->m_size; i++)
					{
						if(this->arr[i] != rhs.arr[i]) return true;
					}
					return false;
				}
				else return true;
			}
			
			
		protected:
			size_type m_capacity; //!< capacity of the array (alocated memory).
			size_type m_size; //!< size of the array.
			T * arr; //!< T type array pointer.
		
		public:
		/*! \class my_iterator
			
			With this class we're trying to implement an iterator class for vectors.
		*/
		class my_iterator{
			private:
				T * it; //!< Iterator pointer
				typedef my_iterator iterator; 

			public:
				//=== Alias
				typedef size_t size_type; //!< Type of size.
				
				//=== Constructor
				my_iterator(T* it)
					:it{it}
				{/*empty*/}

				//=== Destructor
				~my_iterator()
				{/*empty*/}

				//=== Operations
				iterator insert ( iterator pos, const T & value );

				template< typename InItr >
				iterator insert( iterator pos, InItr first, InItr last );

				iterator insert( my_iterator pos, std::initializer_list< T > ilist );

				iterator erase( iterator pos );

				iterator erase( iterator first, iterator last );

				void assign( size_type count, const T& value );

				template< typename InItr >
				void assign( InItr first, InItr last );

				void assign( std::initializer_list< T > ilist );

			public:
				//=== Operators
				iterator operator++(void)
				{ return iterator( ++it ); }

				iterator operator++(int)
				{ 
					iterator temp( it );
					it++;
					return temp;
				}

				T& operator*()
				{ return *it; }

				iterator operator--(void)
				{ return iterator( --it ); }

				iterator operator--(int)
				{
					iterator temp( it );
					it--;
					return temp;
				}

				friend iterator operator+(int n, iterator it)
				{
					for( int i = 0 ; i < n ; i++ )
						it++;
					return iterator( it );
				}

				friend iterator operator+(iterator it, int n)
				{
					for( int i = 0 ; i < n ; i++ )
						it++;
					return iterator( it );
				}

				friend iterator operator-(int n, iterator it)
				{
					for( int i = 0 ; i < n ; i++ )
						it--;
					return iterator( it );
				}

				friend iterator operator-(iterator it, int n)
				{
					for( int i = 0 ; i < n ; i++ )
						it--;
					return iterator( it );
				}

				friend size_type operator-(iterator it1, iterator it2)
				{
					return it1.it - it2.it;
				}

				//operator->();
				bool operator==(iterator& it2)
				{ return it == it2.it; }

				bool operator!=(iterator& it2)
				{ return it != it2.it; }
		}; // class my_iterator
		

		/*! \class my_constiterator
			
			With this class we're trying to implement an constant iterator class for vectors.
		*/
		// class my_constiterator{
		// 	private:
		// 		CiT * it; //!< Constant iterator pointer
		// 		typedef my_constiterator< CiT > const_iterator;

		// 	public:
		// 		//=== Alias
		// 		typedef size_t size_type; //!< Type of Size

		// 		//=== Constructor
		// 		my_constiterator();

		// 		//=== Destructor
		// 		~my_constiterator();

		// 		//=== Const Operations
		// 		const const_iterator insert( const_iterator pos, const CiT & value );

		// 		template< typename InItr >
		// 		const const_iterator insert( const_iterator pos, InItr first, InItr last );

		// 		const const_iterator insert( my_constiterator < const CiT > pos, std::initializer_list< CiT > ilist );

		// 		const const_iterator erase( const_iterator pos );

		// 		const const_iterator erase( const_iterator first, const_iterator last );

		// 		void assign( size_type count, const CiT& value );

		// 		template< typename InItr >
		// 		void assign( InItr first, InItr last );

		// 		void assign( std::initializer_list< CiT > ilist );
		// }; // class my_constiterator

	}; // class vector


} // namespace sc

#endif
