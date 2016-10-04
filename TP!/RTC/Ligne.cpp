#include "Ligne.h"
#include <iostream>


/**
 * \brief Constructeur de ligne avec paramètres
 * \param[in] ligne_gtfs == Un vecteur de string comportant les informations contenus dans routes.txt
 */
Ligne::Ligne(const std::vector<std::string>& ligne_gtfs):
m_id(stoi(ligne_gtfs[0])),
m_numero(ligne_gtfs[2]),
m_description(ligne_gtfs[4]),
m_categorie(couleurToCategorie(ligne_gtfs[7])),
m_voyages()
{

}

/**
 * \brief Méthode servant à traduire le code couleurs des lignes en catégorie
 * \param[in] couleur == Le string comportant le code de couleur de la ligne
 * \return La catégorie de la ligne correspondant à couleur
 */
CategorieBus Ligne::couleurToCategorie(std::string couleur) {
	CategorieBus tmp;
	if (couleur == "97BF0D"){
		tmp=CategorieBus::METRO_BUS;
	}
	if (couleur == "013888"){
		tmp=CategorieBus::LEBUS;
	}
	if (couleur == "E04503"){
		tmp=CategorieBus::EXPRESS;
	}
	if (couleur == "1A171B" || couleur == "003888"){
		tmp=CategorieBus::COUCHE_TARD;
	}
	return tmp;
}

/**
 * \brief Méthode servant à convertir la catégorie en string
 * \param[in] c == La catégorie du bus
 * \return La catégorie de la ligne correspondant sous forme de string
 */
std::string Ligne::categorieToString(CategorieBus c) {
	std::string tmp;
	if (c == CategorieBus::COUCHE_TARD){
		tmp="COUCHE_TARD";
	}
	else if (c == CategorieBus::EXPRESS){
		tmp="EXPRESS";
	}
	else if (c == CategorieBus::LEBUS){
		tmp="LEBUS";
	}
	else if (c == CategorieBus::METRO_BUS){
		tmp="METRO_BUS";
	}
	else{
		tmp="fuck";
	}
	return tmp;
}

/**
 * \brief Méthode accesseur récupérant la catégorie
 * \return La catégorie de la ligne
 */
CategorieBus Ligne::getCategorie() const {

	return m_categorie;
}

/**
 * \brief Méthode servant à modifier la catégorie
 * \param[in] categorie == La catégorie du bus à qui sera attitré à m_catégorie
 */
void Ligne::setCategorie(CategorieBus categorie) {

	m_categorie = categorie;
}
/**
 * \brief Méthode servant à convertir la catégorie en string
 * \return La destination d'aller/retour d'un bus sous forme de pair de string
 */
std::pair<std::string, std::string> Ligne::getDestinations() const {

	std::string depart = "";
	std::string destination = "";
	bool splitTest = false;
	for (unsigned i=0; i<m_description.size()+3; i++){
		if (!splitTest){
			depart += m_description[i];
			if (m_description[i+1]==' ' && m_description[i+2]=='-' && m_description[i+3]){
				splitTest=true;
			}

		}
		else{
			destination += m_description[i+3];
		}


	}
	std::pair<std::string, std::string> pair(depart, destination);
	return  pair;

}

/**
 * \brief Méthode accesseur servant à récupérer l'id de la ligne
 * \return L'id de la ligne
 */
unsigned int Ligne::getId() const {

	return m_id;
}

/**
 * \brief Méthode servant à modifier l'id d'une ligne
 * \param[in] id == l'id de la ligne qui remplacera m_id
 */
void Ligne::setId(unsigned int id) {

	m_id = id;
}
/**
 * \brief Méthode accesseur servant à récupérer le numéro d'une ligne
 * \return Le numéro de la ligne
 */
const std::string& Ligne::getNumero() const {

	return m_numero;
}

/**
 * \brief Méthode servant à modifier le numéro d'une ligne
 * \param[in] numero == Nouveau Numéro 	qui sera affecté à la ligne
 */
void Ligne::setNumero(const std::string& numero) {

	m_numero = numero;
}

/**
 * \brief Méthode accesseur servant à récupérer les voyages de la ligne
 * \return Les voyages de la ligne correspondant sous forme de vecteur
 */
const std::vector<Voyage*>& Ligne::getVoyages() const {

	return m_voyages;
}

/**
 * \brief Méthode servant à modifier les voyages de la ligne
 * \param[in] voyages == Vecteur qui sera affecté au vecteur m_voyages
 */
void Ligne::setVoyages(const std::vector<Voyage*>& voyages) {

	m_voyages = voyages;
}


/**
 * \brief Méthode servant à ajouter des voyages
 * \param[in] ptr_voyages == voyage qui sera ajouté au vecteur m_voyages
 */
void Ligne::addVoyage(Voyage* ptr_voyage) {

	m_voyages.push_back(ptr_voyage);
}


/**
 * \brief Méthode accesseur servant à récupérer la description de la ligne
 * \return La description de la ligne sous forme de string
 */
const std::string& Ligne::getDescription() const {

	return m_description;
}

/**
 * \brief Méthode servant modifier la description
 * \param[in] description == description qui sera affecté
 */
void Ligne::setDescription(const std::string& description) {

	m_description = description;


}

/**
 * \brief Méthode de surcharge qui implante le format de l'opérateur <<
 * \param[in] f == ostream où sera envoyé les informations formatés
 * \param[in] p_ligne == Ligne qui doit être envoyé dans le ostream
 * \return le contenu du ostream
 */
std::ostream & operator<<(std::ostream& f, const Ligne& p_ligne)
{
	f << p_ligne.categorieToString(p_ligne.getCategorie()) << " " << p_ligne.getNumero();
	f << " : " << p_ligne.getDescription() << std::endl;

	return f;
}
/*
 * ligne.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




