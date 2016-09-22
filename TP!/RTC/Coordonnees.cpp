/*
 * coordonnee.cpp
 *
 *  Created on: 2016-09-14
 *      Author: etudiant
 */


#include <iostream>
#include "Coordonnees.h"

Coordonnees::Coordonnees(double latitude, double longitude):
m_latitude(latitude),
m_longitude(longitude)
{

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
	bool isValide = false;
	if (p_latitude <= 90 && p_latitude >= 0 && p_longitude >= -180 && p_latitude <= 180 )
	{
		isValide = true;
	}
	return isValide;
}

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

std::ostream & operator<<(std::ostream & flux, const Coordonnees & p_coord)
{
	flux << "( " << p_coord.getLatitude() << ", " << p_coord.getLongitude() << " )";
	return flux;
}
