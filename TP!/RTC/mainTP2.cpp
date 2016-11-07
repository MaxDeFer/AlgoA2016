/*
 * mainTP2.cpp
 *
 *  Created on: 2016-11-04
 *      Author: etudiant
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Coordonnees.h"
#include <vector>
#include "Auxiliaires.h"
#include "Arret.h"
#include "Ligne.h"
#include "Station.h"
#include "Voyage.h"
#include <algorithm>
#include "Gestionnaire.h"
#include "reseau.h"
#include <cstring>
using namespace std;

int main(int argc, char **argv) {
	cout<<"Bienvenue dans l'application RTC<<endl";
	double chrono0 = clock();
	Gestionnaire unGestionnaire("./");
	double chrono1=clock();
	cout<<fixed<<setprecision(4)<<"Chargement des données terminé en "<<(chrono1 - chrono0)/1000000<<" secondes"<<endl;

	char reponseMenu[255] = "1";
	char reponse[255];
	string repM = "1";

	Date uneDate;
	Heure uneHeure;

	time_t secondes;
	tm *temps;
	int an;
	int mois;
	int jour;
	int heure;
	int min;
	int sec;

	while (repM=="1" || repM=="2" || repM =="3" || repM=="4")
	{
		cout<<"Menu"<<endl
				<<"1 - Stations à proximité"<<endl
				<<"2 - Consulter horaire du bus"<<endl
				<<"3 - Itinéraire"<<endl
				<<"4 - Stats de connectivité"<<endl
				<<"Sélectionner une option en indiquant un chiffre ou autre chose pour quitter:";
		cin.getline(reponseMenu, 255);
		repM = reponseMenu;
		if (repM == "1")
		{
			double latitude;
			double longitude;
			double rayon;
			vector<pair<double, Station*>> stationEnv;

			cout<<"Entrez vos coordonnées GPS"<<endl
					<<"Latitude:";
			cin.getline(reponse, 255);
			latitude = atof(reponse);

			cout<<endl<<"Longitude:";
			cin.getline(reponse, 255);
			longitude = atof(reponse);

			cout<<endl<<"Entrez un rayon (en Km) pour la recherche:";
			cin.getline(reponse, 255);
			rayon = atof(reponse);

			Coordonnees position(latitude, longitude);
			stationEnv = unGestionnaire.trouver_stations_environnantes(position,rayon);
			for(vector<pair<double, Station*>>::iterator itr = stationEnv.begin(); itr!=stationEnv.end(); itr++)
			{
				cout<<fixed<<setprecision(7)<<"À une distance de "<<itr->first<<"km:"<<endl;
				cout<<itr->second->getId()<<" - "<<itr->second->getDescription();
			}
		}

		else if (repM == "2")
		{
			secondes = time(0);
			temps = localtime(&secondes);

			an = temps->tm_year+1900;
			mois = temps->tm_mon+1;
			jour = temps->tm_mday;
			heure = temps->tm_hour;
			min = temps->tm_min;
			sec = temps->tm_sec;




			int numStation;

			cout<<"Entrez la date qui vous intéresse!"<<endl
					<<"année [défaut="<<an<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) an = atoi(reponse);

			cout<<"mois [défaut="<<mois<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) mois = atoi(reponse);

			cout<<"jour [défaut="<<jour<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) jour = atoi(reponse);

			uneDate = Date(an, mois, jour);

			cout<<"Entrez l'heure de début de l'horaire!"<<endl
					<<"heure [défaut="<<heure<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) heure = atoi(reponse);

			cout<<"minutes [défaut="<<min<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) min = atoi(reponse);

			cout<<"secondes [défaut="<<sec<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) sec = atoi(reponse);

			uneHeure = Heure(heure, min, sec);

			cout<<"Entrez le numéro du bus: ";
			cin.getline(reponse,255);
			string numBus(reponse);

			cout<<"Entrez le numéro de la station: ";
			cin.getline(reponse,255);
			numStation = atoi(reponse);

			pair<string,string> pairDest = unGestionnaire.get_bus_destinations(numStation, numBus);
			string choixDest = pairDest.first;
			if(pairDest.second!= "")
			{
				cout<<"Plusieurs destinations possible!"<<endl
						<<"1: "<<pairDest.first<<endl
						<<"2: "<<pairDest.second<<endl;
				cout<<"Choisissez votre destination: ";
				cin.getline(reponse,255);
				cout<<endl;

				if (atoi(reponse)==2) choixDest = pairDest.second;


			}

			Station maStation = unGestionnaire.getStation(numStation);
			Ligne maLigne = unGestionnaire.getLigne(numBus);

			cout<<maLigne.categorieToString(maLigne.getCategorie())<<" "<<numBus<<" - "<<maLigne.getDescription()<<endl
					<<numStation<<" - "<<maStation.getDescription()<<endl<<endl;


			vector<Heure> monHoraire = unGestionnaire.trouver_horaire(uneDate, uneHeure, numBus, numStation, choixDest);
			for(auto itr = monHoraire.begin(); itr!= monHoraire.end(); itr++)
			{
				cout<<*itr<<endl;
			}
		}

		else if (repM == "3")
		{

			vector<pair<string, Coordonnees>> monCarnet = {{"3475 avenue maricourt, Québec", Coordonnees(46.760074,-71.319867)},
														{"2325 vie étudiante, Québec", Coordonnees(46.778398, -71.26853)},
														{"Cineplex odéon sainte-foy", Coordonnees(46.785923,-71.354046)},
														{"Pavillon pouliot", Coordonnees(46.776635,-71.270671)},
														{"2476, avenue de lisieux, québec", Coordonnees(46.857245,-71.206804)},
														{"Pavillon desjardin", Coordonnees(46.778808,-71.270014)}};

			cout<<"Choisir votre point de départ"<<endl
					<<"Carnets d'adresse"<<endl;
			for (int i = 0; i< monCarnet.size(); i++)
			{
				cout<<i+1<<" - "<<monCarnet[i].first<<": "<<monCarnet[i].second<<endl;
			}
			cout<<"Sélectionner une adresse en indiquant un chiffre:";
			cin.getline(reponse,255);
			Coordonnees pointDepart(monCarnet[atoi(reponse)-1].second);

			cout<<"Choisir votre point d'arrivé"<<endl
					<<"Carnets d'adresse"<<endl;
			for (int i = 0; i< monCarnet.size(); i++)
			{
				cout<<i+1<<" - "<<monCarnet[i].first<<": "<<monCarnet[i].second<<endl;
			}
			cout<<"Sélectionner une adresse en indiquant un chiffre:";
			cin.getline(reponse,255);
			Coordonnees pointDarrivee(monCarnet[atoi(reponse)-1].second);

			secondes = time(0);
			temps = localtime(&secondes);

			an = temps->tm_year+1900;
			mois = temps->tm_mon+1;
			jour = temps->tm_mday;
			heure = temps->tm_hour;
			min = temps->tm_min;
			sec = temps->tm_sec;

			cout<<"Entrez la date qui vous intéresse!"<<endl
					<<"année [défaut="<<an<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) an = atoi(reponse);

			cout<<"mois [défaut="<<mois<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) mois = atoi(reponse);

			cout<<"jour [défaut="<<jour<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) jour = atoi(reponse);

			uneDate = Date(an, mois, jour);

			cout<<"Entrez l'heure de départ!"<<endl
					<<"heure [défaut="<<heure<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) heure = atoi(reponse);

			cout<<"minutes [défaut="<<min<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) min = atoi(reponse);

			cout<<"secondes [défaut="<<sec<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) sec = atoi(reponse);

			uneHeure = Heure(heure, min, sec);



			cout<<"Initialisation du réseau ...."<<endl;


			vector<unsigned int> monChemin = unGestionnaire.plus_court_chemin(uneDate, uneHeure, pointDepart, pointDarrivee);
			for (auto itr = monChemin.begin(); itr!=monChemin.end(); itr++)
			{
				Station maStationPlusCourt = unGestionnaire.getStation(*itr);
				cout<<maStationPlusCourt.getId()<<" - "<<maStationPlusCourt.getDescription()<<endl;
			}



		}

		else if (repM == "4")
		{
			secondes = time(0);
			temps = localtime(&secondes);

			an = temps->tm_year+1900;
			mois = temps->tm_mon+1;
			jour = temps->tm_mday;
			heure = temps->tm_hour;
			min = temps->tm_min;
			sec = temps->tm_sec;

			cout<<"Entrez la date qui vous intéresse!"<<endl
					<<"année [défaut="<<an<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) an = atoi(reponse);

			cout<<"mois [défaut="<<mois<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) mois = atoi(reponse);

			cout<<"jour [défaut="<<jour<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) jour = atoi(reponse);

			uneDate = Date(an, mois, jour);

			cout<<"Entrez l'heure de début qui vous intéresse!"<<endl
					<<"heure [défaut="<<heure<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) heure = atoi(reponse);

			cout<<"minutes [défaut="<<min<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) min = atoi(reponse);

			cout<<"secondes [défaut="<<sec<<"] :";
			cin.getline(reponse,255);
			if (strlen(reponse) != 0) sec = atoi(reponse);

			uneHeure = Heure(heure, min, sec);

			vector<string> maReponse = {"n'est pas fortement connexe", "est fortement connexe"};
			bool estConnexeAvec = unGestionnaire.reseau_est_fortement_connexe(uneDate, uneHeure);
			bool estConnexeSans = unGestionnaire.reseau_est_fortement_connexe(uneDate, uneHeure, false);
			cout<<"Avec les arêtes de transfert, le réseau "<<maReponse[estConnexeAvec]<<endl;
			cout<<"Sans les arêtes de transfert, le réseau "<<maReponse[estConnexeSans]<<endl;


		}


	}





	return 0;
}




