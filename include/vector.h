#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>

/*! \namespace sc
    \brief namespace to differ from std
*/
namespace sc{

	
	class iterator;	
	
	/*! \class Vector
    	\brief means like std::vector

    	With this class we try to implement our own vector.
	*/
	template< typename T >
	class vector{

		private:
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
			vector( vector& other )
				: m_capacity{other.capacity()}, m_size{other.size()}, arr{new T[m_capacity]}
			{
				for( size_type i{0u} ; i < m_size ; i++ )
					arr[i] = other[i];
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

			void pop_back( );

			void pop_front( );

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

			//bool operator==( const vector& lhs, const vector& rhs );

			//bool operator!=( const vector& lhs, const vector& rhs );
			
			friend class my_iterator;
			
		private:
			size_type m_capacity; //!< capacity of the array (alocated memory).
			size_type m_size; //!< size of the array.
			T * arr; //<! T type array pointer.
			
	}; // class vector
	
	/*! \class my_iterator
		
		With this class we're trying to implement an iterator class for vectors.

	template< typename T >
	class my_iterator{
		public:
			//=== Alias
			typedef size_t size_type; //!< Type of size.
			using iterator = my_iterator< T >;
			using const_iterator = my_iterator < const T >;
			
			//=== Constructor
			my_iterator();

			//=== Destructor
			~my_iterator();

			//=== Methods
			
			iterator begin();
			const_iterator cbegin() const;
			iterator end();
			const_iterator cend() const;

			//=== Operations
			iterator insert ( iterator pos, const T & value );

			template< typename InItr >
			iterator insert( iterator pos, InItr first, InItr last );

			iterator insert( const_iterator pos, std::initializer_list< T > ilist );

			iterator erase( iterator pos );

			iterator erase( iterator first, iterator last );

			void assign( size_type count, const T& value );

			template< typename InItr >
			void assign( InItr first, InItr last );

			void assign( std::initializer_list< T > ilist );

			//=== Const Operations
			const iterator insert( iterator pos, const T & value );

			template< typename InItr >
			const iterator insert( iterator pos, InItr first, InItr last );

			const iterator insert( const_iterator pos, std::initializer_list< T > ilist );

			const iterator erase( iterator pos );

			const iterator erase( iterator first, iterator last );

			void assign( size_type count, const T& value );

			template< typename InItr >
			void assign( InItr first, InItr last );

			void assign( std::initializer_list< T > ilist );

		public:
			//=== Operators
			iterator operator++();
			iterator operator*();
			iterator operator-();
			friend iterator& operator+(int n, iterator it);
			friend iterator operator+(iterator it, int n);
			friend iterator& operator-(int n, iterator it);
			friend iterator operator-(iterator it, int n);
			pointer operator->();
			bool operator==();
			bool operator!=();
	}; // class my_iterator */

} // namespace sc

#endif
