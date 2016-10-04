/*
 * coordonnee.cpp
 *
 *  Created on: 2016-09-14
 *      Author: etudiant
 */


#include <iostream>
#include "Coordonnees.h"


/**
 * \brief Constructeur de coordonnées avec paramètre
 * \param[in] latitude == Latitude correspondante à la coordonnée
 * \param[in] longitude == Longitude correspondante
 */
Coordonnees::Coordonnees(double latitude, double longitude):
m_latitude(latitude),
m_longitude(longitude)
{

}

/**
 * \brief Méthode accesseur récupérant la latitude
 * \return Latitude de la coordonnée
 */
double Coordonnees::getLatitude() const
{
	return this->m_latitude;
}

/**
 * \brief Méthode permettant la modification de la latitude
 * \param[in] latitude == Nouvelle latitude à attitrer à m_latitude
 */
void Coordonnees::setLatitude(double latitude)
{
	this->m_latitude = latitude;
}

/**
 * \brief Méthode accesseur récupérant la longitude
 * \return Longitude de la coordonnée
 */
double Coordonnees::getLongitude() const
{
	return this->m_longitude;
}


/**
 * \brief Méthode permettant la modification de la latitude
 * \param[in] longitude == Nouvelle latitude à attitrer à m_longitude
 */
void Coordonnees::setLongitude(double longitude)
{
	this->m_longitude = longitude;
}

/**
 * \brief Méthode permettant de vérifier si une coordonnée est valide
 * \param[in] m_longitude == Longitude de la coordonée à tester.
 * \param[in] m_latitude == Longitude de la coordonée à tester.
 * \return Un booléen true si le coordonnée est valide, false sinon.
 */
static bool is_valide_coord(double p_latitude, double p_longitude)
{
	bool isValide = false;
	if (p_latitude <= 90 && p_latitude >= 0 && p_longitude >= -180 && p_latitude <= 180 )
	{
		isValide = true;
	}
	return isValide;
}

/**
 * \brief Méthode de surcharge de soustraction entre deux coordonnées pour calculer la distance
 * \param[in] p_other == Deuxième arret à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */
double Coordonnees::operator- (const Coordonnees & other) const
{
	const double PI = 3.141592653589793;
	double distance;
	double thisLong = this->getLongitude();
	double thisLat = this->getLatitude()*PI/180;
	double otherLong = other.getLongitude()*PI/180;
	double otherLat = other.getLatitude()*PI/180;
	distance = 2*6371*(asin(sqrt(pow(sin((otherLat-thisLat)/2)+cos(thisLat)*cos(otherLat),2)*(pow(sin((otherLong-thisLong)/2),2)))));
	return distance;
}

/**
 * \brief Méthode de surcharge qui implante le format de l'opérateur <<
 * \param[in] flux == ostream où sera envoyé les informations formatés
 * \param[in] p_coord == Coordonnée qui doit être envoyé dans le ostream
 * \return le contenu du ostream
 */
std::ostream & operator<<(std::ostream & flux, const Coordonnees & p_coord)
{
	flux << "( " << p_coord.getLatitude() << ", " << p_coord.getLongitude() << " )";
	return flux;
}
