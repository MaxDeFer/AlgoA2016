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

/*
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

	vector<Arret> arretVoyage;
	for (int i=0; i<vLigne.size(); i++)
	{
		for (int j=0; j<vFichier.size(); j++)
		{
			Voyage voyage(vFichier[j],&vLigne[i]);
			if (vLigne[i].getId() == stoi(vFichier[j][0]))
			{
				for (int k = 0; k<vArret.size(); k++)
				{
					if (vArret[k].getVoyageId() == voyage.getId())
					{
						//cout<<"Found!"<<endl;
						arretVoyage.push_back(vArret[k]);
					}
				}

				if(arretVoyage.size() > 1)
				{
				voyage.setArrets(arretVoyage);
				arretVoyage.clear();
				vVoyage.push_back(voyage);
				int waouh = vVoyage.size()-1;
				cout<<vVoyage[waouh]<<endl;
				vLigne[i].addVoyage(&(vVoyage[waouh]));
				//cout<<vLigne[i].getVoyages().size()<<endl;
				}
			}
		}
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

	for (int z=0 ; z < vStation.size(); z++){
		toFile << vStation[z] << endl;
	}
	toFile << "===================" << endl
			<< "Voyage de la journée du " << aujourdhui << endl << now << "-" << then << endl;
			vector<Voyage> voyageNow;
			vector<string> serviceNow;
			vector<Arret> arretThing;


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


		for (int z=0 ; z < vVoyage.size(); z++){
			if(std::find(serviceNow.begin(), serviceNow.end(), vVoyage[z].getServiceId() ) != serviceNow.end()) {
				toFile << vVoyage[z] << endl;
				for (int y=0 ; y < vVoyage[z].getArrets().size(); y++){

					arretThing.push_back(vVoyage[z].getArrets()[y]);
					sort(arretThing.begin(), arretThing.end());
					toFile << arretThing[y] << endl;
					arretThing.clear();

				}
			}

		}





			/*cout<<serviceNow<<" : "<<((vLigne[0].getVoyages())[0]->getServiceId())<<endl;

			for (int i = 0; i<vLigne.size(); i++)
			{
				for (int j = 0; j<vLigne[i].getVoyages().size(); j++)
				{
					if (vVoyage[j].getId() == serviceNow)
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

	}*/
//	toFile.close();



	return 0;


}


