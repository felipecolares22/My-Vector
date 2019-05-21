#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>

/*! \namespace sc
    \brief namespace to differ from std
*/
namespace sc{

	template< typename T >
	class my_iterator;	
	
	/*! \class Vector
    	\brief means like std::vector

    	With this class we try to implement our own vector.
	*/
	template< typename T >
	class vector{

		protected:
			//=== Alias
			typedef size_t size_type; //!< Type of size.
			static constexpr size_type initial_capacity=1; //!< Default value is 1.
			static constexpr size_type initial_size=0; //!< Default value is 0.

		public:
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
				: m_capacity{(size_type)((last - first) * 2)}, m_size{(size_type)(last - first)}, arr{new T[m_capacity]}
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
				: m_capacity{ilist.size() * 2}, m_size{ilist.size()}, arr{new T[m_capacity]}
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

		public:
			//=== Methods
			/// Return the size of array.
			size_type size( ) const
			{return this->m_size;}

			/// Delete all array elements;
			void clear( )
			{
				delete arr;

				this->m_capacity = initial_capacity;
				this->m_size = initial_size;
				this->arr = new T[m_capacity];
			}

			/// Checks if the array is empty
			bool empty( )
			{return m_size == initial_size;}

			void push_front( const T & value );

			void push_back( const T & value );

			void pop_back( )
			{
				m_size--;
			}

			void pop_front( )
			{
				vector<T> aux = *this;
				delete arr;
				
				this->m_capacity = m_size
				this->arr = new T[m_capacity];
				for( size_type i{0u}; i < (m_size-1); i++ )
				{
					arr[i] = aux[i]
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
			vector& operator=( vector& other )
			{
				if( m_size != initial_size )
					delete arr;

				this->m_capacity = other.capacity();
				this->m_size = other.size();
				this->arr = new T[m_capacity];

				for( size_type i{0u} ; i < m_size ; i++ )
					arr[i] = other[i];

				return other;
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
			T * arr; //<! T type array pointer.
		
		/*! \class my_iterator
			
			With this class we're trying to implement an iterator class for vectors.
		*/
		template < typename iT >
		class my_iterator{
			public:
				//=== Alias
				typedef size_t size_type; //!< Type of size.
				
				//=== Constructor
				my_iterator();

				//=== Destructor
				~my_iterator();

				//=== Methods
				my_iterator< iT > begin()
				{
					return arr;
				}
				my_iterator< iT > end()
				{
					return &arr[m_size];
				}

				//=== Operations
				my_iterator< iT > insert ( my_iterator< iT > pos, const iT & value );

				template< typename InItr >
				my_iterator< iT > insert( my_iterator< iT > pos, InItr first, InItr last );

				my_iterator< iT > insert( my_iterator < const iT > pos, std::initializer_list< iT > ilist );

				my_iterator< iT > erase( my_iterator< iT > pos );

				my_iterator< iT > erase( my_iterator< iT > first, my_iterator< iT > last );

				void assign( size_type count, const iT& value );

				template< typename InItr >
				void assign( InItr first, InItr last );

				void assign( std::initializer_list< iT > ilist );

			public:
				//=== Operators
				// my_iterator< iT > operator++();
				// my_iterator< iT > operator*();
				// my_iterator< iT > operator-();
				// friend my_iterator< iT >& operator+(int n, my_iterator< iT > it);
				// friend my_iterator< iT > operator+(my_iterator< iT > it, int n);
				// friend my_iterator< iT >& operator-(int n, my_iterator< iT > it);
				// friend my_iterator< iT > operator-(my_iterator< iT > it, int n);
				// pointer operator->();
				// bool operator==();
				// bool operator!=();
		}; // class my_iterator
		

		/*! \class my_constiterator
			
			With this class we're trying to implement an constant iterator class for vectors.
		*/
		
		template< typename CiT >
		class my_constiterator{
			public:
				//=== Alias
				typedef size_t size_type; //!< Type of Size

				//=== Constructor
				my_constiterator();

				//=== Destructor
				~my_constiterator();

				//=== Methods
				my_iterator < const CiT > cbegin() const;
				my_iterator < const CiT > cend() const;

				//=== Const Operations
				const my_constiterator< CiT > insert( my_iterator< CiT > pos, const CiT & value );

				template< typename InItr >
				const my_constiterator< CiT > insert( my_iterator< CiT > pos, InItr first, InItr last );

				const my_constiterator< CiT > insert( my_iterator < const CiT > pos, std::initializer_list< CiT > ilist );

				const my_constiterator< CiT > erase( my_iterator< CiT > pos );

				const my_constiterator< CiT > erase( my_iterator< CiT > first, my_iterator< CiT > last );

				void assign( size_type count, const CiT& value );

				template< typename InItr >
				void assign( InItr first, InItr last );

				void assign( std::initializer_list< CiT > ilist );
		}; // class my_constiterator

	}; // class vector


} // namespace sc

#endif
