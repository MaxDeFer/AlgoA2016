/*
 * coordonnee.cpp
 *
 *  Created on: 2016-09-14
 *      Author: etudiant
 */

#include <string>
#include <sstream>
#include "Coordonnees.h"

Coordonnees::Coordonnees(double latitude, double longitude)
{
	this->m_latitude = latitude;
	this->m_longitude = longitude;

}


double Coordonnees::getLatitude() const
{
	return this->m_latitude;
}

void Coordonnees::setLatitude(double latitude)
{
	this->m_latitude = latitude;
}

double Coordonnees::getLongitude() const
{
	return this->m_longitude;
}

void Coordonnees::setLongitude(double longitude)
{
	this->m_longitude = longitude;
}

static bool is_valide_coord(double p_latitude, double p_longitude)
{
	
}