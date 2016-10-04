
#include "Station.h"
#include <cstdlib>



/**
 * \brief Constructeur de Station avec paramètres
 * \param[in] ligne_gtfs == Un vecteur de string comportant les informations du txt des stations
 */
Station::Station(const std::vector<std::string>& ligne_gtfs):
m_id(std::stoi(ligne_gtfs[0])),
m_nom(ligne_gtfs[1]),
m_description(ligne_gtfs[2]),
m_coords(std::stod(ligne_gtfs[3]),std::stod(ligne_gtfs[4])),
m_voyages_passants(){


}

/**
 * \brief Méthode accesseur récupérant les coordonnées de la sation
 * \return Les coordonnées de la station
 */
const Coordonnees& Station::getCoords() const {

	return m_coords;
}

/**
 * \brief Méthode servant à modifier les coordonnées de la station
 * \param[in] coords == La coordonnée qui remplacera celle d'origine
 */
void Station::setCoords(const Coordonnees& coords) {

	this->m_coords = coords;
}

/**
 * \brief Méthode accesseur récupérant la description de la station
 * \return La description de la station
 */
const std::string& Station::getDescription() const {

	return m_description;
}

/**
 * \brief Méthode servant à modifier la description de la station
 * \param[in] description == La description qui remplacera celle d'origine
 */
void Station::setDescription(const std::string& description) {

	this->m_description = description;
}

/**
 * \brief Méthode accesseur récupérant les lignes passantes à la station
 * \return Le vecteur de de lignes passantes à la station
 */
std::vector<Ligne*> Station::getLignesPassantes() const {

	std::vector<Ligne*> totalLignes;
	for (unsigned i = 0; i < this->m_voyages_passants.size(); i++)
	{
		totalLignes.push_back(this->m_voyages_passants[i]->getLigne());
	}

	return totalLignes;

}

/**
 * \brief Méthode accesseur récupérant le nom de la station
 * \return Le nom de la station sous forme de string
 */
const std::string& Station::getNom() const {

	return m_nom;
}


/**
 * \brief Méthode servant à modifier la description de la station
 * \param[in] nom == Le nom qui remplacera celle d'origine
 */
void Station::setNom(const std::string& nom) {

	this->m_nom = nom;
}

/**
 * \brief Méthode accesseur récupérant l'id de la station
 * \return L'id de la station sous forme de unsigned int
 */
unsigned int Station::getId() const {

	return m_id;
}

/**
 * \brief Méthode servant à modifier l'id de la station
 * \param[in] sationId == L'id qui remplacera celle d'origine
 */
void Station::setId(unsigned int stationId) {

	this->m_id = stationId;
}

/**
 * \brief Méthode accesseur récupérant les voyages passants à la station
 * \return Le vecteur de voyages passants à la station
 */
const std::vector<Voyage*>& Station::getVoyagesPassants() const {

	return this->m_voyages_passants;
}
/**
 * \brief Méthode servant à ajouter un voyage au groupe de voyage
 * \param[in] ptr_voyage == voyage qui sera ajouté au vecteur de voyages
 */
void Station::addVoyage(Voyage* ptr_voyage) {

	this->m_voyages_passants.push_back(ptr_voyage);
}

/**
 * \brief Méthode servant à ajouter un voyage au groupe de voyage
 * \param[in] p_station == Station avec laquelle on cherche la distance
 * \return La distance entre deux stations sous forme de double
 */
double Station::distance(const Station& p_station) const {

	return this->m_coords-p_station.getCoords();
}
/**
 * \brief Méthode de surcharge qui implante le format de l'opérateur <<
 * \param[in] f == ostream où sera envoyé les informations formatés
 * \param[in] p_station == Station qui doit être envoyé dans le ostream
 * \return le contenu du ostream
 */
std::ostream & operator<<(std::ostream& flux, const Station& p_station)
{
	flux << p_station.getId() << " - " << p_station.getDescription();

	return flux;
}


/*
 * station.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




