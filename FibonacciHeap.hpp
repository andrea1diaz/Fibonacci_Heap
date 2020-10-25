#ifndef FibonacciHeap_H
#define FibonacciHeap_H

#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>

#include "Node.hpp"
#include "Lector.hpp"
#include "CImg.h"

template <class T>
class FibonacciHeap {
private:
	int size;
	std::vector<Node<T> *> grados;
	std::vector<Node<T> *> roots;
	Node<T> *min;
	Node<T> *head;
	Node<T> *tail;
    bool help = false;
    Node<T> *head_next = nullptr;
    Node<T> *tail_prev = nullptr;

public:
	FibonacciHeap() {
		size = 0;
	}

	bool empty() {
		return size == 0;
	}

	Node<T>* insert (T key) {
		Node<T>* cur = new Node<T> (key);

		roots.push_back(cur);

		if (size == 0) {
			min = cur;
		}
		else if (min->key > key) {
			min = cur;
		}
		
		size++;
		return cur;
	}

public:

	void compact_tree() {
		grados = std::vector<Node<T> *> (size, nullptr);
		std::vector<Node<T>*> nuevosRoots;

		for (auto it = roots.begin(); it != roots.end(); it++) {
			if(!grados[(*it)->grado]) {
				grados[(*it)->grado] = *it;
			} else {
				Node<T>* tmp = *it;
				while(grados[tmp->grado]) {
					tmp = unite(grados[tmp->grado], tmp);
					grados[tmp->grado - 1] = nullptr;
				}
				grados[tmp->grado] = tmp;
			}
		}

		for (auto i : grados) {
			if (i)
				nuevosRoots.push_back(i);
		}

		roots = nuevosRoots;
	}


	Node<T>* unite (Node<T> *first_node, Node<T> *second_node) {
		
		if(first_node->key < second_node->key) {
			second_node->parent = first_node;
			if(!first_node->head) {
				first_node->init_children(second_node);
			}
			else {
				first_node->add_child(second_node);
			}

			first_node->grado++;

			return first_node;
		}
		else {
			first_node->parent = second_node;
			if(!second_node->head) {
				second_node->init_children(first_node);
			}
			else {
				second_node->add_child(first_node);
			}
			second_node->grado++;
            return second_node;
		}
	}

	Node<T>* get_min () {
        return min;
    }

	Node<T>* extract_min() {
		// Retornar el nodo (Kruskal)
		auto it = std::find(roots.begin(), roots.end(), min);
		Node<T>* ret(min);

		if (min->head) {
			auto cur = min->head;
			do {
				roots.push_back(cur);
				cur = cur->next;
			} while (cur != min->head);
		}

		roots.erase(it);
		new_min();
	
		compact_tree();

		size--;

		return ret;
    }

	

	void new_min() {
		auto m = roots.begin();
		Node<T>* mip = *m;

		for (auto it = roots.begin(); it != roots.end(); it++) {
			if (mip->key > (*it)->key) {
				mip = *it;
			}
		}

		min = mip;
	}

	void meld(Node<T> *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        if (node == head) {
            head = min->next;
        }
        if (node == tail) {
            tail = min->prev;
        }

		if(!node->head) {
		    return;
		}

		else {
            tail->next = node->head;
            node->head->prev = tail;
            node->tail->next = head;
            head->prev = node->tail;
            tail = node->tail;
        }
	}
	
	// void decrease_key(Node<T> *node, T new_key) {
    //     node->key = new_key;

	// 	if (!node->parent) {
	// 		if (min->key > new_key)
	// 			min = node;
	// 	}

	// 	else {
	// 		if (node->parent->key > new_key) {
	// 				node->isBlack = false;
					
	// 				node->prev->next = node->next;
	// 				node->next->prev = node->prev;

	// 				tail->next = node;
	// 				node->prev = tail;
	// 				node->next = head;
	// 				head->prev = node;

	// 				tail = node;

	// 				node->parent->grado--;

	// 			if (!node->parent->isBlack) {
	// 				node->parent->isBlack = true;
	// 				node->parent = nullptr;

	// 				compact_tree();
	// 			}

	// 			else {
	// 				Node<T> *current = node->parent;
	// 				Node<T> *tmp = current;
					
	// 				do {
	// 					current->prev->next = current->next;
	// 					current->next->prev = current->prev;

	// 					tail->next = current;
	// 					current->prev = tail;
	// 					current->next = head;
	// 					head->prev = current;

	// 					tail = node;

	// 					current->isBlack = false;

	// 					tmp = current;
	// 					current = current->parent;
	// 					current->grado--;
						
	// 					tmp->parent = nullptr; // voy a revisarlo una vez más, pero lo subo y lo pruebas? 
						
	// 				} while (current->parent->isBlack && current->parent);
	// 			}
	// 		}
			
	// 		else {
	// 			// nada
	// 		}
	// 	}
    // }

	void print_heap () {
		for(auto it = roots.begin(); it != roots.end(); it++) {
        	std::cout << (*it)->key << std::endl;
            (*it)->print_children();
		}
	}

	// A y B deben tener el mismo tamaño
	T distance(std::vector<T> a, std::vector<T> b) {
		T dist = 0;
		for (int i = 0; i < a.size(); ++i) {
			dist += (a[i] - b[i]) * (a[i] - b[i]);
		}

		return sqrt(dist);
	}

private:

    Node<T>* searchAux(Node<T>* node, T value) {
        if (node) {
            if (node->key == value) {
                return node;
            }
            for (int j = 0; j < node->children.size(); ++j) {
                auto aux = searchAux(node->children[j], value);
                if (aux)
                    return aux;
            }
        }
        return nullptr;
    }
};

#endif /* FibonacciHeap_H */
