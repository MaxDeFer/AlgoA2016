#include "Station.h"

Station::Station(const std::vector<std::string>& ligne_gtfs):
m_id(ligne_gtfs[0]),
m_nom(ligne_gtfs[1]),
m_description(ligne_gtfs[2]),
m_coords(Coordonnees(atof(ligne_gtfs[3]),atof(ligne_gtfs[4]))) {
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

	/* TODO */
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
}

void Station::addVoyage(Voyage* ptr_voyage) {
}

double Station::distance(const Station& p_station) const {
}
/*
 * station.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




