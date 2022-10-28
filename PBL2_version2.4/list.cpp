#pragma once
#include"thuvien.h"
template<class T>
class node {
public:
	T data;
	node* next;
	node() {}
	node(T data) {
		this->data = data;
		this->next = NULL;
	}
};

template<class T>
class list {
private:
	int size;
	node <T>* head;
	node <T>* tail;
public:
	list() {
		this->size = 0;
		this->head = this->tail = NULL;
	}

	node<T>* getHead() {
		return this->head;
	}

	int getSize() {
		return this->size;
	}

	void push_back(T data) {
		bool check = this->search(data);
		if (!check) {
			node<T>* tam = new node<T>(data);
			if (head == NULL)
				this->tail = this->head = tam;
			else {
				this->tail->next = tam;
				this->tail = tam;
			}
			this->size++;
		}
	}

	bool search(T data) {
		node<T>* temp = head;
		while (temp) {
			if (temp->data == data)
				return true;
			temp = temp->next;
		}
		return false;
	}
	void erase(T data) {
		node<T>* after = this->head, * before = NULL;
		while (after && after->data != data) {
			before = after;
			after = after->next;
		}
		if (after) {
			this->size--;
			if (after == head)
				head = head->next;
			else before->next = after->next;
			delete after;
		}
	}

	void display() {
		node<wstring>* head = this->getHead();
		int idx = 0;
		while (head) {
			wcout << ++idx << ":" << head->data << endl;
			head = head->next;
		}
	}
};