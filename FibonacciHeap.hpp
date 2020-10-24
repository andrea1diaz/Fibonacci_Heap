#ifndef FibonacciHeap_H
#define FibonacciHeap_H

#include <iostream>
#include <cmath>
#include <list>
#include <vector>

#include "Node.hpp"
#include "Lector.hpp"
#include "CImg.h"

template <class T>
class FibonacciHeap {
private:
	int size;
	std::vector<Node<T> *> grados;
	std::list<Node<T> *> roots;
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
		if (size == 0) {
			min = cur;
			tail = head = cur;
			cur->prev = cur;
			cur->next = cur;
		}
		else {
			tail->next = cur;
			cur->prev = tail;
			cur->next = head;
			head->prev = cur;

			tail = cur; 

			if(min->key > key) {
				min = cur;
			}
		}
		size ++;
	
		return cur;
	}

public:

	void compact_tree() {
		grados = std::vector<Node<T> *> (size, nullptr);
		Node<T>* cur = head;
		bool q = 0;
		while(1){
			Node<T> *next = cur->next;
			if(cur == tail)
				q = true;
			if(grados[cur->grado]) {

				while(grados[cur->grado]) {
					cur = unite(grados[cur->grado], cur);
					grados[cur->grado - 1] = nullptr;
				}
				grados[cur->grado] = cur;
			}
			else {
				grados[cur->grado] = cur;
			}

			cur = next;
			if(q)
				break;
		}

	}


	Node<T>* unite (Node<T> *first_node, Node<T> *second_node) {
		if(first_node->key < second_node->key) {
			second_node->parent = first_node;
			second_node->prev->next = second_node->next;
			second_node->next->prev = second_node->prev;

			if(second_node == head) {
				head = first_node;
				if (grados.size() >= 0) {
					tail = first_node->next;
				}

			}
			if(second_node == tail) {
				tail = first_node;
			}
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
			first_node->prev->next = first_node->next;
			first_node->next->prev = first_node->prev;

			if(first_node == head) {
				head = second_node;

				if (grados.size() >= 0) {
					tail = second_node->next;
				}
			}
			if(first_node == tail) {
				tail = second_node;

			}
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
		if (size > 1) {
			meld(min);
			size--;
			Node<T>* cur = min;


			min = new_min();


			if (tail != head) compact_tree();

			return cur;
		}
	
		size --;
		return head;
	}

	

	Node<T>* new_min() {
		Node<T>* current = head;
		Node<T>* n_min = current;
		do {
			Node<T> * next_ = current->next;
			if (current->key < n_min->key) n_min = current;

			current = next_;
		} while(current != head);

		return n_min;
	}

	void meld(Node<T> *node) {
		if(!node->head) {
			if(head == tail) {
				head = nullptr;
				tail = nullptr;
				return;
			}

			node->prev->next = node->next;
			node->next->prev = node->prev;

			if (node == head) {
				head = node->next;
			}
			else if (node == tail) {
				tail = node->prev;

			}
		    return;
		}
		Node<T>* cur = node->head;
		do {
			Node<T>* next_ = cur->next;	
			cur->parent = nullptr;
			cur = next_;
		} while(cur != node->head);
		if(head == tail) {
			head = node->head;
			tail = node->tail;
		}
		else {
			if (node == head) {
				head = node->next;
			}
			else if (node == tail) {
				tail = node->prev;
			}
			node->prev->next = node->next;
			node->next->prev = node->prev;
			
			tail->next = node->head;
			node->head->prev = tail;
			node->tail->next = head;
			head->prev = node->tail;
			
			tail = node->tail;
		}
	}
	
	void decrease_key(Node<T> *node, T new_key) {
        node->key = new_key;

		if (!node->parent) {
			if (min->key > new_key)
				min = node;
		}

		else {
			if (node->parent->key > new_key) {
					node->isBlack = false;
					
					node->prev->next = node->next;
					node->next->prev = node->prev;

					tail->next = node;
					node->prev = tail;
					node->next = head;
					head->prev = node;

					tail = node;

					node->parent->grado--;

				if (!node->parent->isBlack) {
					node->parent->isBlack = true;
					node->parent = nullptr;

					compact_tree();
				}

				else {
					Node<T> *current = node->parent;
					Node<T> *tmp = current;
					
					do {
						current->prev->next = current->next;
						current->next->prev = current->prev;

						tail->next = current;
						current->prev = tail;
						current->next = head;
						head->prev = current;

						tail = node;

						current->isBlack = false;

						tmp = current;
						current = current->parent;
						current->grado--;
						
						tmp->parent = nullptr; // voy a revisarlo una vez más, pero lo subo y lo pruebas? 
						
					} while (current->parent->isBlack && current->parent);
				}
			}
			
			else {
				// nada
			}
		}
    }

	void print_heap () {
		auto cur = head;
		if (cur) {
            do {
                std::cout << cur->key << std::endl;
                cur->print_children();
                cur = cur->next;
            } while (cur != head);
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
