#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include <iostream>
#include <list>
#include <vector>

#include "Node.hpp"

template <class T>
class BinomialHeap {
private:
	int size;
	std::vector<Node<T> *> grados;

public:
	BinomialHeap() {
		size = 0;
	}

	void insert (T key) {
		Node<T> *new_node = new Node<T> (key);

		size ++;

		compact_tree(new_node);
	}
	
	void  compact_tree (Node<T> *node) {
		if (grados.size() > node->grado && grados[node->grado]) {
			unite (grados[node->grado], node);
			
		}
		
		else if (grados.size() <= node->grado) {
			grados.push_back(node);
		}

		else {
			grados[node->grado] = node;
		}
	}

	void unite (Node<T> *first_node, Node<T> *second_node) {
		if (first_node->key <= second_node->key) {
			second_node->parent = first_node;
			first_node->children.push_back(second_node);

			grados[first_node->grado ++] = nullptr;
			
			compact_tree(first_node);
		}

		else {
			first_node->parent = second_node;
			second_node->children.push_back(first_node);

			grados[second_node->grado ++] = nullptr;
			
			compact_tree(second_node);
		}
	}

	T get_min () {
		for (auto i : grados) {
			
		}
	}

	void print_heap () {
		for (auto i : grados) {
			if (i) {
				std::cout << i->key << "\n";
				i->print_children();
			}
		}
	}
};

#endif /* BINOMIALHEAP_H */
