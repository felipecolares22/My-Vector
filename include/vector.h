#ifndef VECTOR_H
#define VECTOR_H

namespace sc{

	template< typename T >
	class vector {
		public:
			typedef size_t size_type;

		private:
			size_type capacity;
			size_type size;
			T arr;				// I don't know it

		public:
			vector( );
			
			explicit vector( size_type count );

			template< typename InputIt >
			vector( InputIt first, InputIt last );

			vector( const vector& other );

			vector( std::initializer_list<T> ilist );

			~vector( );

			vector& operator=( const vector& other );

			vector& operator=( std::initializer_list<T> ilist );
	}

}

#endif