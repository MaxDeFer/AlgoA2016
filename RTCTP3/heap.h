/*
 * heap.h
 *
 *  Created on: 2016-12-05
 *      Author: etudiant
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <vector>

template <typename X>

class MinHeap {

public:
	MinHeap(std::vector <X> &x);
	void percDown( std::vector<X> & x, int i, int j );
	void insertInHeap(std::vector<X> & x, const X & a);
	void removeFromHeap(std::vector<X> & x);
	void heapsort(std::vector<X> & x );
	int leftChild( int i );




};



#endif /* HEAP_H_ */
