#pragma once
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cmath>

using namespace std;
namespace linkedList {

	template<typename T>
	class Node {
	public:
		T _cofficient;
		Node* _next;
		Node(T cofficient) :_cofficient(cofficient), _next(nullptr) {}
	};

	template <typename T>
	class LinkedList {
	private:
		int _size;
		Node<T>* _head;
	public:
		void print_coeff() const {
			if (!_head) {
				cout « "List is empty." « endl;
				return;
			}

			Node<T>* current = _head;
			int exponent = 0;

			do {
				if (current->_cofficient != 0) {
					if (exponent == 0) {
						cout « current->_cofficient;
					}
					else {
						cout «(current->_cofficient > 0 ? "+" : "") « current->_cofficient « "*x^" « exponent;
					}
				}
				current = current->_next;
				exponent++;
			} while (current != _head);

			cout « endl;
		}
		
		T evaluate_at(T x) const {
			if (!_head) {
				cerr « "List is empty." « endl;
				return 0;
			}

			Node<T>* current = _head;
			T result = 0;
			int exponent = 0;

			do {
				result += current->_cofficient * pow(x, exponent);
				current = current->_next;
				exponent++;
			} while (current != _head);

			return result;
		}

		
		LinkedList(int size, int upper_bound, int lover_bound) : _head(nullptr) {
			srand(time(nullptr));
			for (int i = 0; i < size; ++i) {
				T cofficient = rand() % upper_bound + lover_bound;
				push_head(cofficient);
			}
		}

		LinkedList(int size) : _head(nullptr)
		{
			srand(time(nullptr));
			for (int i = 0; i < size; ++i) {
				float cofficient = 0.001 * rand();
				push_head(cofficient);
			}
		}
		
		void delete_node(Node<T>& node) {
			if (!_head) {
				return;
			}

			Node<T>* current = _head;
			while (current->_next != _head) {
				if (current->_next->_cofficient == node._cofficient) {
					Node<T>* temp = current->_next;
					current->_next = current->_next->_next;
					if (temp == _head) {
						_head = _head->_next;
					}
					delete temp;
				}
				else {
					current = current->_next;
				}
			}

			if (_head && _head->_cofficient == node._cofficient) {
				pop_head();
			}
		}


		
		void pop_tail() {
			if (_head) {
				Node<T>* current = _head;
				Node<T>* previous = nullptr;

				while (current->_next != _head) {
					previous = current;
					current = current->_next;
				}
				if (previous) {
					previous->_next = _head;
				}
				else {
					_head = nullptr;
				}
				delete current;
			}
		}

		
		void pop_head() {
			if (_head) {
				Node<T>* temp = _head;
				if (_head->_next != _head) {
					Node<T>* current = _head;
					while (current->_next != _head) {
						current = current->_next;
					}
					_head = _head->_next;
					current->_next = _head;
				}
				else {
					_head = nullptr;
				}
				delete temp;
			}
		}

		
		~LinkedList()
		{
			while (_head) {
				pop_head();
			}
		}
		
		LinkedList<T>& operator=(const LinkedList<T>& other) {
			if (this == &other) {
				return *this;
			}
			while (_head) {
				pop_head();
			}
			if (other._head) {
				Node<T>* otherCurrent = other._head;
				do {
					push_tail(otherCurrent->_cofficient);
					otherCurrent = otherCurrent->_next;
				} while (otherCurrent != other._head);
			}
			return *this;
		}
		
		LinkedList(const LinkedList<T>& other) : _head(nullptr)
		{
			if (other._head) {
				Node<T>* otherCurrent = other._head;
				do {
					push_tail(otherCurrent->_cofficient);
					otherCurrent = otherCurrent->_next;
				} while (otherCurrent != other._head);
			}
		}

		
		void push_head(T cofficient)
		{
			Node<T>* _newmode = new Node<T>(cofficient);
			if (!_head) {
				_head = _newmode;
				_head->_next = _head;
			}
			Node<T>* current = _head;
			while (current->_next != _head) {
				current = current->_next;
			}
			_newmode->_next = _head;
			current->_next = _newmode;
			_head = _newmode;
			_size++;
		}
		
		void push_head(LinkedList<T> other) {
			Node<T>* otherCurrent = other._head;
			if (otherCurrent) {
				do {
					push_head(otherCurrent->_cofficient);
					otherCurrent = otherCurrent->_next;
				} while (otherCurrent != other._head);
			}
		}

		
		T& operator[](int index)
		{
			int counter = 0;
			Node<T>* current = this->_head;
			do {
				if (counter == index) {
					return current->_cofficient;
				}
				current = current->_next;
				counter++;
			} while (current != this->_head);
		}
		
		void push_tail(T coefficient) {
			Node<T>* new_node = new Node<T>(coefficient);

			if (!_head) {
				_head = new_node;
				_head->_next = _head;
			}
			else {
				Node<T>* current = _head;
				while (current->_next != _head) {
					current = current->_next;
				}
				current->_next = new_node;
				new_node->_next = _head;
			}
		}
		
		void push_tail(LinkedList<T> other) {
			if (other._head) {
				Node<T>* otherCurrent = other._head;
				Node<T>* otherHead = other._head;
				do {
					Node<T>* new_node = new Node<T>(otherCurrent->_cofficient);
					if (!_head) {
						_head = new_node;
						_head->_next = _head;
					}
					else {
						Node<T>* current = _head;
						while (current->_next != _head) {
							current = current->_next;
						}
						new_node->_next = _head;
						current->_next = new_node;
					}
					otherCurrent = otherCurrent->_next;
				} while (otherCurrent != otherHead);
				other._head = nullptr;
			}
		}
		
		T operator[](int index) const {
			int counter = 0;
			Node<T>* current = _head;

			if (!current)
				throw std::out_of_range("List is empty");

			do {
				if (counter == index) {
					return current->_cofficient;
				}
				current = current->_next;
				counter++;
			} while (current != _head);

			throw std::out_of_range("Index out of range");
		}
	};
	

}