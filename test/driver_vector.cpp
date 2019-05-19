#include <iostream>
#include <array>
#include <iterator>

#include "vector.h"

using namespace sc;

int main(){
	std::cout << ">>> STARTING SC::VECTOR TESTS\n\n";
	/*******************************************
								  STARTING TESTS								
	*******************************************/
	// Default constructor
	std::cout << ">>> Default constructor:\n";
	vector<int> vct1;
	std::cout << "Size:     " << vct1.size() << std::endl;
	std::cout << "capacity: " << vct1.capacity() << std::endl;

	// Size defined constructor
	std::cout << ">>> Size defined constructor:\n";
	vector<int> vct2(5);
	std::cout << "Size:     " << vct2.size() << std::endl;
	std::cout << "capacity: " << vct2.capacity() << std::endl;

	// First last constructor
	std::cout << ">>> First last constructor:\n";
	std::array< int, 4 > arr1 = {1, 2, 3, 4};
	vector<int> vct3( arr1.begin(), arr1.end() );
	std::cout << "Size:     " << vct3.size() << std::endl;
	std::cout << "capacity: " << vct3.capacity() << std::endl;
	std::cout << vct3[0] << " " << vct3[1] << " " << vct3[2] << " " << vct3[3] << std::endl;

	// Copy constructor
	std::cout << ">>> Copy constructor:\n";
	vector<int> vct4(vct3);
	std::cout << "Size:     " << vct4.size() << std::endl;
	std::cout << "capacity: " << vct4.capacity() << std::endl;
	std::cout << vct4[0] << " " << vct4[1] << " " << vct4[2] << " " << vct4[3] << std::endl;


	/*******************************************
								    ENDING TESTS								
	*******************************************/
	std::cout << "\n>>> Ending tests\n";

	return EXIT_SUCCESS;
}