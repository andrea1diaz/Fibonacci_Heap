#ifndef NODE_H
#define NODE_H

#define cimg_use_jpeg 1
#include "CImg.h"
#include <iostream>
#include <utility>
#include <list>

using namespace cimg_library;

template <class T>
class Node {
public:
	int grado;
	T key;
	std::list<Node<T> *> children;
	Node<T> *parent = nullptr;
	Node<T> *next = nullptr;
	Node<T> *prev = nullptr;
	Node<T> *head = nullptr;
	Node<T> *tail = nullptr;
	// Como el nodo representa la arista, se debe guardar las imagenes y sus coordenadas
	std::pair<CImg<float>, CImg<float>> imagenes;
	std::pair<std::vector<float>, std::vector<float>> coordenadas;
	std::pair<int, int> uv; // indice del nodo u y nodo v que estan conectados dentro del grafo
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
		if (head) {
		    print_children_aux(head, 1);
		}
		std::cout << "\n";
	}

private:
    void print_children_aux(Node<T>* node, int depth) {
	    auto current = node;
	    std::cout << std::endl;
	    do {
	        for (int i = 0; i < depth; ++i) {
                std::cout << "     ";
            }
	        std::cout << current->key << "|--> ";
	        if (current->head) {
                print_children_aux(current->head, depth + 1);
	        }
            std::cout << std::endl;
	        current = current->next;
	    } while (current != node);
	}

};

#endif /* NODE_H */
