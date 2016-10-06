#include "Voyage.h"


/**
 * \brief Constructeur de voyages avec paramètres
 * \param[in] ligne_gtfs == Un vecteur de string comportant les informations du txt des voyages
 */
Voyage::Voyage(const std::vector<std::string>& ligne_gtfs, Ligne* p_ligne):
	m_id(ligne_gtfs[2]),
	m_ligne(p_ligne),
	m_service_id(ligne_gtfs[1]),
	m_destination(ligne_gtfs[3]),
	m_arrets()

{

}
/**
 * \brief Méthode permettant de récupérer les arrêts affectés à une station
 * \param[in] p_num_station == Numéro de la station dont on cherche les arrêts
 * \return Les arrêts de la station
 */
Arret& Voyage::arretDeLaStation(unsigned int p_num_station) {

	int identifiant;

	for (unsigned i = 0; i<m_arrets.size(); i++)
	{
		if (m_arrets[i].getStationId() == p_num_station)
		{
			identifiant = i;
		}
	}
	return m_arrets[identifiant];
}

/**
 * \brief Méthode accesseur récupérant les arrêts du voyage
 * \return Les arrêts sous forme de vecteur
 */
std::vector<Arret> Voyage::getArrets() const {

	return m_arrets;
}

/**
 * \brief Méthode accesseur récupérant la destinations du voyage
 * \return La destination sous forme de string
 */
const std::string& Voyage::getDestination() const {

	return m_destination;
}

/**
 * \brief Méthode permettant de modifier la destination du voyage
 * \param[in] p_destination == destination qui remplace la destination de l'objet courant
 */
void Voyage::setDestination(const std::string& p_destination) {

	m_destination = p_destination;
}

/**
 * \brief Méthode accesseur récupérant l'id du voyage
 * \return L'id du voyage sous forme de string
 */
std::string Voyage::getId() const {

	return m_id;
}

/**
 * \brief Méthode permettant de modifier l'id du voyage
 * \param[in] p_id == l'id qui remplace celle de l'objet courant
 */
void Voyage::setId(std::string p_id) {

	m_id = p_id;
}


/**
 * \brief Méthode accesseur récupérant la ligne du voyage
 * \return La ligne du voyage
 */

Ligne* Voyage::getLigne() const {

	return m_ligne;
}

/**
 * \brief Méthode permettant de modifier la ligne du voyage
 * \param[in] p_ligne == la ligne qui remplace celle de l'objet courant
 */
void Voyage::setLigne(Ligne* p_ligne) {

	m_ligne = p_ligne;
}

/**
 * \brief Méthode accesseur récupérant l'id de service du voyage
 * \return L'id de service de la ligne sous forme de string
 */
std::string Voyage::getServiceId() const {

	return m_service_id;
}

/**
 * \brief Méthode permettant de modifier la ligne du voyage
 * \param[in] p_service_id == L'id qui remplace celle de l'objet courant
 */
void Voyage::setServiceId(std::string p_service_id) {

	m_service_id = p_service_id;
}

/**
 * \brief Méthode accesseur récupérant l'heure de départ du voyage
 * \return L'heure de départ du voyage
 */
Heure Voyage::getHeureDepart() const {

	return m_arrets[0].getHeureDepart();
}
/**
 * \brief Méthode accesseur récupérant l'heure de fin du voyage
 * \return L'heure de fin du voyage
 */
Heure Voyage::getHeureFin() const {

	int derniereCase = (m_arrets.size() - 1);

	return m_arrets[derniereCase].getHeureArrivee();
}

/**
 * \brief Méthode permettant de modifier la ligne du voyage
 * \param[in] resultat == Le vecteur d'arrets qui remplace celui de l'objet courant
 */
void Voyage::setArrets(std::vector<Arret>& resultat) {

	m_arrets = resultat;
	std::sort(m_arrets.begin(),m_arrets.end());
	Heure changeHeure;
	if (m_arrets.size() > 1)
	{
	for (unsigned i = 1; i < m_arrets.size(); i++)
	{
		if (m_arrets[i-1].getHeureDepart() == m_arrets[i].getHeureDepart())
		{
			changeHeure = m_arrets[i].getHeureDepart().add_secondes(30);
			m_arrets[i].setHeureDepart(changeHeure);
			changeHeure = m_arrets[i].getHeureArrivee().add_secondes(30);
			m_arrets[i].setHeureArrivee(changeHeure);
		}
	}
	}

}
/**
 * \brief Méthode de surcharge de comparateur "Plus petit que" entre deux voyages en se basant sur l'heure de départ
 * \param[in] p_other == Deuxième arret à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */
bool Voyage::operator <(const Voyage& p_other) const {

	return this->getHeureDepart()<p_other.getHeureDepart();
}

/**
 * \brief Méthode de surcharge de comparateur "Plus grand que" entre deux voyages en se basant sur l'heure de départ
 * \param[in] p_other == Deuxième arret à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */
bool Voyage::operator >(const Voyage& p_other) const {

	return this->getHeureDepart()>p_other.getHeureDepart();
}

/**
 * \brief Méthode de surcharge qui implante le format de l'opérateur <<
 * \param[in] flux == ostream où sera envoyé les informations formatés
 * \param[in] p_voyages == Voyage qui doit être envoyé dans le ostream
 * \return le contenu du ostream
 */
std::ostream & operator<<(std::ostream & flux, const Voyage & p_voyage)
{
	flux << p_voyage.getLigne()->getNumero() << ": Vers" << p_voyage.getDestination();

	return flux;
}
/*
 * voyage.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




