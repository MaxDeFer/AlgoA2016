Station::Station(const std::vector<std::string>& ligne_gtfs) {
}

const Coordonnees& Station::getCoords() const {
}

void Station::setCoords(const Coordonnees& coords) {
}

const std::string& Station::getDescription() const {
}

void Station::setDescription(const std::string& description) {
}

std::vector<Ligne*> Station::getLignesPassantes() const {
}

const std::string& Station::getNom() const {
}

void Station::setNom(const std::string& nom) {
}

unsigned int Station::getId() const {
}

void Station::setId(unsigned int stationId) {
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




