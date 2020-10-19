#include <iostream>

#include "FibonacciHeap.hpp"

int main () {
	FibonacciHeap<int> bh;

	for (int i = 1; i <= 10; ++i) {
	    bh.insert(i);
	}

//	bh.insert(1);
//	bh.insert(2);
//	bh.insert(3);
//	bh.insert(5);

	bh.print_heap();
	bh.extract_min();
	std::cout << "====" << std::endl;
	bh.print_heap();
	return 0;
}
