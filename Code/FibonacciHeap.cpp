#include <iostream>
#include <stdio.h>
#include "FibonacciHeap.h"

using namespace std;

int main() 
{
	//test();
	FibonacciHeap<int> h;
	
	h.insert(2);
	h.insert(3);
	h.insert(1);
	h.insert(4);
	h.printArbol(01);
	
	h.removeMinimum();
	h.removeMinimum();
	h.printArbol(02);
	
	h.insert(5);
	h.insert(7);
	h.insert(9);
	h.insert(10);
	h.printArbol(03);
	
	h.removeMinimum();
	h.printArbol(04);
	
	h.insert(2);
	h.insert(12);
	h.insert(22);
	h.printArbol(05);

	h.removeMinimum();
	h.removeMinimum();
	h.removeMinimum();
	
	h.printArbol(21);
	

	return 0;
	
}
