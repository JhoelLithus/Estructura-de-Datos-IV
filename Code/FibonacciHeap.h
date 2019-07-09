#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <iostream>
#include <cstdlib>
#include <cstdio>  
#include <malloc.h>
#include <fstream>
#include <string>
using namespace std;

template <class T> 
class FibonacciHeap;

template <class T> 
struct node 
{
	private:
		node<T>* prev;
		node<T>* next;
		node<T>* child;
		node<T>* parent;
		T value;
		int degree;
		bool marked;
	public:
		friend class FibonacciHeap<T>;
		node<T>* getPrev() {return prev;}
		node<T>* getNext() {return next;}
		node<T>* getChild() {return child;}
		node<T>* getParent() {return parent;}
		T getValue() {return value;}
		bool isMarked() {return marked;}
		bool hasChildren() {return child;}
		bool hasParent() {return parent;}
};

template <class T> 
class FibonacciHeap 
{
protected:
	node<T>* heap;
public:

	FibonacciHeap();
	virtual ~FibonacciHeap() ;
	node<T>* insert(T value) ;
	void merge(FibonacciHeap& other);
	bool isEmpty();
	T getMinimum();
	T removeMinimum();
	void decreaseKey(node<T>* n,T value);
	node<T>* find(T value);
	void printArbol(int num);
	void printArbol(ofstream & os, node<T> *n);
private:
	node<T>* _empty();
	node<T>* _singleton(T value);
	node<T>* _merge(node<T>* a,node<T>* b);
	void _deleteAll(node<T>* n);
	void _addChild(node<T>* parent,node<T>* child);
	void _unMarkAndUnParentAll(node<T>* n);
	node<T>* _removeMinimum(node<T>* n);
	node<T>* _cut(node<T>* heap,node<T>* n);
	node<T>* _decreaseKey(node<T>* heap,node<T>* n, T value);
	node<T>* _find(node<T>* heap,T value);
};

#include "FibonacciHeap.inl"
#endif
