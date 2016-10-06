#include "Auxiliaires.h"

/**
 * \brief Méthode séparant des string par un délimiteur
 * \param[in] s == Le string devant être séparé
 * \param[in] delim == Le charactère où efectuer les coupes
 * \return Un vecteur dont les éléments sont les mots séparés
 */

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
/**
 * \brief Méthode qui effectue la lecture d'un fichier texte
 * \param[in] resultat == Le vecteur 2D où seront enregistré chaque lignes sous forme de vecteur dont les
 * éléments seront les colonnes du fichier textes
 * \param[in] delimiteur == Le charactère où efectuer les coupes des "colonnes"
 * \param[in] rm_entete == Un booléen qui détermine si l'entête doit être inclu dans le vecteur
 */
void lireFichier(std::string nomFichier,
		std::vector<std::vector<std::string> >& resultats, char delimiteur,
		bool rm_entete) {

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


/**
 * \brief Constructeur de date par défaut
 */

Date::Date() {

	time_t secondes = time(0);
	tm *temps = localtime(&secondes);

	m_an = temps->tm_year+1900;
	m_mois = temps->tm_mon+1;
	m_jour = temps->tm_mday;
}

/**
 * \brief Constructeur de date avec paramètre
 * \param[in] an == L'année correspondante à la date
 * \param[in] mois == Le mois correspondant à la date
 * \param[in] jour == Le jour correspondant à la date
 */
Date::Date(unsigned int an, unsigned int mois, unsigned int jour):m_an(an), m_mois(mois), m_jour(jour) {
}


/**
 * \brief Méthode de surcharge de comparateur
 * \param[in] p_other == Deuxième date à comparer à notre objet courant
 * \return Un booléen true si les dates sont égales, false sinon
 */
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
/**
 * \brief Méthode de surcharge de comparateur "Plus petit que" entre deux dates
 * \param[in] p_other == Deuxième date à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */
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

/**
 * \brief Méthode de surcharge de comparateur "Plus grand que" entre deux dates
 * \param[in] p_other == Deuxième date à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */
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


/**
 * \brief Méthode de surcharge qui implante le format de l'opérateur <<
 * \param[in] f == ostream où sera envoyé les informations formatés
 * \param[in] p_date == Arret qui doit être envoyé dans le ostream
 * \return le contenu du ostream
 */
std::ostream & operator<<(std::ostream & flux, const Date & p_date)
{
	flux << p_date.m_an << "/" << p_date.m_mois << "/" << p_date.m_jour;

	return flux;
}

Heure::Heure(){

	time_t secondes = time(0);
	tm *temps = localtime(&secondes);

	m_heure = temps->tm_hour;
	m_min = temps->tm_min;
	m_sec = temps->tm_sec;
}


/**
 * \brief Constructeur de date avec paramètre
 * \param[in] heure == L'année correspondante à la date
 * \param[in] min == Le mois correspondant à la date
 * \param[in] sec == Le jour correspondant à la date
 */
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

/**
 * \brief Méthode de surcharge de comparateur
 * \param[in] p_other == Deuxième heure à comparer à notre objet courant
 * \return Un booléen true si les heure sont égales, false sinon
 */
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

/**
 * \brief Méthode de surcharge de comparateur "Plus petit que" entre deux heures
 * \param[in] p_other == Deuxième heure à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */
bool Heure::operator <(const Heure& other) const {
	bool vrai = 0;

	if (this->m_heure < other.m_heure)
	{
		vrai = 1;
	}

	else if (this->m_heure == other.m_heure &&
		this->m_min < other.m_min)
	{
		vrai = 1;
	}

	else if (this->m_heure == other.m_heure &&
		this->m_min == other.m_min &&
		this->m_sec < other.m_sec)
	{
		vrai = 1;
	}
	return vrai;
}
/**
 * \brief Méthode de surcharge de comparateur "Plus grand que" entre deux heures
 * \param[in] p_other == Deuxième heure à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */
bool Heure::operator >(const Heure& other) const {
	bool vrai = 0;

		if (this->m_heure > other.m_heure)
		{
			vrai = 1;
		}

		else if (this->m_heure == other.m_heure &&
			this->m_min > other.m_min)
		{
			vrai = 1;
		}

		else if (this->m_heure == other.m_heure &&
			this->m_min == other.m_min &&
			this->m_sec > other.m_sec)
		{
			vrai = 1;
		}
		return vrai;
	}

/**
 * \brief Méthode de surcharge de comparateur "Plus petit ou égale que" entre deux heures
 * \param[in] p_other == Deuxième heure à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */
bool Heure::operator <=(const Heure& other) const {
	bool vrai = 0;

	if (this->m_heure < other.m_heure)
	{
		vrai = 1;
	}

	else if (this->m_heure == other.m_heure &&
		this->m_min < other.m_min)
	{
		vrai = 1;
	}

	else if (this->m_heure == other.m_heure &&
		this->m_min == other.m_min &&
		this->m_sec <= other.m_sec)
	{
		vrai = 1;
	}
	return vrai;
}
/**
 * \brief Méthode de surcharge de comparateur "Plus grand ou égale que" entre deux heures
 * \param[in] p_other == Deuxième heure à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */
bool Heure::operator >=(const Heure& other) const {
	bool vrai = 0;

			if (this->m_heure > other.m_heure)
			{
				vrai = 1;
			}

			else if (this->m_heure == other.m_heure &&
				this->m_min > other.m_min)
			{
				vrai = 1;
			}

			else if (this->m_heure == other.m_heure &&
				this->m_min == other.m_min &&
				this->m_sec >= other.m_sec)
			{
				vrai = 1;
			}
			return vrai;
		}

/**
 * \brief Méthode de surcharge de comparateur de soustraction entre deux heures
 * \param[in] p_other == Deuxième heure à comparer à notre objet courant
 * \return Un booléen correspondant au résultat
 */
int Heure::operator -(const Heure& other) const {
	return (this->m_heure*3600 + this->m_min*60 + this->m_sec) -
			(other.m_heure*3600 + other.m_min*60 + other.m_sec);


}


/**
 * \brief Méthode de surcharge qui implante le format de l'opérateur <<
 * \param[in] f == ostream où sera envoyé les informations formatés
 * \param[in] p_heure == Heure qui doit être envoyé dans le ostream
 * \return le contenu du ostream
 */
std::ostream & operator<<(std::ostream & flux, const Heure & p_heure)
{
	std::string ajusteH = "";
	std::string ajusteM = "";
	std::string ajusteS = "";
	if (p_heure.m_heure < 10){
		ajusteH = "0";
	}
	if (p_heure.m_min < 10){
		ajusteM = "0";
	}
	if (p_heure.m_sec < 10){
		ajusteS = "0";
	}
	flux << ajusteH << p_heure.m_heure << ":" << ajusteM << p_heure.m_min << ":" << ajusteS << p_heure.m_sec;

	return flux;
}
/*
 * auxiliaires.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




