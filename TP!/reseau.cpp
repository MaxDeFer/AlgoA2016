#include "reseau.h"
#include <vector>
#include <list>
#include <map>
#include <stack>

Reseau::Reseau() {

}

void Reseau::ajouterSommet(unsigned int numero) throw (std::logic_error) {
	liste_arcs arcsVides;
	m_graphe.insert(std::pair<unsigned int, liste_arcs>(numero, arcsVides));
}

void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error) {
	m_graphe.erase(numero);
}

void Reseau::ajouterArc(unsigned int numOrigine, unsigned int numDest,
		unsigned int cout, unsigned int type) throw (std::logic_error) {
	std::pair<unsigned int, unsigned int> tmp(cout, type);
	m_graphe.at(numOrigine).insert(
			std::pair<unsigned int, std::pair<unsigned int, unsigned int>>(
					numDest, tmp));

}

void Reseau::enleverArc(unsigned int numOrigine, unsigned int numDest)
		throw (std::logic_error) {
	m_graphe.at(numOrigine).erase(numDest);
}

void Reseau::majCoutArc(unsigned int numOrigine, unsigned int numDest,
		unsigned int cout) throw (std::logic_error) {
	m_graphe.at(numOrigine).at(numDest).first = cout;
}

int Reseau::nombreSommets() const {
	return m_graphe.size();
}

int Reseau::nombreArcs() const {
	int total = 0;
	for (std::pair<unsigned int, liste_arcs> element : m_graphe) {
		total += element.second.size();
	}
	return total;
}

bool Reseau::estVide() const {
	if (m_graphe.size() == 0) {
		return true;
	} else {
		return false;
	}

}

bool Reseau::sommetExiste(unsigned int numero) const {
	std::unordered_map<unsigned int, liste_arcs>::const_iterator got =
			m_graphe.find(numero);
	if (got == m_graphe.end()) {
		return false;
	} else {
		return true;
	}
}

bool Reseau::arcExiste(unsigned int numOrigine, unsigned int numDest) const
		throw (std::logic_error) {

	bool booltmp = false;
	if (m_graphe.at(numOrigine).count(numDest) > 0) {
		booltmp = true;
	}
	return booltmp;
}

int Reseau::getCoutArc(unsigned int numOrigine,
		unsigned int numDestination) const throw (std::logic_error) {
	return m_graphe.at(numOrigine).at(numDestination).first;
}

int Reseau::getTypeArc(unsigned int numOrigine,
		unsigned int numDestination) const throw (std::logic_error) {
	return m_graphe.at(numOrigine).at(numDestination).second;
}

int Reseau::dijkstra(unsigned int numOrigine, unsigned int numDest,
		std::vector<unsigned int>& chemin) throw (std::logic_error) {

	std::map<unsigned int, std::pair<unsigned int, unsigned int>> sommetsNonSol;
	std::map<unsigned int, std::pair<unsigned int, unsigned int>> sommetsSol;

	int u;

	// On initialise a Infini les poids et 0 les predecesseurs
	for (std::pair<unsigned int, liste_arcs> element : m_graphe) {
		std::pair<unsigned int, unsigned int> tmp(INFINI, 0);
		sommetsNonSol.insert(
				std::pair<unsigned int, std::pair<unsigned int, unsigned int>>(
						element.first, tmp));

	}

	sommetsNonSol.at(numOrigine).first = 0;
	sommetsNonSol.at(numOrigine).second = numOrigine;

	//On boucle autant de fois que le nombre de sommets
	for (int i = 0; i < this->nombreSommets(); i++) {
		unsigned int petite = INFINI;
		//std::cout << sommetsNonSol.size();
		//Pour toute les valeurs non solutionnees on cherche la valeur la plus petite
		//Pour toute les noeuds non solutionnees on regarde si leur poid est plus petit que petite = INFINI
		//Si oui, on remplace petite par la valeur du noeud
		for (auto g = sommetsNonSol.begin(); g != sommetsNonSol.end(); g++) {
			if (g->second.first < petite) {
				petite = g->second.first;
				u = g->first;

			}
		}
		sommetsSol[u] = sommetsNonSol[u];
		sommetsNonSol.erase(u);
		unsigned int tmp = INFINI;

		for (auto element = sommetsNonSol.begin();
				element != sommetsNonSol.end(); element++) {

			if (this->arcExiste(u, element->first)) {

				tmp = petite + getCoutArc(u, element->first);

				if (tmp < element->second.first) {

					element->second.first = tmp;
					element->second.second = u;
				}
			}
		}

	}
	unsigned int trail = numDest;
	while (trail != numOrigine) {
		chemin.push_back(trail);
		trail = sommetsSol[trail].second;
	}
	chemin.push_back(numOrigine);
	return sommetsSol.at(numDest).first;
}

