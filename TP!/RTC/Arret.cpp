#include "Arret.h"


/**
 * \brief Constructeur d'Arret avec paramètres
 * \param[in] ligne_gtfs == Un vecteur de string comportant les informations contenus dans stop
 * \pre p_nom est dans un format valide
 * \pre p_volume est dans un format valide
 * \pre p_numero est dans un format valide
 * \pre p_page est dans un format valide
 * \post m_nom prend la valeur de p_nom
 * \post m_volume prend la valeur de p_volume
 * \post m_numero prend la valeur de p_numero
 * \post m_page prend la valeur de p_page
 */

Arret::Arret(const std::vector<std::string>& ligne_gtfs):
		m_station_id(std::stoi(ligne_gtfs[0])),
		m_heure_arrivee(Heure(std::stoi(ligne_gtfs[1].substr(0,2)),std::stoi(ligne_gtfs[1].substr(3,2)), std::stoi(ligne_gtfs[1].substr(6,2)))),
		m_heure_depart(Heure(std::stoi(ligne_gtfs[2].substr(0,2)),std::stoi(ligne_gtfs[2].substr(3,2)), std::stoi(ligne_gtfs[2].substr(6,2)))),
		m_numero_sequence(std::stoi(ligne_gtfs[3])),
		m_voyage_id()
		{

}

const Heure& Arret::getHeureArrivee() const {

	return m_heure_arrivee;
}

void Arret::setHeureArrivee(const Heure& p_heureArrivee) {

	m_heure_arrivee = p_heureArrivee;
}

const Heure& Arret::getHeureDepart() const {

	return m_heure_depart;
}

void Arret::setHeureDepart(const Heure& p_heureDepart) {

	m_heure_depart = p_heureDepart;
}

unsigned int Arret::getNumeroSequence() const {

	return m_numero_sequence;
}

void Arret::setNumeroSequence(unsigned int p_numeroSequence) {

	m_numero_sequence = p_numeroSequence;
}

unsigned int Arret::getStationId() const {

	return m_station_id;
}

void Arret::setStationId(unsigned int stationId) {

	m_station_id = stationId;
}

std::string Arret::getVoyageId() const {

	return m_voyage_id;
}

void Arret::setVoyageId(const std::string& voyageId) {

	m_voyage_id = voyageId;
}

bool Arret::operator <(const Arret& p_other) const {

	if (m_numero_sequence < p_other.getNumeroSequence()){
		return true;
	}
	else{
		return false;
	}
}

bool Arret::operator >(const Arret& p_other) const {

	if (m_numero_sequence > p_other.getNumeroSequence()){
		return true;
	}
	else{
		return false;
	}

}

std::ostream & operator<<(std::ostream& f, const Arret& p_arret)
{
	f << p_arret.getHeureArrivee() <<  " - " << p_arret.getStationId();

	return f;
}
/*
 * arret.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




