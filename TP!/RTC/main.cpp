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
using namespace std;


int main()
{
	double chrono0=clock();

	//Code chargeant les arrets dans les voyages et les voyages dans les lignes
	vector<vector<string>> vFichier;
	lireFichier("stop_times.txt", vFichier, ',', 1);



	vector<Arret> vArret;
	Heure now;
	Heure then = now.add_secondes(3600);

	for (int i=0;i<vFichier.size();i++)
	{
		Arret arret(vFichier[i]);
		if (now<arret.getHeureDepart() &&
			arret.getHeureDepart()<then)
		{
		vArret.push_back(arret);
		}
	}

	vFichier.clear();

	lireFichier("routes.txt", vFichier, ',', 1);

	vector<Ligne> vLigne;

	for (int i=0;i<vFichier.size();i++)
		{
			Ligne ligne(vFichier[i]);
			vLigne.push_back(ligne);
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

	double chrono3 = clock();

	lireFichier("trips.txt", vFichier, ',', 1);

	vector<Voyage> vVoyage;
	for (int i=0; i<vLigne.size(); i++)
	{
		for (int j=0; j<vFichier.size(); j++)
		{
			if (vLigne[i].getId() == stoi(vFichier[j][0]))
			{
				Voyage voyage(vFichier[j],&vLigne[i]);
				vector<Arret> arretVoyage;

				for (int k = 0; k<vArret.size(); k++)
				{
					if (vArret[k].getVoyageId() == voyage.getId())
					{
						arretVoyage.push_back(vArret[k]);
					}
				}
				if(arretVoyage.size() > 1)
				{
				voyage.setArrets(arretVoyage);
				vVoyage.push_back(voyage);
				int waouh = vVoyage.size()-1;
				cout<<&vVoyage[waouh]<<endl;
				vLigne[i].addVoyage(&(vVoyage[waouh]));
				cout<<*vLigne[i].getVoyages()[0]<<endl;
				}
			}
		}
	}

	vFichier.clear();
	double chrono1=clock();
	ofstream toFile;
	Date aujourdhui = Date();
	Heure maintenant = Heure();
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

	for (int z=0 ; z < vStation.size(); z++){
		toFile << vStation[z] << endl;
	}
	toFile << "===================" << endl
			<< "Voyage de la journée du " << aujourdhui << endl << now << "-" << then << endl;
			vector<Voyage> voyageNow;
			string serviceNow;

			lireFichier("calendar_dates.txt", vFichier, ',', 1);
			for (int i = 0; i<vFichier.size(); i++)
			{
				Date calDate(stoi(vFichier[i][1].substr(0,4)),
						stoi(vFichier[i][1].substr(4,2)),
						stoi(vFichier[i][1].substr(6,2)));
				if (calDate == aujourdhui)
				{
					serviceNow = vFichier[i][0];
				}
			}
			cout<<serviceNow<<" : "<<((vLigne[0].getVoyages())[0]->getServiceId())<<endl;

			for (int i = 0; i<vLigne.size(); i++)
			{
				for (int j = 0; j<vLigne[i].getVoyages().size(); j++)
				{
					if ((vLigne[i].getVoyages()[j])->getServiceId() == serviceNow)
					{
					voyageNow.push_back(*(vLigne[i].getVoyages()[j]));
					}
				}
			}
			cout<< "Compte = " << voyageNow.size() << endl
			<< "===================" << endl;
	for (int z=0 ; z < voyageNow.size(); z++){
		toFile << voyageNow[z].getLigne()->getNumero()<<": Vers "
				<< voyageNow[z].getDestination() << endl;
		for (int y = 0; y<voyageNow[z].getArrets().size(); y++)
		{
			toFile << voyageNow[z].getArrets()[y].getHeureDepart()
					<<" - "<<voyageNow[z].getArrets()[y].getStationId()<<endl;
		}

	}
	toFile.close();



	return 0;


}

