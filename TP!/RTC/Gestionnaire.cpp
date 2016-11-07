#include "Gestionnaire.h"
#include "Auxiliaires.h"
#include <algorithm>
using namespace std;

Gestionnaire::Gestionnaire(std::string chemin_dossier) {

	lireFichier(chemin_dossier+"routes.txt",resultats, ',', 1 );

	for (auto itr = resultats.begin(); itr != resultats.end(); itr++)
	{
		Ligne maLigne(*itr);
		m_lignes.insert(pair<int,Ligne>(maLigne.getId(),maLigne));
	}
	resultats.clear();

	lireFichier(chemin_dossier+"trips.txt",resultats, ',', 1 );

	for (unsigned int i = 0;i<resultats.size(); i++)
	{
		for (auto itr = m_lignes.begin(); itr!=m_lignes.end(); itr++)
		{
			if (itr->second.getId() == stoi(resultats[i][0]))
			{
				Voyage monVoyage(resultats[i] ,&(m_lignes.find(stoi(resultats[i][0]))->second));
				m_voyages.insert(pair<string,Voyage> (monVoyage.getId(),monVoyage));
				itr->second.addVoyage(&m_voyages.find(monVoyage.getId())->second);
			}
		}
	}

	resultats.clear();

	lireFichier(chemin_dossier+"stops.txt",resultats, ',', 1 );

	for (auto itr = resultats.begin(); itr!=resultats.end(); itr++)
	{
		Station maStation(*itr);
		m_stations.insert(pair<int,Station>(maStation.getId(),maStation));
	}

	resultats.clear();

	lireFichier(chemin_dossier+"calendar_dates.txt",resultats, ',', 1 );

	for (unsigned int i = 0;i<resultats.size(); i++)
	{
		Date date(stoi(resultats[i][1].substr(0,4)),
						stoi(resultats[i][1].substr(4,2)),
						stoi(resultats[i][1].substr(6,2)));
		for (auto itr = m_voyages.begin(); itr!=m_voyages.end(); itr++)
		{
			if (itr->second.getServiceId() == resultats[i][0])
			{
			m_voyages_date.insert(pair<Date, Voyage*>(date,&(itr->second)));
			}
		}


	}

	resultats.clear();

	lireFichier(chemin_dossier+"stop_times.txt",resultats, ',', 1 );

	multimap<string, Arret> mesArrets;

	for (auto itr = resultats.begin(); itr!=resultats.end();itr++)
	{
		mesArrets.insert(pair<string, Arret>((*itr)[0], Arret(*itr)));
	}

	vector<Arret> arretVoyage;
	for (auto itr = m_voyages.begin(); itr!=m_voyages.end();itr++)
	{
		pair<multimap<string, Arret>::iterator,multimap<string, Arret>::iterator> mesIterators =  mesArrets.equal_range(itr->first);
		for (auto itr2 = mesIterators.first; itr2!=mesIterators.second; itr2++)
		{
			arretVoyage.push_back(itr2->second);
		}
		itr->second.setArrets(arretVoyage);
		arretVoyage.clear();

	}

/*
	for (auto itr = m_voyages.begin(); itr!=m_voyages.end(); itr++)
	{
		for (unsigned int i = 0;i<resultats.size(); i++)
		{
			if (itr->second.getId() == resultats[i][0])
			{
						arretVoyage.push_back(Arret(resultats[i]));
						m_stations.find((stoi(resultats[i][3])))->second.addVoyage(&(itr->second)); //TEST
			}



		}
		itr->second.setArrets(arretVoyage);
		arretVoyage.clear();

	}
*/
}

bool Gestionnaire::date_est_prise_en_charge(const Date& date) {

	bool estPresent=0;
	m_voyages_date.count(date) > 0 ? estPresent = 1 : estPresent = 0;

	return estPresent;


}

bool Gestionnaire::bus_existe(std::string num_ligne) {

	bool estPresent=0;

	for (unsigned int i = 0; i<m_lignes.size(); i++)
	{
		if (m_lignes.find(i)->second.getNumero() == num_ligne) estPresent = 1;
	}

	return estPresent;
}

bool Gestionnaire::station_existe(int station_id) {

	bool estPresent = 0;

	m_stations.count(station_id) > 0 ? estPresent = 1 : estPresent = 0;

	return estPresent;
}

Ligne Gestionnaire::getLigne(std::string num_ligne) {

	for (unsigned int i = 0; i<m_lignes.size(); i++)
		{
			if (m_lignes.find(i)->second.getNumero() == num_ligne)
			{
				Ligne maLigne = m_lignes.find(i)->second;
				return maLigne;
			}
		}



}

