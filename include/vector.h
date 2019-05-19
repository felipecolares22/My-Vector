#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

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
			//=== Operations
			/// Return the size of array.
			size_type size( ) const
			{return this->m_size;}

			void clear( );

			bool empty( );

			void push_front( const T & value );

			void push_back( const T & value );

			void pop_back( );

			void pop_front( );

			const T & back( ) const;

			const T & front( ) const;

			void assign( size_type count, const T & value );

			// Return the object at the index position.
			T & operator[]( size_type pos )
			{return arr[pos];}

			T & at( size_type pos );

			/// Return the capacity of array.
			size_type capacity( ) const
			{return m_capacity;}

			void reserve( size_type new_cap );

			void shrink_to_fit( );			

		public:
			//=== Operators overload

			vector& operator=( vector& other );

			vector& operator=( std::initializer_list<T> ilist );

			//bool operator==( const vector& lhs, const vector& rhs );

			//bool operator!=( const vector& lhs, const vector& rhs );

		private:
			size_type m_capacity; //!< capacity of the array (alocated memory).
			size_type m_size; //!< size of the array.
			T * arr; //<! T type array pointer.
			
	}; // class vector

} // namespace sc

#endif
