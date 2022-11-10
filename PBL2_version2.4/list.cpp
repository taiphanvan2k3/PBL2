#pragma once
#include"node.cpp"
template<class T>
class list {
private:
	int size;
	node <T>* head;
	node <T>* tail;
public:
	list();
	node<T>* getHead();
	int getSize();
	void push_back(T data);
	bool search(T data);
	void erase(T data);
	void display();
};

template<class T>
list<T>::list() {
	this->size = 0;
	this->head = this->tail = NULL;
}

template<class T>
node<T>* list<T>::getHead() {
	return this->head;
}

template<class T>
int list<T>::getSize() {
	return this->size;
}

template<class T>
void list<T>::push_back(T data) {
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

template<class T>
bool list<T>::search(T data) {
	node<T>* temp = head;
	while (temp) {
		if (temp->data == data)
			return true;
		temp = temp->next;
	}
	return false;
}

template<class T>
void list<T>::erase(T data) {
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

template<class T>
void list<T>::display() {
	node<T>* head = this->getHead();
	int idx = 0;
	while (head) {
		wcout << ++idx << ":" << head->data << endl;
		head = head->next;
	}
}