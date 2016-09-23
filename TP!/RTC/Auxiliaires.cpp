#include "Auxiliaires.h"

std::vector<std::string> split(const std::string& s, char delim) {
}

void lireFichier(std::string nomFichier,
		std::vector<std::vector<std::string> >& resultats, char delimiteur,
		bool rm_entete) {
}

Date::Date() {
}

Date::Date(unsigned int an, unsigned int mois, unsigned int jour) {
}

bool Date::operator ==(const Date& other) const {
}

bool Date::operator <(const Date& other) const {
}

bool Date::operator >(const Date& other) const {
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
		unsigned int mins = nouvelleSec/60;
		nouvelleSec = (this->m_sec + secs)%60;
		if (this->m_min + mins > 60)
		{

		}
			//TODO
	}
}

bool Heure::operator ==(const Heure& other) const {
}

bool Heure::operator <(const Heure& other) const {
}

bool Heure::operator >(const Heure& other) const {
}

bool Heure::operator <=(const Heure& other) const {
}

bool Heure::operator >=(const Heure& other) const {
}

int Heure::operator -(const Heure& other) const {
}
/*
 * auxiliaires.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