Station Gestionnaire::getStation(int station_id) {

	return m_stations.find(station_id)->second;
}

std::pair<std::string, std::string> Gestionnaire::get_bus_destinations(
		int station_id, std::string num_ligne) {
	pair<string,string> pairRetour("","");

	for(auto itr = m_lignes.find(stoi(num_ligne))->second.getVoyages().begin(); itr != m_lignes.find(stoi(num_ligne))->second.getVoyages().end(); itr++)
	{
		for(auto itr2 = (*itr)->getArrets().begin(); itr2!=(*itr)->getArrets().end(); itr2++ )
		{
			if (itr2->getStationId() == station_id)
			{
				if (pairRetour.first == "")
				{
					pairRetour.first = (*itr)->getDestination();
				}
				else if ((*itr)->getDestination() != pairRetour.first)
				{
					pairRetour.second = (*itr)->getDestination();
				}

			}
		}
	}

	return pairRetour;
}

std::vector<std::pair<double, Station*> > Gestionnaire::trouver_stations_environnantes(
		Coordonnees coord, double rayon) {

	vector<pair<double, Station*>> StationsEnv;
	double distance = 0;

	for(map<int, Station>::iterator itr = m_stations.begin(); itr != m_stations.end(); itr++)
	{
		distance = abs(coord-itr->second.getCoords());
		if (distance <= rayon)
		{
			pair<double, Station*> maPair(distance, &itr->second);
			StationsEnv.push_back(maPair);
		}
	}
	return StationsEnv;

}

std::vector<Heure> Gestionnaire::trouver_horaire(Date date, Heure heure,
		std::string numero_ligne, int station_id, std::string destination) {
	vector<Heure> vectHeure;
	vector<Voyage*> vectVoyAll = m_lignes.find(stoi(numero_ligne))->second.getVoyages();
	vector<Arret> vectArr;
	vector<Voyage*> vectVoy;
	for (auto itr = m_voyages_date.equal_range(date).first; itr != m_voyages_date.equal_range(date).second; itr++)
	{
		for (auto itr2 = vectVoyAll.begin(); itr2!=vectVoyAll.end(); itr2++)
		{
			if (itr->second->getId() == (*itr2)->getId()) vectVoy.push_back(*itr2);
		}
	}
	for (vector<Voyage*>::iterator itr = vectVoy.begin(); itr!=vectVoy.end(); itr++)
	{
		if ((*itr)->getDestination() == destination)
		{
			vectArr = (*itr)->getArrets();
			for (vector<Arret>::iterator itr2 = vectArr.begin(); itr2!=vectArr.end(); itr2++)
			{
				if (itr2->getHeureDepart()>heure && itr2->getStationId() == station_id)
				{
					vectHeure.push_back(itr2->getHeureDepart());
				}
			}
		}
	}
	return vectHeure;
}

bool Gestionnaire::reseau_est_fortement_connexe(Date date, Heure heure_debut,
		bool considerer_transfert) {
	return 0;

}

void Gestionnaire::composantes_fortement_connexes(Date date, Heure heure_debut,
		std::vector<std::vector<unsigned int> >& composantes,
		bool considerer_transfert) {
}

std::vector<unsigned int> Gestionnaire::plus_court_chemin(Date date,
		Heure heure_depart, Coordonnees depart, Coordonnees destination) {
	this->initialiser_reseau(date, heure_depart, heure_depart.add_secondes(interval_planification_en_secondes), depart, destination);

	vector<unsigned int> cheminPlusCourt;
	m_reseau.dijkstra(0, 1,cheminPlusCourt);
	vector<unsigned int> inverse;
	for(auto itr = cheminPlusCourt.end(); itr!=cheminPlusCourt.begin(); itr--)
	{
		inverse.push_back(*itr);
	}

	return inverse;
}

