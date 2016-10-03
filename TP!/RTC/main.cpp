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
	for (unsigned i = 0; i<vect.size();i++)
	{
		cout<<vect[i]<<endl;
	}
}
using namespace std;
int main()
{
	vector<vector<string>> fichierLignes;
	lireFichier("routes.txt", fichierLignes, ',', false);
	for (unsigned i = 0; i < fichierLignes.size(); i++){
		Ligne tempLigne = Ligne(fichierLignes[i]);
		cout << tempLigne;
	}

	return 0;


}

