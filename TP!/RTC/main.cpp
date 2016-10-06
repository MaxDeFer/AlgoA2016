/*
 * Main.cpp
 *
 *  Created on: 2016-09-19
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
using namespace std;


int main()
{

	double chrono0 = clock();
	Heure now;
	Heure then = now.add_secondes(3600);
	Date today;
	vector<vector<string>> vFichier;
	lireFichier("routes.txt", vFichier, ',', 1);
	vector<Ligne> vLigne;

		for (int i=0;i<vFichier.size();i++)
			{
				Ligne ligne(vFichier[i]);
				vLigne.push_back(ligne);
			}
	vFichier.clear();

	lireFichier("trips.txt", vFichier, ',', 1);

	vector<Voyage> vVoyage;

	for (int i=0; i<vFichier.size(); i++)
	{
		for (int j=0; j<vLigne.size(); j++)
		{
			if (vLigne[j].getId() == stoi(vFichier[i][0]))
			{
				Voyage unVoyage(vFichier[i], &vLigne[j]);
				vVoyage.push_back(unVoyage);
				vLigne[j].addVoyage(&vVoyage[vVoyage.size()-1]);
			}
		}
	}
	vFichier.clear();

	vector<string> serviceNow;

	lireFichier("calendar_dates.txt", vFichier, ',', 1);
	for (int i = 0; i<vFichier.size(); i++)
	{
		Date calDate(stoi(vFichier[i][1].substr(0,4)),
				stoi(vFichier[i][1].substr(4,2)),
				stoi(vFichier[i][1].substr(6,2)));
		if (calDate == today)
		{
			serviceNow.push_back(vFichier[i][0]);
		}

	}

	vFichier.clear();

		for (int i=0; i<vVoyage.size(); i++)
		{
			if (find(serviceNow.begin(), serviceNow.end(), vVoyage[i].getServiceId()) == serviceNow.end())
			{
				vVoyage.erase(vVoyage.begin()+i);
			}
		}
	lireFichier("stop_times.txt", vFichier, ',', 1);

	vector<Arret> vArret;

	for (int i=0; i<vFichier.size(); i++)
	{
		Arret unArret(vFichier[i]);
		if (now<unArret.getHeureDepart())
		{
			if (unArret.getHeureDepart()<then)
			{
				vArret.push_back(unArret);
			}
		}
	}

	vector<Arret> arretVoyage;
	for (int i=0; i<vVoyage.size(); i++)
	{
		for (int j=0; j<vArret.size(); j++)
		{
			if (vVoyage[i].getId() == vArret[j].getVoyageId())
			{
						arretVoyage.push_back(vArret[j]);
			}



		}
		vVoyage[i].setArrets(arretVoyage);
		arretVoyage.clear();

	}
	vFichier.clear();



	lireFichier("stops.txt", vFichier, ',', 1);

	vector<Station> vStation;

	for (int i=0;i<vFichier.size();i++)
			{
				Station station(vFichier[i]);
				vStation.push_back(station);
			}

	vFichier.clear();

	double chrono1=clock();

	ofstream toFile;
	Date aujourdhui = Date();
	toFile.open("test.txt");
	cout<<fixed<<setprecision(4)<<"Chargement des données terminé en "<<(chrono1 - chrono0)/1000000<<" secondes"<<endl;
	toFile << "Chargement des données terminé en "
			<<  (chrono1 - chrono0)/1000000<<" secondes"<<endl
			<< "===================" << endl
			<< "Ligne de la RTC" << endl
			<< "Compte = " << vLigne.size() << endl
			<< "===================" << endl;

	for (int z=0 ; z < vLigne.size(); z++){

		toFile << vLigne[z] << endl;
	}
	toFile << "===================" << endl
			<< "Stations de la RTC" << endl
			<< "Compte = " << vStation.size() << endl
			<< "===================" << endl;
	cout << vVoyage[0].getArrets()[2];
	for (int z=0 ; z < vStation.size(); z++){
		toFile << vStation[z] << endl;
	}
	toFile << "===================" << endl
			<< "Voyage de la journée du " << aujourdhui << endl << now << "-" << then << endl
			<< "Compte = " << vVoyage.size();
			vector<Voyage> voyageNow;
			vector<string> serviceNow;


	lireFichier("calendar_dates.txt", vFichier, ',', 1);
	for (int i = 0; i<vFichier.size(); i++)
	{
		Date calDate(stoi(vFichier[i][1].substr(0,4)),
				stoi(vFichier[i][1].substr(4,2)),
				stoi(vFichier[i][1].substr(6,2)));
		if (calDate == aujourdhui)
		{
			serviceNow.push_back(vFichier[i][0]);
		}

	}
	cout << vVoyage[0].getArrets()[2];

		for (int z=0 ; z < vVoyage.size(); z++){
			if(std::find(serviceNow.begin(), serviceNow.end(), vVoyage[z].getServiceId() ) != serviceNow.end()) {
				toFile << vVoyage[z] << endl;

				for (int y=0 ; y < vVoyage[z].getArrets().size(); y++){
					if (vVoyage[z].getArrets()[y].getHeureDepart()>now && vVoyage[z].getArrets()[y].getHeureDepart()<then)

				toFile << vVoyage[z].getArrets()[y] << endl;
				}
			}

		}





	toFile.close();





	return 0;


}