void Gestionnaire::initialiser_reseau(Date date, Heure heure_depart,
		Heure heure_fin, Coordonnees depart, Coordonnees dest,
		double dist_de_marche, double dist_transfert) {
	string latitude = to_string(depart.getLatitude());
	string longitude = to_string(depart.getLongitude());
	vector<string> v ={"0","", "", latitude,longitude }; //Pour initialiser les stations de départ et d'arrivée
	Station stationDepart(v);
	v[0] = "1";
	latitude = to_string(dest.getLatitude());
	longitude = to_string(dest.getLongitude());
	v[3] = latitude;
	v[4] = longitude;
	Station stationDest(v);
	stationDest.setCoords(dest);
	m_reseau.ajouterSommet(stationDepart.getId());
	m_reseau.ajouterSommet(stationDest.getId());
	vector<pair<double, Station*>> stationMarche = this->trouver_stations_environnantes(stationDepart.getCoords(), dist_de_marche);

	pair<multimap<Date,Voyage*>::iterator,multimap<Date,Voyage*>::iterator> itrDate = m_voyages_date.equal_range(date);

	for (vector<pair<double, Station*>>::iterator itr = stationMarche.begin(); itr!=stationMarche.end(); itr++)
	{
		m_reseau.ajouterSommet(itr->second->getId());
		if (!(m_reseau.arcExiste(0,itr->second->getId())))
		{
			m_reseau.ajouterArc(0,itr->second->getId(), itr->first, 1);
		}
	}

	stationMarche.clear();

	stationMarche = this->trouver_stations_environnantes(stationDest.getCoords(), dist_de_marche);
	for (vector<pair<double, Station*>>::iterator itr = stationMarche.begin(); itr!=stationMarche.end(); itr++)
	{
		m_reseau.ajouterSommet(itr->second->getId());
		if (!(m_reseau.arcExiste(itr->second->getId(), 1)))
		{
			m_reseau.ajouterArc(itr->second->getId(), 1, itr->first, 1);
		}
	}

	stationMarche.clear();

	for (auto itr = m_voyages.begin(); itr!= m_voyages.end(); itr++)
	{
		for (auto dateItr = itrDate.first; dateItr!=itrDate.second; dateItr++)
		{
		if (dateItr->second->getId() == itr->second.getId())
		{

		for (auto itr2= itr->second.getArrets().begin(); itr2 != itr->second.getArrets().end(); itr2++)
		{
			if(itr2->getHeureDepart()>heure_depart && itr2->getHeureDepart() < heure_fin)
			{
				cout<<"if externe"<<endl;
				if (!(m_reseau.sommetExiste(itr2->getStationId())))
				{
					cout<<"Premier if dedans"<<endl;
					m_reseau.ajouterSommet(itr2->getStationId());
					int x = itr2->getStationId();
					cout<<m_reseau.sommetExiste(itr2->getStationId())<<endl;
					cout<<itr2->getStationId()<<endl;
					stationMarche = trouver_stations_environnantes(m_stations.find(x)->second.getCoords(), dist_transfert);
					cout<<"avant for"<<endl;
					cout<<itr2->getStationId()<<endl;
					cout<<x<<endl;
					for (auto itr3 = stationMarche.begin(); itr3!=stationMarche.end();itr3++)
					{
						cout<<m_reseau.sommetExiste(itr2->getStationId())<<endl;
						cout<<"Jsuis dedans"<<endl;
						m_reseau.ajouterSommet(itr3->second->getId());
						cout<<"Milieu"<<endl;
						cout<<m_reseau.sommetExiste(itr3->second->getId())<<endl<<m_reseau.sommetExiste(itr2->getStationId());
						m_reseau.ajouterArc(itr2->getStationId(), itr3->second->getId(), itr3->first, 1);
						cout<<"Maman?"<<endl;
					}
					stationMarche.clear();
				}
				cout<<"new if"<<endl;
				if (itr2 != itr->second.getArrets().begin())
				{
					cout<<"2e if"<<endl;
				if(!(m_reseau.arcExiste((itr2-1)->getStationId(), itr2->getStationId())))
				{
					cout<<"Dedans le 2e if"<<endl;
					int station1 = (itr2-1)->getStationId();
					int station2 = itr2->getStationId();
					m_reseau.ajouterArc(station1, station2, (m_stations.find(station2)->second.getCoords()- m_stations.find(station1)->second.getCoords()));
				}

				else if (m_reseau.arcExiste((itr2-1)->getStationId(), itr2->getStationId()))
				{
					if(m_reseau.getTypeArc((itr2-1)->getStationId(), itr2->getStationId())==1)
					{
					cout<<"Else"<<endl;


					int station1 = (itr2-1)->getStationId();
					int station2 = itr2->getStationId();
					m_reseau.enleverArc(station1, station2);
					m_reseau.ajouterArc(station1, station2, (m_stations.find(station2)->second.getCoords()-m_stations.find(station1)->second.getCoords()),0);
				}}
			}
			}
		}}}
		}
	}

/*
 * Gestionnaire.cpp
 *
 *  Created on: 2016-10-13
 *      Author: etudiant
 */




