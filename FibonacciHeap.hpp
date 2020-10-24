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
		return cur;
	}

private:
    // void compact_helper(Node<T>* node) {
    //     if (node->key < grados[node->grado]->key) {
    //         grados[node->grado]->next->prev = grados[node->grado]->prev;
    //         grados[node->grado]->prev->next = grados[node->grado]->next;
    //     } else {
    //         node->next->prev = node->prev;
    //         node->prev->next = node->next;
    //     }
    //     auto tmp = unite(node, grados[node->grado]);
    //     if (tmp->tail == head) {
    //         head = head_next;
    //     }
    //     if (tmp->tail == tail) {
    //         tail = tail_prev;
    //     }
    //     grados[tmp->grado - 1] = nullptr;
    //     if (grados[tmp->grado]) {
    //         compact_helper(tmp);
    //     } else {
    //         grados[tmp->grado] = tmp;
    //     }
	// }
public:

	// void compact_tree () {
	// 	grados = std::vector<Node<T> *>(size, nullptr);
	// 	Node<T> *current = head;
		
	// 	do {
	// 	    head_next = head->next;
	// 	    tail_prev = tail->prev;
	// 	    auto cur_next = current->next;
	// 		if(grados[current->grado]) {
	// 		    compact_helper(current);
	// 		}
	// 		else {
	// 			grados[current->grado] = current;
	// 		}
	// 		current = cur_next;
	// 	} while(current != head);
	// }

	void compact_tree() {
		grados = std::vector<Node<T> *> (size, nullptr);
		Node<T>* cur = head;
		do {
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
			cur = cur->next;
		} while(current != head);
	}


	Node<T>* unite (Node<T> *first_node, Node<T> *second_node) {
		if(first_node->key < second_node->key) {
			second_node->parent = first_node;
			second_node->prev->next = second_node->next;
			second_node->next->prev = second_node->prev;
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
		meld(min);
		Node<T>* cur = min;

		min = new_min();
	
		compact_tree();
		return cur;
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

public:
	// void buildFromInput() {
	// 	images = lector.Vectorizar();
	// 	// first es el vector caracteristico y second la imagen
	// 	std::vector<std::vector<T> > distances
	// 	for(int i = 0; i < images.size(); ++i) {
	// 		for(int j = 0; j < images.size(); ++j) {
	// 			if(i == j) {
	// 				distances[i][j] = 0;
	// 				continue;
	// 			}
	// 			else if(distances[i][j])
	// 				continue;
	// 			distance[i][j] = distance(images[i].first, images[j].first);
	// 			Node<T>* cur = insert(distance[i][j]);
	// 			cur->coordenadas = {images[i].first, images[j].first};
	// 			cur->imagenes = {images[i].second, images[j].second};
	// 		}
	// 	}
	// 	// Answer tiene todos los vectores caracteristicos y las imagenes correspondientes
	// 	// armar el heap con las aristas?
	// 	// las aristas serian las distancias entre cada nodo (usar la funcion distance())
	// 	// las coordenadas estan guardadas en answer
    // }


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
