#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"

using namespace std;



int main() {
    GestionnaireInvestigation rtc("txt");

    for (int i=0; i<=20; i++){
    	 cout << "Temps moyen de dijsktra " << rtc.tester_n_paires_dijsktra(1000) << endl;
    }
    for (int i=0; i<=20; i++){
    	cout << "Temps moyen de bellman " << rtc.tester_n_paires_bellman(1000) << endl;
    }


    return 0;
}
