#ifndef FibonacciHeap_H
#define FibonacciHeap_H

#include <iostream>
#include <list>
#include <vector>

#include "Node.hpp"

template <class T>
class FibonacciHeap {
private:
	int size;
	std::vector<Node<T> *> grados;
	std::list<Node<T> *> roots;
	Node<T> *min;
	Node<T> *head;
	Node<T> *tail;

public:
	FibonacciHeap() {
		size = 0;
	}

	void insert (T key) {
		Node<T>* cur = new Node<T> (key);
		if (size == 0) {
			min = cur;
			tail = head = cur;
			tail->prev = head;
			tail->next = head;
			head->prev = tail;
			head->next = tail;
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
	}

	void compact_tree () {
		grados = std::vector<Node<T> *>(size, nullptr);
		Node<T> *current = head;
		
		do {
			if(grados[current->grado]) {
				unite(grados[current->grado], current);
			}
			else {
				grados[current->grado] = current;
			}
			current = current->next;
		} while(current != head);
	}

	void unite (Node<T> *first_node, Node<T> *second_node) {
		if(first_node->key < second_node->key) {
			second_node->parent = first_node;
			if(!first_node->head) {
				first_node->init_children(second_node);
			}
			else {
				first_node->add_child(second_node);
			}
			first_node->grado++;
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
		}
	}

	Node<T>* get_min () {
        return min;
    }

	T extract_min() {
		meld(min);
		T value = min->key;
		delete min;
		min = new_min();

		compact_tree();
		return value;
    }

	Node<T>* new_min() {
		Node<T>* current = head;
		Node<T>* min = current;
		do {
			if (current->key < min->key) min = current;
			current = current->next;
		} while(current != head);
		return min;
	}

	void meld(Node<T> *node) {
		if(!node->head) return;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		
		tail->next = node->head;
		node->head->prev = tail;
		node->tail->next = head;
		head->prev = node->tail;
		tail = node->tail;
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

        /*Node<T> *current = node;
        T tmp;
        while(current->parent && current->parent->key > current->key) {
            tmp = current->parent->key;
            current->parent->key = current->key;
            current->key = tmp;
            current = current->parent;
        }*/
		
    }

	void print_heap () {
		auto cur = head;
		if (cur) {
			std::cout << cur->key << std::endl;
			cur->print_children();
			cur = cur->next;
		}
		while (cur && cur != head) {
			std::cout << '\n';
			std::cout << cur->key << std::endl;
			cur->print_children();
			cur = cur->next;
		}
		// for (auto i : grados) {
		// 	if (i) {
		// 		std::cout << i->key << "\n";
		// 		i->print_children();
		// 	}
		// }
	}

	void buildFromInput() {
        T n;
        while(std::cin >> n) insert(n);
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