int Reseau::bellmanFord(unsigned int numOrigine, unsigned int numDest,
		std::vector<unsigned int>& chemin) throw (std::logic_error) {
	std::map<unsigned int, std::pair<unsigned int, unsigned int>> sommets;
	std::map<std::pair<unsigned int, unsigned int>, unsigned int> edges;


	// On initialise a Infini les poids et 0 les predecesseurs
	for (std::pair<unsigned int, liste_arcs> noeud : m_graphe) {
		std::pair<unsigned int, unsigned int> tmp(INFINI, 0);
		sommets.insert(
				std::pair<unsigned int, std::pair<unsigned int, unsigned int>>(
						noeud.first, tmp));
		for (std::pair<unsigned int, std::pair<unsigned int, unsigned int>> adjacents : noeud.second) {
			std::pair<unsigned int, unsigned int> tmpPair(noeud.first,
					adjacents.first);
			edges.insert(
					std::pair<std::pair<unsigned int, unsigned int>,
							unsigned int>(tmpPair, adjacents.second.first));
		}
	}
	sommets.at(numOrigine).first = 0;
	sommets.at(numOrigine).second = numDest;
	for (unsigned int i = 1; i < sommets.size(); i++) {

		for (std::pair<std::pair<unsigned int, unsigned int>, unsigned int> arcs : edges) {

			unsigned int tmp = sommets.at(arcs.first.first).first
					+ this->getCoutArc(arcs.first.first, arcs.first.second);
			if (tmp < sommets.at(arcs.first.second).first) {
				sommets.at(arcs.first.second).first = tmp;
				sommets.at(arcs.first.second).second = arcs.first.first;

			}
		}
	}
	for (std::pair<std::pair<unsigned int, unsigned int>, unsigned int> arcs : edges) {
		if (sommets.at(arcs.first.second).first
				> sommets.at(arcs.first.first).first
						+ this->getCoutArc(arcs.first.first,
								arcs.first.second)) {
			throw std::logic_error("Cycle negatif");
		}
	}
	unsigned int trail = numDest;
	while (trail != numOrigine) {
		chemin.push_back(trail);
		trail = sommets[trail].second;
	}
	chemin.push_back(numOrigine);

	return sommets.at(numDest).first;

}

bool Reseau::estFortementConnexe() const {
	bool booltmp = false;
	std::vector<std::vector<unsigned int>> tmpVect;
	if (this->getComposantesFortementConnexes(tmpVect) == 1){
		booltmp = true;
	}
	return booltmp;
}

int Reseau::getComposantesFortementConnexes(
		std::vector<std::vector<unsigned int>>& composantes) const {
	std::stack<unsigned int> mainStack;
	std::stack<unsigned int> tmpStack;
	std::map<unsigned int,bool> mainVisite;
	std::map<unsigned int, unsigned int> nonVisites;
	Reseau inverse;
	for (std::pair<unsigned int, liste_arcs> element : m_graphe) {
		nonVisites.insert(std::pair<unsigned int, unsigned int>(element.first,element.first));

	}
	while(!nonVisites.empty()){
		//std::cout<< nonVisites.begin()->first << std::endl;
		explore(nonVisites.begin()->first, mainStack, mainVisite);
		tmpStack = mainStack;
		while(!tmpStack.empty()){
			nonVisites.erase(tmpStack.top());
			tmpStack.pop();
		}}

	inverse = this->inversion();
	//On réutilise réinitialise mainVisite
	mainVisite.clear();
	for (std::pair<unsigned int, liste_arcs> element : m_graphe) {
			mainVisite.insert(std::pair<unsigned int, unsigned int>(element.first,false));
		}

	while(!mainStack.empty()){
		if (mainVisite.at(mainStack.top())==true){
			mainStack.pop();

		}
		else{
			std::vector<unsigned int> vecInVec;
			explore(mainStack.top(), tmpStack, mainVisite);
			int stackSize = tmpStack.size();
			for (int i = 0; i<stackSize; i++){
				vecInVec.push_back(tmpStack.top());
				std:: cout << vecInVec.size();
				tmpStack.pop();

			}
			mainStack.pop();
			composantes.push_back(vecInVec);
			vecInVec.clear();


		}
	}



	return composantes.size();
}

void Reseau::explore(unsigned int numOrigine, std::stack<unsigned int>& stack, std::map<unsigned int,bool>& visite) const {

	std::map<unsigned int, int> debut;
	std::map<unsigned int, int> fin;

	int clock = 0;
	for (std::pair<unsigned int, liste_arcs> noeud : m_graphe) {
		visite.insert(std::pair<unsigned int, bool>(noeud.first, false));
		debut.insert(std::pair<unsigned int, int>(noeud.first, 0));
		fin.insert(std::pair<unsigned int, int>(noeud.first, 0));
	}

	visite.at(numOrigine) = true;
	debut.at(numOrigine) = clock;
	clock += 1;
	for (std::pair<unsigned int, std::pair<unsigned int, unsigned int>> adjacents : m_graphe.at(
			numOrigine)) {
		if (visite.at(adjacents.first) == false) {
			this->explore(adjacents.first, stack, visite);

		}
	}
	fin.at(numOrigine) = clock;
	clock += 1;
	stack.push(numOrigine);


}

Reseau Reseau::inversion() const{
	Reseau reseauInverse;
	for (std::pair<unsigned int, liste_arcs> noeud : m_graphe){
		reseauInverse.ajouterSommet(noeud.first);
	}
	for (std::pair<unsigned int, liste_arcs> noeud : m_graphe){
		for (std::pair< unsigned int,std::pair<unsigned int,unsigned int>> arcs : m_graphe.at(noeud.first)){
			reseauInverse.ajouterArc(arcs.first, noeud.first, arcs.second.first, arcs.second.second);
		}
	}
	return reseauInverse;
}

/*
 * reseau.cpp
 *
 *  Created on: 2016-11-03
 *      Author: etudiant
 */

