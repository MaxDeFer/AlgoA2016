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




/*	vector<vector<string>> fichierLigne;

	lireFichier("/home/etudiant/Bureau/Algo/TP1/AlgoA2016/TP!/RTC/routes.txt", fichierLigne, ',', 1);

	vector<vector<string>> fichierVoyage;

	lireFichier("/home/etudiant/Bureau/Algo/TP1/AlgoA2016/TP!/RTC/trips.txt", fichierVoyage, ',', 1);

	vector<vector<string>> fichierStation;

	lireFichier("/home/etudiant/Bureau/Algo/TP1/AlgoA2016/TP!/RTC/stops.txt", fichierStation, ',', 1);

	vector<vector<string>> fichierArret;

	lireFichier("/home/etudiant/Bureau/Algo/TP1/AlgoA2016/TP!/RTC/stop_times.txt", fichierArret, ',', 1);

	vector<Ligne> vLigne;

	for (int i=0; i<fichierLigne.size(); i++)
	{
		Ligne uneLigne(fichierLigne[i]);
		vLigne.push_back(uneLigne);
	}

	vector<Voyage> vVoyage;

	for (int i = 0; i<vLigne.size(); i++)
	{
		for (int j = 0; j<fichierVoyage.size(); j++)
		{
			if (vLigne[i].getId() == stoi(fichierVoyage[j][0]))
			{
				Voyage unVoyage(fichierVoyage[j],&vLigne[i]);
				vVoyage.push_back(unVoyage);
			}
		}
	}

	vector<Arret> vArret;

	for (int i = 0; i<fichierArret.size(); i++)
	{
		Arret unArret(fichierArret[i]);
		vArret.push_back(unArret);
	}


	for (int i = 0; i<vVoyage.size(); i++)
	{
		vector<Arret> arretVoyage;
		for (int j = 0; j<vArret.size(); j++)
		{
			if (vVoyage[i].getId() == vArret[j].getVoyageId())
			{
				arretVoyage.push_back(vArret[j]);
			}
		}
		vVoyage[i].setArrets(arretVoyage);
	}

	for (int i = 0; i<vLigne.size(); i++)
	{
		vector<Voyage*> ligneVoyage;
		for (int j = 0; j<vVoyage.size(); j++)
		{
			if (vLigne[i].getId() == vVoyage[j].getLigne()->getId())
			{
				ligneVoyage.push_back(&vVoyage[j]);
			}
		}
		vLigne[i].setVoyages(ligneVoyage);
	}

*/
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

	double chrono2 = clock();
	cout<<"Temps apres Arret:"<<(chrono2-chrono0)/1000000<<endl;

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
	cout<<"Temps avant LA boucle:"<<(chrono3 - chrono0)/1000000<<endl;

	lireFichier("trips.txt", vFichier, ',', 1);

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
				vLigne[i].addVoyage(&voyage);
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
			for (int i = 0; i<vLigne.size(); i++)
			{
				for (int j = 0; j<vLigne[i].getVoyages().size(); j++)
				{
					if (vLigne[i].getVoyages()[j]->getServiceId() == serviceNow)
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

