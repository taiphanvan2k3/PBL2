#pragma once
#include"thuvien.h"
template<class T>
class Hashtable;
template<class T>
class list;

template<class T>
class node {
private:
	T data;
	node* next;
public:
	node();
	node(T data);
	T getData();
	node* getNext();

	friend class list<T>;
	friend class Hashtable<T>;
	friend class HashtableVocab;
	friend class HashtableUser;
};

template<class T>
node<T>::node() {

}

template<class T>
node<T>::node(T x) {
	data = x;
	next = NULL;
}

template<class T>
T node<T>::getData() {
	return data;
}

template<class T>
node<T>* node<T>::getNext() {
	return this->next;
}