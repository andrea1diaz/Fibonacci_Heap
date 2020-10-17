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
	void decrease_key(Node<T> *node, T new_key) {
        node->key = new_key;
        Node<T> *current = node;
        T tmp;
        while(current->parent && current->parent->key > current->key) {
            tmp = current->parent->key;
            current->parent->key = current->key;
            current->key = tmp;
            current = current->parent;
        }
    }

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

	void  compact_tree () {
		grados = vector<Node*>(size, nullptr);
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
			if(!first->node->head) {
				initChildren(second_node);
			}
			else {
				addChild(second_node);
			}
		}
		else {
			if(!head) {
				initChildren(second_node);
			}
			else {
				addChild(second_node);
			}
		}
	}

	Node<T>* get_min () {
        // asumimos que size > 0
        Node<T> *min_node = new Node<T>(std::numeric_limits<T>::max());
        for (auto x : grados)
            if(x)
                min_node = min_node->key < x->key ? min_node : x;
        return min_node;
    }

	void delete_min() {
        Node<T>* min_node = get_min();
        size--;
        grados[min_node->grado] = nullptr;
        for(auto x : min_node->children)
            compact_tree(x);
        delete min_node;
    }

	
	void delete_key(T k) {
        Node<T>* node = search(k);
        if (node) {
            decrease_key(node, std::numeric_limits<T>::min());
            delete_min();
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
	
	Node<T>* search(T value) {
        for(int i = 0; i < grados.size(); ++i) {
            if (grados[i]) {
                auto aux = searchAux(grados[i], value);
                if (aux)
                    return aux;
            }
        }
        return nullptr;
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
