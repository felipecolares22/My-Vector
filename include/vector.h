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

			/// Constructor with elements in [first, last) range.
			template< typename InputIt >
			vector( InputIt first, InputIt last )
				: m_capacity{(size_type)(last - first)}, m_size{(size_type)(last - first)}, arr{new T[m_capacity]}
			{
				size_type count{0};
				while(first != last)
					arr[count++] = *(first++);
			}

			/// Copy constructor.
			vector( const vector& other )
				: m_capacity{other.capacity()}, m_size{other.size()}, arr{new T[m_capacity]}
			{
				for( size_type i{0u} ; i < m_size ; i++ )
					arr[i] = other.arr[i];
			}

			/// std::initializer_list copy constructor.
			vector( std::initializer_list<T> ilist )
				: m_capacity{ilist.size()}, m_size{ilist.size()}, arr{new T[m_capacity]}
			{
				size_type count{0};
				for( const T& e : ilist )
					arr[count++] = e;
			}

			/// Destructor.
			~vector( )
			{
				delete arr;
			}

			//=== Iterators
			/// Returns an iterator pointing to the first item in the list
			my_iterator begin()
			{
				my_iterator iter(&arr[0]);
				return iter;
			}

			/// Returns a constant iterator pointing to the first item in the list.
			my_iterator end()
			{
				my_iterator iter(&arr[m_size]);
				return iter;
			}

			/// Returns an iterator pointing to the position just after the last element of the list.
			my_iterator cbegin() const
			{
				my_const_iterator iter(&arr[0]);	
				return iter;
			}

			/// Returns a constant iterator pointing to the position just after the last element of the list.
			my_iterator cend() const
			{
				my_const_iterator iter(&arr[m_size]);
				return iter;	
			}


		public:
			//=== Methods
			/// Returns the size of array.
			size_type size( ) const
			{return this->m_size;}

			/// Delete all array elements.
			void clear( )
			{
				delete arr;

				this->m_size = initial_size;
				this->arr = new T[m_capacity];
			}

			/// Checks if the array is empty.
			bool empty( )
			{return m_size == initial_size;}
			
			/// Adds value to the front of the list.
			void push_front( const T & value )
			{
				if( m_size == m_capacity )
				{
					if( m_capacity != 0 )
						reserve( m_capacity * 2 );
					else
						reserve( 1 );
				}

				vector<T> aux = *this;
				delete arr;

				arr = new T[m_capacity];
				arr[0] = value;
				m_size++;
				for(size_type i{1u} ; i < m_size ; i++ )
					arr[i] = aux.arr[i-1];
			}

			/// Adds value to the end of the list.
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
			
			/// Removes the object at the end of the list.
			void pop_back( )
			{
				m_size--;
			}

			/// Removes the object at the front of the list.
			void pop_front( )
			{
				vector<T> aux = *this;
				delete arr;

				this->m_size--;
				this->arr = new T[m_capacity];

				for( size_type i{0u}; i < m_size; i++ )
				{
					arr[i] = aux[i+1];
				}
			}

			/// Returns the object at the end of the list.
			const T & back( ) const
			{
				return arr[m_size-1];
			}

			/// Returns the object at the beginning of the list.
			const T & front( ) const
			{
				return arr[0];
			}

			/// Replaces the content of the list with count copies of value.
			void assign( size_type count, const T & value )
			{
				if( count > m_capacity ){
					reserve( count );
					this->m_capacity = count;
				}

				delete arr;
				this->m_size = count;
				this->arr = new T[m_capacity];

				for( size_type i{0u} ; i < m_size ; i++ )
					arr[i] = value;
			}

			/// Return the object at the index position.
			T & operator[]( size_type pos )
			{ return arr[pos]; }

			/// Returns the object at the index pos in the array.
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
				for( const T& e : ilist )
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

			//=== Operations
			/// Adds value into the list before pos. Returns an iterator to the position of the inserted item.
			my_iterator insert ( my_iterator pos, const T & value )
			{
				vector<T> aux = *this;
				size_type range_size = 1; 
				size_type posi = pos - arr;
				size_type total_size = (size_type)(m_size + range_size);

				reserve( total_size );

				for( size_type i = m_size ; i >= posi ; i-- )
				{
					arr[i+range_size] = arr[i];
				}
				
				arr[posi] = value;

				m_size = total_size;

				return pos;
			}

			///inserts elements from the range [first; last) before pos.
			template< typename InItr >
			my_iterator insert( my_iterator pos, InItr first, InItr last )
			{
				vector<T> aux = *this;
				size_type range_size = last-first; 
				size_type posi = pos - arr;
				size_type total_size = (size_type)(m_size + range_size);

				reserve( total_size );

				for( size_type i = m_size ; i >= posi ; i-- )
				{
					arr[i+range_size] = arr[i];
				}
				
				while( first != last )
				{
					arr[posi++] = *(first++);
				}

				m_size = total_size;

				return pos;
			}

			/// Inserts elements from the initializer list ilist before pos.
			my_iterator insert( my_iterator pos, std::initializer_list< T > ilist )
			{
				vector<T> aux = *this;
				size_type range_size = ilist.size(); 
				size_type posi = pos - arr;
				size_type total_size = (size_type)(m_size + range_size);

				reserve( total_size );

				for( size_type i = m_size ; i >= posi ; i-- )
				{
					arr[i+range_size] = arr[i];
				}
				
				for( const T& e : ilist )
				{
					arr[posi++] = e;
				}

				m_size = total_size;

				return pos;
			}

			/// Removes the object at position pos. Returns an iterator to the element that follows pos before the call.
			my_iterator erase( my_iterator pos )
			{
				size_type posi = pos - arr;
				for( size_type i{posi} ; i < m_size ; i++ )
				{
					arr[i-1] = arr[i];
				}

				m_size--;

				return my_iterator( &arr[posi-1] );
			}

			/// Removes elements in the range [first; last).
			my_iterator erase( my_iterator first, my_iterator last )
			{
				size_type range_size = last - first;
				size_type posi = first - arr;

				for( size_type i{posi} ; i < m_size - range_size ; i++ )
				{
					arr[i-1] = arr[i-1+range_size];
				}

				return my_iterator( &arr[posi] );
			}

			/// Replaces the contents with count copies of value value.
			template< typename InItr >
			void assign( InItr first, InItr last )
			{
				size_type range_size = last-first;

				if( range_size > m_capacity ){
					reserve( range_size );
					this->m_capacity = range_size;
				}

				delete arr;
				this->m_size = range_size;
				this->arr = new T[m_capacity];

				size_type count{0u};
				while( first != last )
					arr[count++] = *(first++);
			}

			/// Replaces the contents of the list with copies of the elements in the range [first; last).
			void assign( std::initializer_list< T > ilist )
			{
				if( ilist.size() > m_capacity ){
					reserve( ilist.size() );
					this->m_capacity = ilist.size();
				}

				delete arr;
				this->m_size = ilist.size();
				this->arr = new T[m_capacity];

				size_type count{0u};
				for( const T& e : ilist )
					arr[count++] = e;
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

				iterator operator->()
				{
					return iterator( it );
				}

				bool operator==( const iterator& it2) const
				{ return it == it2.it; }

				bool operator!=( const iterator& it2) const
				{ return it != it2.it; }
		}; // class my_iterator
		

		/*! \class my_constiterator
			
			With this class we're trying to implement an constant iterator class for vectors.
		*/


		class my_const_iterator{
			private:
				const T * it; //!< Iterator pointer
				typedef my_const_iterator iterator; 

			public:
				//=== Alias
				typedef size_t size_type; //!< Type of size.
				
				//=== Constructor
				my_const_iterator(T* it)
					:it{it}
				{/*empty*/}

				//=== Destructor
				~my_const_iterator()
				{/*empty*/}

				

			public:
				//=== Operators
				const iterator operator++(void)
				{ return iterator( ++it ); }

				const iterator operator++(int)
				{ 
					iterator temp( it );
					it++;
					return temp;
				}

				const T& operator*()
				{ return *it; }

				const iterator operator--(void)
				{ return iterator( --it ); }

				const iterator operator--(int)
				{
					iterator temp( it );
					it--;
					return temp;
				}

				friend const iterator operator+(int n, iterator it)
				{
					for( int i = 0 ; i < n ; i++ )
						it++;
					return iterator( it );
				}

				friend const iterator operator+(iterator it, int n)
				{
					for( int i = 0 ; i < n ; i++ )
						it++;
					return iterator( it );
				}

				friend const iterator operator-(int n, iterator it)
				{
					for( int i = 0 ; i < n ; i++ )
						it--;
					return iterator( it );
				}

				friend const iterator operator-(iterator it, int n)
				{
					for( int i = 0 ; i < n ; i++ )
						it--;
					return iterator( it );
				}

				friend const size_type operator-(iterator it1, iterator it2)
				{
					return it1.it - it2.it;
				}

				const iterator operator->()
				{
					return iterator( it );
				}
				const bool operator==( const iterator& it2) const
				{ return it == it2.it; }

				const bool operator!=( const iterator& it2) const
				{ return it != it2.it; }
		}; // class my_iterator
		
	}; // class vector

} // namespace sc

#endif
