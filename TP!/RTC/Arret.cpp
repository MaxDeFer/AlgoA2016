#include "Arret.h"

Arret::Arret(const std::vector<std::string>& ligne_gtfs):
		m_station_id(stoi(ligne_gtfs[0])),
		m_heure_arrivee(ligne_gtfs[1]),
		m_heure_depart(ligne_gtfs[2]),
		m_numero_sequence(stoi(ligne_gtfs[3])),
		m_voyage_id()
		{

}

const Heure& Arret::getHeureArrivee() const {
}

void Arret::setHeureArrivee(const Heure& p_heureArrivee) {
}

const Heure& Arret::getHeureDepart() const {
}

void Arret::setHeureDepart(const Heure& p_heureDepart) {
}

unsigned int Arret::getNumeroSequence() const {
}

void Arret::setNumeroSequence(unsigned int p_numeroSequence) {
}

unsigned int Arret::getStationId() const {
}

void Arret::setStationId(unsigned int stationId) {
}

std::string Arret::getVoyageId() const {
}

void Arret::setVoyageId(const std::string& voyageId) {
}

bool Arret::operator <(const Arret& p_other) const {
}

bool Arret::operator >(const Arret& p_other) const {
}
/*
 * arret.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




