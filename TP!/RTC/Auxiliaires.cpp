#include "Auxiliaires.h"

std::vector<std::string> split(const std::string& s, char delim) {

	std::vector<std::string> vecteurRetour;
	std::string buffer;
	std::stringstream ss;
	ss.str(s);
	while (std::getline(ss, buffer, delim))
	{
		vecteurRetour.push_back(buffer);
	}

	return vecteurRetour;

}

void lireFichier(std::string nomFichier,
		std::vector<std::vector<std::string> >& resultats, char delimiteur,
		bool rm_entete) {

	std::vector<std::string> vecteurLigne;
	std::string buffer;
	std::ifstream fichier;

	try
	{
		fichier.open(nomFichier);

		if (rm_entete)
		{
			std::getline(fichier,buffer);
		}

		while (std::getline(fichier,buffer))
		{
			resultats.push_back(split(buffer,delimiteur));
		}

		fichier.close();
	}

	catch (std::exception& e)
	{
		std::cout<<"Impossible d'ouvrir le fichier:"<<e.what()<<std::endl;
	}
}

Date::Date():m_an(1900), m_mois(1), m_jour(1) {
}

Date::Date(unsigned int an, unsigned int mois, unsigned int jour):m_an(an), m_mois(mois), m_jour(jour) {
}

bool Date::operator ==(const Date& other) const {

	bool estEgal = 0;

	if (this->m_an == other.m_an &&
		this->m_mois == other.m_mois &&
		this->m_jour == other.m_jour)
	{
		estEgal = 1;
	}

	return estEgal;
}

bool Date::operator <(const Date& other) const {

	bool estPPetit = 0;

	if (this->m_an < other.m_an)
	{
		estPPetit = 1;
	}

	if (this->m_an == other.m_an &&
		this->m_mois < other.m_mois)
	{
		estPPetit = 1;
	}

	if (this->m_an == other.m_an &&
		this->m_mois == other.m_mois &&
		this->m_jour < other.m_jour)
	{
		estPPetit = 1;
	}

	return estPPetit;
}

bool Date::operator >(const Date& other) const {

	bool estPGrand = 0;

	if (this->m_an > other.m_an)
	{
		estPGrand = 1;
	}

	if (this->m_an == other.m_an &&
		this->m_mois > other.m_mois)
	{
		estPGrand = 1;
	}

	if (this->m_an == other.m_an &&
		this->m_mois == other.m_mois &&
		this->m_jour > other.m_jour)
	{
		estPGrand = 1;
	}

	return estPGrand;
}

std::ostream & operator<<(std::ostream & flux, const Date & p_date)
{
	flux << p_date.m_an << "/" << p_date.m_mois << "/" << p_date.m_jour;

	return flux;
}

Heure::Heure():m_heure(0), m_min(0), m_sec(0) {
}

Heure::Heure(unsigned int heure, unsigned int min, unsigned int sec):m_heure(heure), m_min(min), m_sec(sec)  {
}

Heure Heure::add_secondes(unsigned int secs) const {
	unsigned int nouvelleHeure;
	unsigned int nouvelleMin;
	unsigned int nouvelleSec;

	nouvelleSec = this->m_sec + secs;

	if (nouvelleSec > 59)
	{
		nouvelleMin = nouvelleSec/60 + this->m_min;
		nouvelleSec = nouvelleSec%60;
	}
	if (nouvelleMin > 59)
	{
		nouvelleHeure = nouvelleMin/60 + this->m_heure;
		nouvelleMin = nouvelleMin%60;
	}
	if (nouvelleHeure > 29)
	{
		nouvelleHeure = nouvelleHeure%30;
	}
	return Heure(nouvelleHeure, nouvelleMin, nouvelleSec);
}

bool Heure::operator ==(const Heure& other) const {
	bool vrai = 0;
			if (this->m_heure == other.m_heure &&
				this->m_min == other.m_min &&
				this->m_sec == other.m_sec)
			{
				vrai = 1;
			}
	return vrai;
}

bool Heure::operator <(const Heure& other) const {
	bool vrai = 0;

	if (this->m_heure < other.m_heure)
	{
		vrai = 1;
	}

	if (this->m_heure == other.m_heure &&
		this->m_min < other.m_min)
	{
		vrai = 1;
	}

	if (this->m_heure == other.m_heure &&
		this->m_min == other.m_min &&
		this->m_sec < other.m_sec)
	{
		vrai = 1;
	}
	return vrai;
}

bool Heure::operator >(const Heure& other) const {
	bool vrai = 0;

		if (this->m_heure > other.m_heure)
		{
			vrai = 1;
		}

		if (this->m_heure == other.m_heure &&
			this->m_min > other.m_min)
		{
			vrai = 1;
		}

		if (this->m_heure == other.m_heure &&
			this->m_min == other.m_min &&
			this->m_sec > other.m_sec)
		{
			vrai = 1;
		}
		return vrai;
	}


bool Heure::operator <=(const Heure& other) const {
	bool vrai = 0;

	if (this->m_heure < other.m_heure)
	{
		vrai = 1;
	}

	if (this->m_heure == other.m_heure &&
		this->m_min < other.m_min)
	{
		vrai = 1;
	}

	if (this->m_heure == other.m_heure &&
		this->m_min == other.m_min &&
		this->m_sec <= other.m_sec)
	{
		vrai = 1;
	}
	return vrai;
}

bool Heure::operator >=(const Heure& other) const {
	bool vrai = 0;

			if (this->m_heure > other.m_heure)
			{
				vrai = 1;
			}

			if (this->m_heure == other.m_heure &&
				this->m_min > other.m_min)
			{
				vrai = 1;
			}

			if (this->m_heure == other.m_heure &&
				this->m_min == other.m_min &&
				this->m_sec >= other.m_sec)
			{
				vrai = 1;
			}
			return vrai;
		}


int Heure::operator -(const Heure& other) const {
	return (this->m_heure*3600 + this->m_min*60 + this->m_sec) -
			(other.m_heure*3600 + other.m_min*60 + other.m_sec);


}

std::ostream & operator<<(std::ostream & flux, const Heure & p_heure)
{
	flux << p_heure.m_heure << ":" << p_heure.m_min << ":" << p_heure.m_sec;

	return flux;
}
/*
 * auxiliaires.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




