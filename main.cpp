#include <iostream>
#include "Graph.h"

int main () {
	FibonacciHeap<int> bh;

	// TODO: Revisar que este bien
    for (int i = 1; i <= 10; ++i) {
         bh.insert(i);
     }
	bh.extract_min();
	bh.extract_min();
	bh.extract_min();
	bh.extract_min();
	bh.extract_min();
	bh.print_heap();
	// // End test

	// // Lectura de imagenes
	// bh.buildFromInput();
	// Graph* g = new Graph();
	// g->drawMST();
	return 0;
}
