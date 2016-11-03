#include "reseau.h"


Reseau::Reseau() {
}

void Reseau::ajouterSommet(unsigned int numero) throw (std::logic_error) {
}

void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error) {
}

void Reseau::ajouterArc(unsigned int numOrigine, unsigned int numDest,
		unsigned int cout, unsigned int type) throw (std::logic_error) {
}

void Reseau::enleverArc(unsigned int numOrigine, unsigned int numDest)
		throw (std::logic_error) {
}

void Reseau::majCoutArc(unsigned int numOrigine, unsigned int numDest,
		unsigned int cout) throw (std::logic_error) {
}

int Reseau::nombreSommets() const {
}

int Reseau::nombreArcs() const {
}

bool Reseau::estVide() const {
}

bool Reseau::sommetExiste(unsigned int numero) const {
}

bool Reseau::arcExiste(unsigned int numOrigine, unsigned int numDest) const
		throw (std::logic_error) {
}

int Reseau::getCoutArc(unsigned int numOrigine,
		unsigned int numDestination) const throw (std::logic_error) {
}

int Reseau::getTypeArc(unsigned int numOrigine,
		unsigned int numDestination) const throw (std::logic_error) {
}

int Reseau::dijkstra(unsigned int numOrigine, unsigned int numDest,
		std::vector<unsigned int>& chemin) throw (std::logic_error) {
}

int Reseau::bellmanFord(unsigned int numOrigine, unsigned int numDest,
		std::vector<unsigned int>& chemin) throw (std::logic_error) {
}

bool Reseau::estFortementConnexe() const {
}

int Reseau::getComposantesFortementConnexes(
		std::vector<std::vector<unsigned int> >& composantes) const {
}
/*
 * reseau.cpp
 *
 *  Created on: 2016-11-03
 *      Author: etudiant
 */




