#include <iostream>

#include "FibonacciHeap.hpp"

int main () {
	FibonacciHeap<int> bh;

	// TODO: Revisar que este bien
    for (int i = 1; i <= 100; ++i) {
         bh.insert(i);
     }
	bh.extract_min();
	bh.extract_min();
    bh.extract_min();
    bh.extract_min();
    bh.extract_min();
    bh.extract_min();
    bh.extract_min();
	bh.print_heap();
	// End test

	// Lectura de imagenes
	bh.buildFromInput();
	return 0;
}
