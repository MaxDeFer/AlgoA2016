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
using namespace std;

int main(int argc, char **argv) {
	Date uneDate;
	Heure heureDepart;
	Heure heureArrivee = heureDepart.add_secondes(3600);
	Coordonnees depart(46.891,-71.271741);	//3041
	Coordonnees arrivee(46.744664,-71.457378);	//6195
	Gestionnaire unGestionnaire("/home/etudiant/Bureau/Algo/AlgoA2016/TP!/");
	unGestionnaire.initialiser_reseau(uneDate, heureDepart, heureArrivee, depart, arrivee, 250, 100);




	return 0;
}




