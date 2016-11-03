Gestionnaire::Gestionnaire(std::string chemin_dossier) {
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




