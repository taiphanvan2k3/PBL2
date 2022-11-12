#pragma once
#define maxsize 6997
#include"vocab.h"
#include"list.cpp"
template<class T>
class Hashtable {
protected:
	T* heads[maxsize];
	list<int>listId;
	//Lưu những id khi mà hash ra
	int num, deleted;
public:
	Hashtable();
	~Hashtable();
	int hash(wstring key);
	void insertIntoLinkList(T*& head, T* x);
	int getSoLuong();
	void convertToArray(T*& ds, int& n);
	bool insert(T* x);
	T* search(wstring key);
};

template<class T>
Hashtable<T>::Hashtable() {
	num = deleted = 0;
	for (int i = 0; i < maxsize; i++)
		heads[i] = NULL;
}

template<class T>
Hashtable<T>::~Hashtable() {
	node<int>* head = listId.getHead();
	while (head) {
		int idx = head->getData();
		deleteLinkList(heads[idx]);
		head = head->getNext();
	}
}

template<class T>
int Hashtable<T>::hash(wstring key) {
	int sum = 0, len = (int)key.length();
	for (int i = 0; i < len; i++)
		sum += key[i];
	return sum % maxsize;
}

template<class T>
void Hashtable<T>::insertIntoLinkList(T*& head, T* x) {
	if (head == NULL)
		head = x;
	else {
		x->setNext(head);
		head = x;
	}
}

template<class T>
int Hashtable<T>::getSoLuong() {
	return this->num - this->deleted;
}

template<class T>
void Hashtable<T>::convertToArray(T*& ds, int& n) {
	n = num - deleted;
	ds = new T[n];
	int i = 0;
	node<int>* l = listId.getHead();
	while (l) {
		T* tam = heads[l->getData()];
		while (tam) {
			ds[i++] = *tam;
			tam = tam->getNext();
		}
		l = l->getNext();
		//l = l->next;
	}
}

template<class T>
bool Hashtable<T>::insert(T* x) {
	T* tam = this->search(x->getKey());
	if (tam != NULL)
		return false;
	int id = hash(x->getKey());
	if (heads[id] == NULL)
		listId.push_back(id);
	num++;
	this->insertIntoLinkList(heads[id], x);
	return true;
}

template<class T>
T* Hashtable<T>::search(wstring key) {
	convert(key);
	int id = hash(key);
	T* tam = heads[id];
	while (tam) {
		if (wstrcmp(tam->getKey(), key) == 0)
			return tam;
		tam = tam->getNext();
	}
	return NULL;
}
