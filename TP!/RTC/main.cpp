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


void printVector(vector<int> vect)
{
	for (int i = 0; i<vect.size();i++)
	{
		cout<<vect[i]<<endl;
	}
}
using namespace std;
int main()
{
	double chrono0=clock();

	vector<vector<string>> arretTxt;
	lireFichier("stop_times.txt", arretTxt, ',', 1);
	vector<Arret> vecteurArret;
	for (int i=0;i<arretTxt.size();i++)
	{
		Arret arret(arretTxt[i]);
		vecteurArret.push_back(arret);
	}

	double chrono1=clock();

	cout<<fixed<<setprecision(4)<<"Chargement des données terminé en "<<(chrono1 - chrono0)/1000<<" secondes"<<endl;
	for (int i = 0; i<vecteurArret.size(); i++)
	{
		cout<<arretTxt[i][0]<<endl;
	}
	return 0;


}

