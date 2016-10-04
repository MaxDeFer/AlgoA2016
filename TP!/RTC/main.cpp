/*
 * Main.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */

#include <iostream>
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

	vector<vector<string>> vFichier;
	lireFichier("/home/etudiant/Bureau/Algo/TP1/AlgoA2016/TP!/RTC/stop_times.txt", vFichier, ',', 1);



	vector<Arret> vArret;
	vArret.reserve(vFichier.size());
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

	lireFichier("/home/etudiant/Bureau/Algo/TP1/AlgoA2016/TP!/RTC/routes.txt", vFichier, ',', 1);

	vector<Ligne> vLigne;
	vLigne.reserve(vFichier.size());

	for (int i=0;i<vFichier.size();i++)
		{
			Ligne ligne(vFichier[i]);
			vLigne.push_back(ligne);
		}

	vFichier.clear();

	lireFichier("/home/etudiant/Bureau/Algo/TP1/AlgoA2016/TP!/RTC/stops.txt", vFichier, ',', 1);

	vector<Station> vStation;
	vStation.reserve(vFichier.size());

	for (int i=0;i<vFichier.size();i++)
			{
				Station station(vFichier[i]);
				vStation.push_back(station);
			}

	vFichier.clear();
	double chrono3 = clock();
	cout<<"Temps avant LA boucle:"<<(chrono3 - chrono0)/1000000<<endl;

	lireFichier("/home/etudiant/Bureau/Algo/TP1/AlgoA2016/TP!/RTC/trips.txt", vFichier, ',', 1);

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
					voyage.setArrets(arretVoyage);
					vLigne[i].addVoyage(&voyage);
				}
		}
	}

	vFichier.clear();

	double chrono1=clock();

	cout<<fixed<<setprecision(4)<<"Chargement des données terminé en "<<(chrono1 - chrono0)/1000000<<" secondes"<<endl;



	return 0;


}

