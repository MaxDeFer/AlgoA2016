#include "Ligne.h"
#include <iostream>

Ligne::Ligne(const std::vector<std::string>& ligne_gtfs):
m_id(atoi(ligne_gtfs[0].c_str())),
m_numero(ligne_gtfs[2]),
m_description(ligne_gtfs[4]),
m_categorie(couleurToCategorie(ligne_gtfs[7])),
m_voyages()
{

}

CategorieBus Ligne::couleurToCategorie(std::string couleur) {
	CategorieBus tmp;
	if (couleur == "97BF0D"){
		tmp=CategorieBus::METRO_BUS;
	}
	if (couleur == "013888"){
		tmp=CategorieBus::LEBUS;
	}
	if (couleur == "E04503"){
		tmp=CategorieBus::EXPRESS;
	}
	if (couleur == "1A171B" || couleur == "003888"){
		tmp=CategorieBus::COUCHE_TARD;
	}
	return tmp;
}

std::string Ligne::categorieToString(CategorieBus c) {
	std::string tmp;
	if (c == CategorieBus::COUCHE_TARD){
		tmp="COUCHE_TARD";
	}
	else if (c == CategorieBus::EXPRESS){
		tmp="EXPRESS";
	}
	else if (c == CategorieBus::LEBUS){
		tmp="LEBUS";
	}
	else if (c == CategorieBus::METRO_BUS){
		tmp="METRO_BUS";
	}
	else{
		tmp="fuck";
	}
	return tmp;
}

CategorieBus Ligne::getCategorie() const {

	return m_categorie;
}

void Ligne::setCategorie(CategorieBus categorie) {

	m_categorie = categorie;
}

std::pair<std::string, std::string> Ligne::getDestinations() const {

	std::string depart = "";
	std::string destination = "";
	bool splitTest = false;
	for (unsigned i=0; i<m_description.size()+3; i++){
		if (!splitTest){
			depart += m_description[i];
			if (m_description[i+1]==' ' && m_description[i+2]=='-' && m_description[i+3]){
				splitTest=true;
			}

		}
		else{
			destination += m_description[i+3];
		}


	}
	std::pair<std::string, std::string> pair(depart, destination);
	return  pair;

}

unsigned int Ligne::getId() const {

	return m_id;
}

void Ligne::setId(unsigned int id) {

	m_id = id;
}

const std::string& Ligne::getNumero() const {

	return m_numero;
}

void Ligne::setNumero(const std::string& numero) {

	m_numero = numero;
}

const std::vector<Voyage*>& Ligne::getVoyages() const {

	return m_voyages;
}

void Ligne::setVoyages(const std::vector<Voyage*>& voyages) {

	m_voyages = voyages;
}

void Ligne::addVoyage(Voyage* ptr_voyage) {

	m_voyages.push_back(ptr_voyage);
}

const std::string& Ligne::getDescription() const {

	return m_description;
}

void Ligne::setDescription(const std::string& description) {

	m_description = description;


}

std::ostream & operator<<(std::ostream& f, const Ligne& p_ligne)
{
	f << p_ligne.categorieToString(p_ligne.getCategorie()) << " " << p_ligne.getNumero();
	f << " : " << p_ligne.getDescription() << std::endl;

	return f;
}
/*
 * ligne.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




