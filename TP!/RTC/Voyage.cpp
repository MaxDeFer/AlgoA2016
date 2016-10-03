#include "Voyage.h"

Voyage::Voyage(const std::vector<std::string>& ligne_gtfs, Ligne* p_ligne):
	m_id(ligne_gtfs[2]),
	m_ligne(p_ligne),
	m_service_id(ligne_gtfs[1]),
	m_destination(ligne_gtfs[3]),
	m_arrets()

{

}

Arret& Voyage::arretDeLaStation(unsigned int p_num_station) {

	int identifiant;

	for (int i = 0; i<m_arrets.size(); i++)
	{
		if (m_arrets[i].getStationId() == p_num_station)
		{
			identifiant = i;
		}
	}
	return m_arrets[identifiant];
}

std::vector<Arret> Voyage::getArrets() const {

	return m_arrets;
}

const std::string& Voyage::getDestination() const {

	return m_destination;
}

void Voyage::setDestination(const std::string& p_destination) {

	m_destination = p_destination;
}

std::string Voyage::getId() const {

	return m_id;
}

void Voyage::setId(std::string p_id) {

	m_id = p_id;
}

Ligne* Voyage::getLigne() const {

	return m_ligne;
}

void Voyage::setLigne(Ligne* p_ligne) {

	m_ligne = p_ligne;
}

std::string Voyage::getServiceId() const {

	return m_service_id;
}

void Voyage::setServiceId(std::string p_service_id) {

	m_service_id = p_service_id;
}

Heure Voyage::getHeureDepart() const {

	return m_arrets[0].getHeureDepart();
}

Heure Voyage::getHeureFin() const {

	int derniereCase = (m_arrets.size() - 1);

	return m_arrets[derniereCase].getHeureArrivee();
}

void Voyage::setArrets(std::vector<Arret>& resultat) {

	m_arrets = resultat;
	std::sort(m_arrets.begin(),m_arrets.end());

	for (int i = 0; i < m_arrets.size() - 2; i++)
	{
		if (m_arrets[i].getHeureDepart() == m_arrets[i+1].getHeureDepart())

		{
			m_arrets[i+1].setHeureDepart((m_arrets[i+1].getHeureDepart()).add_secondes(30));

		}

		if (m_arrets[i].getHeureArrivee() == m_arrets[i+1].getHeureArrivee())
		{
			m_arrets[i+1].setHeureArrivee((m_arrets[i+1].getHeureArrivee()).add_secondes(30));
		}
	}
}

bool Voyage::operator <(const Voyage& p_other) const {

	return this->getHeureDepart()<p_other.getHeureDepart();
}

bool Voyage::operator >(const Voyage& p_other) const {

	return this->getHeureDepart()>p_other.getHeureDepart();
}
/*
 * voyage.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




