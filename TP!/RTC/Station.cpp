
#include "Station.h"
#include <cstdlib>

Station::Station(const std::vector<std::string>& ligne_gtfs):
m_id(std::stoi(ligne_gtfs[0])),
m_nom(ligne_gtfs[1]),
m_description(ligne_gtfs[2]),
m_coords(std::stod(ligne_gtfs[3]),std::stod(ligne_gtfs[4])),
m_voyages_passants(){


}

const Coordonnees& Station::getCoords() const {

	return m_coords;
}

void Station::setCoords(const Coordonnees& coords) {

	this->m_coords = coords;
}

const std::string& Station::getDescription() const {

	return m_description;
}

void Station::setDescription(const std::string& description) {

	this->m_description = description;
}

std::vector<Ligne*> Station::getLignesPassantes() const {

	std::vector<Ligne*> totalLignes;
	for (int i = 0; i < this->m_voyages_passants.size(); i++)
	{
		totalLignes.push_back(this->m_voyages_passants[i]->getLigne());
	}

	return totalLignes;

}

const std::string& Station::getNom() const {

	return m_nom;
}

void Station::setNom(const std::string& nom) {

	this->m_nom = nom;
}

unsigned int Station::getId() const {

	return m_id;
}

void Station::setId(unsigned int stationId) {

	this->m_id = stationId;
}

const std::vector<Voyage*>& Station::getVoyagesPassants() const {

	return this->m_voyages_passants;
}

void Station::addVoyage(Voyage* ptr_voyage) {

	this->m_voyages_passants.push_back(ptr_voyage);
}

double Station::distance(const Station& p_station) const {

	return this->m_coords-p_station.getCoords();
}
/*
 * station.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




