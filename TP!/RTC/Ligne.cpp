#include "Ligne.h"

Ligne::Ligne(const std::vector<std::string>& ligne_gtfs):
m_id(std::stoi(ligne_gtfs[0])),
m_numero(ligne_gtfs[2]),
m_description(ligne_gtfs[4]),
m_categorie(couleurToCategorie(ligne_gtfs[4])),
m_voyages()
{

}

CategorieBus Ligne::couleurToCategorie(std::string couleur) {
	CategorieBus tmp;
	if (couleur == "97BF0D"){
		tmp=CategorieBus::METRO_BUS;
	}
	if (couleur == "013888"){
		tmp=CategorieBus::METRO_BUS;
	}
	if (couleur == "E04503"){
		tmp=CategorieBus::METRO_BUS;
	}
	if (couleur == "1A171B" && couleur == "003888"){
		tmp=CategorieBus::METRO_BUS;
	}
	return tmp;
}

std::string Ligne::categorieToString(CategorieBus c) {
	std::string tmp;
	if (c == CategorieBus::COUCHE_TARD){
		tmp="COUCHE_TARD";
	}
	if (c == CategorieBus::EXPRESS){
		tmp="EXPRESS";
	}
	if (c == CategorieBus::LEBUS){
		tmp="LEBUS";
	}
	if (c == CategorieBus::METRO_BUS){
		tmp="METRO_BUS";
	}
	return tmp;
}

CategorieBus Ligne::getCategorie() const {

}

void Ligne::setCategorie(CategorieBus categorie) {
}

std::pair<std::string, std::string> Ligne::getDestinations() const {
}

unsigned int Ligne::getId() const {
}

void Ligne::setId(unsigned int id) {
}

const std::string& Ligne::getNumero() const {
}

void Ligne::setNumero(const std::string& numero) {
}

const std::vector<Voyage*>& Ligne::getVoyages() const {
}

void Ligne::setVoyages(const std::vector<Voyage*>& voyages) {
}

void Ligne::addVoyage(Voyage* ptr_voyage) {
}

const std::string& Ligne::getDescription() const {
}

void Ligne::setDescription(const std::string& description) {
}
/*
 * ligne.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




