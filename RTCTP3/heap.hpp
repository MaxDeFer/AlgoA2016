/*
 * heap.hpp
 *
 *  Created on: 2016-12-05
 *      Author: etudiant
 */

#include "heap.h"



template<typename X>
MinHeap<X>::MinHeap(std::vector<X>& x) {
	int lastParent = x.size()/2 - 1; //car les indices débutent à 0
	for( int i = lastParent; i >= 0; i-- )
	percDown( x, i, x.size( ) );

}

template<typename X>
void MinHeap<X>::percDown(std::vector<X>& x, int i, int j) {
	{
	int child;
	while(leftChild( i ) < j) //tant que a[i] a un enfant
	{
	child = leftChild( i );
	if( child < j - 1 && x[child] < x[child + 1] )
	child++; //child est l’indice du plus grand enfant
	if( x[i] < x[child] ) //alors interchanger et recommencer avec l’enfant
	{
	std::swap( x[i], x[child] );
	i = child;
	}
	else break; //sinon retourner, il n’y a plus rien à faire
	}
	}

}

int leftChild( int i ) { return 2 * i + 1; }

template<typename X>
void MinHeap<X>::insertInHeap(std::vector<X>& x, const X& a) {
	x.push_back(a);
	int child = x.size()-1; //indices débutent en 0
	int parent = (child-1)/2; //== a.size()/2 - 1
	while(child > 0 && x[parent] < x[child])
	{
	std::swap( x[parent], x[child] );
	child = parent;
	parent = (child-1)/2;
	}
}

template<typename X>
void MinHeap<X>::removeFromHeap(std::vector<X>& x) {
	x[0] = x[x.size()-1]; //écrasement de la racine
	x.pop_back(); //enlever le dernier élément de a
	percDown(x, 0, x.size()); //reconstruire le reste du tas
}

template<typename X>
void MinHeap<X>::heapsort(std::vector<X>& x) {
	MinHeap(x); // construction du monceau
	for( int j = x.size( ) - 1; j > 0; j-- )
	{
	swap( x[ 0 ], x[ j ] ); // positionner la racine dans le tableau trié
	percDown( x, 0, j ); //reconstruction du tas sans l’élément j
	}
}
