#include "Arret.h"


/**
 * \brief Constructeur d'Arret avec paramètres
 * \param[in] ligne_gtfs == Un vecteur de string comportant les informations contenus dans stop.txt
 */

Arret::Arret(const std::vector<std::string>& ligne_gtfs):
		m_station_id(std::stoi(ligne_gtfs[3])),
		m_heure_arrivee(Heure(std::stoi(ligne_gtfs[1].substr(0,2)),std::stoi(ligne_gtfs[1].substr(3,2)), std::stoi(ligne_gtfs[1].substr(6,2)))),
		m_heure_depart(Heure(std::stoi(ligne_gtfs[2].substr(0,2)),std::stoi(ligne_gtfs[2].substr(3,2)), std::stoi(ligne_gtfs[2].substr(6,2)))),
		m_numero_sequence(std::stoi(ligne_gtfs[3])),
		m_numero_sequence(std::stoi(ligne_gtfs[4])),
		m_voyage_id(ligne_gtfs[0])
		{

/**
 * \brief Méthode accesseur récupérant l'heure d'arrivée
 * \return L'Heure d'arrivée
 */
const Heure& Arret::getHeureArrivee() const {

	return m_heure_arrivee;
}

/**
 * \brief Méthode permettant la modification de l'heure d'arriée
 * \param[in] p_heureArrivee == Nouvelle heure à attitrer à m_heure_arrivee
 */
void Arret::setHeureArrivee(const Heure& p_heureArrivee) {

	m_heure_arrivee = p_heureArrivee;
}

/**
 * \brief Méthode accesseur récupérant l'heure de départ
 * \return L'Heure de départ
 */
const Heure& Arret::getHeureDepart() const {

	return m_heure_depart;
}

/**
 * \brief Méthode permettant la modification de l'heure de départ
 * \param[in] p_heureDepart == Nouvelle heure à attitrer à m_heure_depart
 */
void Arret::setHeureDepart(const Heure& p_heureDepart) {

	m_heure_depart = p_heureDepart;
}

/**
 * \brief Méthode accesseur récupérant le numéro de séquence de l'arret
 * \return Le numéro de séquence de l'arret
 */
unsigned int Arret::getNumeroSequence() const {

	return m_numero_sequence;
}

/**
 * \brief Méthode permettant la modification du numéro de séquence
 * \param[in] p_numeroSequence == Nouvelle valeur à attitrer à m_numero_sequence
 */
void Arret::setNumeroSequence(unsigned int p_numeroSequence) {

	m_numero_sequence = p_numeroSequence;
}

/**
 * \brief Méthode accesseur récupérant l'id de la station de l'arrêt
 * \return Le l'id de la station de l'arret
 */

unsigned int Arret::getStationId() const {

	return m_station_id;
}

/**
 * \brief Méthode permettant la modification de l'id de la station de l'arret
 * \param[in] stationId == Nouvelle valeur à attitrer à m_station_id
 */

void Arret::setStationId(unsigned int stationId) {

	m_station_id = stationId;
}

/**
 * \brief Méthode accesseur récupérant l'id du voyage de l'arrêt
 * \return Le l'id du voyage de l'arret
 */
std::string Arret::getVoyageId() const {

	return m_voyage_id;
}

/**
 * \brief Méthode permettant la modification de l'id du voyage de l'arret
 * \param[in] voyageId == Nouvelle valeur à attitrer à m_voyage_id
 */
void Arret::setVoyageId(const std::string& voyageId) {

	m_voyage_id = voyageId;
}

/**
 * \brief Méthode de surcharge de comparateur "Plus petit que" entre deux arrets
 * \param[in] p_other == Deuxième arret à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */

bool Arret::operator <(const Arret& p_other) const {

	if (m_numero_sequence < p_other.getNumeroSequence()){
		return true;
	}
	else{
		return false;
	}
}

/**
 * \brief Méthode de surcharge de comparateur "Plus grand que" entre deux arrets
 * \param[in] p_other == Deuxième arret à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */
bool Arret::operator >(const Arret& p_other) const {

	if (m_numero_sequence > p_other.getNumeroSequence()){
		return true;
	}
	else{
		return false;
	}

}

/**
 * \brief Méthode de surcharge qui implante le format de l'opérateur <<
 * \param[in] f == ostream où sera envoyé les informations formatés
 * \param[in] p_arret == Arret qui doit être envoyé dans le ostream
 * \return le contenu du ostream
 */
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




