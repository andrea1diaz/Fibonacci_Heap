#include <iostream>

#include "FibonacciHeap.hpp"

int main () {
	FibonacciHeap<int> bh;

	bh.insert(1);
	bh.insert(2);
	bh.insert(3);
	bh.insert(5);

	bh.print_heap();
	bh.extract_min();
	bh.print_heap();
	return 0;
}
