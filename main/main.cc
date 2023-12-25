#pragma once
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cmath>
#include <random>

using namespace std;
namespace linkedList {

	template<typename T>
	class Node {
	public:
		string lastName;
		string firstName;
		int course;
		float averageScore;
		Node* next;

		Node(string lName, string fName, int crs, float score) {
			lastName = lName;
			firstName = fName;
			course = crs;
			averageScore = score;
			next = nullptr;
    	}
	};

	template <typename T>
	class LinkedList {
	private:
		Node<T>* _head;
	public:
		LinkedList() : _head(nullptr) {}

		LinkedList(const LinkedList& other) {
			_head = nullptr;
			if (other._head != nullptr) {
				Node* current = other._head->next;
				do {
					addStudent(new Node(current->lastName, current->firstName, current->course, current->averageScore));
					current = current->next;
				} while (current != other._head->next);
			}
		}
		LinkedList(int numStudents) : _head(nullptr) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> scoreDistribution(2.0, 5.0);
			for (int i = 0; i < numStudents; ++i) {
				addStudent(new Node("LastName" + to_string(i), "FirstName" + to_string(i), i % 5 + 1, scoreDistribution(gen)));
			}
		}

		~LinkedList() {
			while (_head != nullptr) {
				pop_head();
			}
		}

		LinkedList& operator=(const LinkedList& other) {
			if (this != &other) {
				LinkedList temp(other);
				std::swap(head, temp.head);
			}
			return *this;
		}

		void addStudent(Node* newStudent) {
			if (head == nullptr) {
				_head = newStudent;
				_head->next = _head; 
			} else {
				newStudent->next = _head->next;
				_head->next = newStudent;
				_head = newStudent; 
			}
		}

		void push_tail(LinkedList& other) {
			if (other._head != nullptr) {
				Node* current = other._head->next;
				do {
					addStudent(new Node(current->lastName, current->firstName, current->course, current->averageScore));
					current = current->next;
				} while (current != other._head->next);
			}
		}

		void push_head(Node* newStudent) {
			if (_head == nullptr) {
				addStudent(newStudent);
			} else {
				newStudent->next = _head->next;
				_head->next = newStudent;
			}
		}

		void push_head(LinkedList& other) {
			if (other._head != nullptr) {
				Node* current = other._head->next;
				do {
					push_head(new Node(current->lastName, current->firstName, current->course, current->averageScore));
					current = current->next;
				} while (current != other._head->next);
			}
		}

		void pop_head() {
			if (_head != nullptr) {
				if (_head->next == _head) { 
					delete _head;
					_head = nullptr;
				} else {
					Node* temp = _head->next;
					_head->next = temp->next;
					delete temp;
				}
			}
		}

		void pop_tail() {
			if (_head != nullptr) {
				if (_head->next == _head) { 
					delete _head;
					_head = nullptr;
				} else {
					Node* current = _head->next;
					while (current->next != _head) {
						current = current->next;
					}
					current->next = _head->next;
					delete _head;
					_head = current;
				}
			}
		}

		void delete_node(const string& lName, const string& fName, int crs) {
			if (_head != nullptr) {
				Node* current = _head->next;
				Node* prev = _head;
				while (current != _head) {
					if (current->lastName == lName && current->firstName == fName && current->course == crs) {
						prev->next = current->next;
						delete current;
						current = prev->next;
					} else {
						prev = current;
						current = prev->next;
					}
				}
			}
		}

		Node* operator[](int index) const {
			if (index < 0 || head == nullptr) return nullptr;

			Node* current = _head->next;
			int count = 0;

			do {
				if (count == index) return current;
				++count;
				current = current->next;
			} while (current != _head->next);

			return nullptr; 
		}

		Node*& operator[](int index) {
			if (index < 0 || _head == nullptr) 
				throw out_of_range("Index out of range");

			Node* current = _head->next;
			int count = 0;

			do {
				if (count == index) 
					return current;
				++count;
				current = current->next;
			} while (current != _head->next);

			throw out_of_range("Index out of range"); 
		}
		void removeDuplicates() {
			unordered_set<string> seen;
			Student* current = head->next;
			Student* prev = _head;

			while (current != _head) {
				string key = current->firstName + current->lastName + to_string(current->course);
				if (seen.find(key) != seen.end()) {
					prev->next = current->next;
					delete current;
				} else {
					seen.insert(key);
					prev = current;
				}
				current = prev->next;
			}
		}
	};
}