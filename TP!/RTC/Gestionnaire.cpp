#include "Gestionnaire.h"
#include "Auxiliaires.h"
#include <map>
using namespace std;

Gestionnaire::Gestionnaire(std::string chemin_dossier) {

	vector<vector<string>> resultats;
	map<int, Ligne> m_lignes;
	map<int, Station> m_stations;
	map<string, Voyage> m_voyages;
	map<Voyage*, Date> m_voyages_date;

	lireFichier(chemin_dossier+"routes.txt",resultats, ';', 1 );

	for (vector<vector<string>>::iterator itr = resultats.begin(); itr != resultats.end(); itr++)
	{
		Ligne maLigne(*itr);
		m_lignes[maLigne.getId()]=maLigne;
	}

	lireFichier(chemin_dossier+"stops.txt",resultats, ';', 1 );

	for (vector<vector<string>>::iterator itr = resultats.begin(); itr != resultats.end(); itr++)
	{
		Station maStation(*itr);
		m_stations[maStation.getId()]=maStation;
	}

	lireFichier(chemin_dossier+"trips.txt",resultats, ';', 1 );

	for (unsigned int i = 0;i<resultats.size(); i++)
	{
		Voyage monVoyage(resultats[i] ,&(m_lignes[stoi(resultats[i][0])]));
		m_voyages[monVoyage.getId()]=monVoyage;
	}

	lireFichier(chemin_dossier+"calendar_dates.txt",resultats, ';', 1 );


}

bool Gestionnaire::date_est_prise_en_charge(const Date& date) {
}

bool Gestionnaire::bus_existe(std::string num_ligne) {
}

bool Gestionnaire::station_existe(int station_id) {
}

Ligne Gestionnaire::getLigne(std::string num_ligne) {
}

Station Gestionnaire::getStation(int station_id) {
}

std::pair<std::string, std::string> Gestionnaire::get_bus_destinations(
		int station_id, std::string num_ligne) {
}

std::vector<std::pair<double, Station*> > Gestionnaire::trouver_stations_environnantes(
		Coordonnees coord, double rayon) {
}

std::vector<Heure> Gestionnaire::trouver_horaire(Date date, Heure heure,
		std::string numero_ligne, int station_id, std::string destination) {
}

bool Gestionnaire::reseau_est_fortement_connexe(Date date, Heure heure_debut,
		bool considerer_transfert) {
}

void Gestionnaire::composantes_fortement_connexes(Date date, Heure heure_debut,
		std::vector<std::vector<unsigned int> >& composantes,
		bool considerer_transfert) {
}

std::vector<unsigned int> Gestionnaire::plus_court_chemin(Date date,
		Heure heure_depart, Coordonnees depart, Coordonnees destination) {
}

void Gestionnaire::initialiser_reseau(Date date, Heure heure_depart,
		Heure heure_fin, Coordonnees depart, Coordonnees dest,
		double dist_de_marche, double dist_transfert) {
}
/*
 * Gestionnaire.cpp
 *
 *  Created on: 2016-10-13
 *      Author: etudiant
 */




