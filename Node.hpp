#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <list>

template <class T>
class Node {
public:
	int grado;
	T key;
	std::list<Node<T> *> children;
	Node<T> *parent;
	Node<T> *next;
	Node<T> *prev;
	Node<T> *head;
	Node<T> *tail;
	bool isBlack = false;

	Node();

	Node (T data) {
		key = data;
		grado = 0;
	}

	void init_children (Node<T>* node) {
		tail = head = node;

		tail->prev = head;
		tail->next = head;
		head->prev = tail;
		head->next = tail;
	}


	void add_child (Node<T> *child) {
		tail->next = child;
		child->prev = tail;
		child->next = head;
		head->prev = child;

		tail = child;
	}

	void print_children () {
		std::cout << "|--> ";
		for (auto i : children) {
			if (i) {
				std::cout << i->key << " ";
				
			if (i->children.size() > 0)
				i->print_children();	
			}
		}
		std::cout << "\n";
	}


};

#endif /* NODE_H */
