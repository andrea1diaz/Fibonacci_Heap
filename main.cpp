#include <iostream>

#include "BinomialHeap.hpp"

int main () {
	BinomialHeap<int> bh;

	bh.insert(1);
	bh.insert(2);
	bh.insert(3);
	bh.insert(5);

	bh.print_heap();
	return 0;
}
