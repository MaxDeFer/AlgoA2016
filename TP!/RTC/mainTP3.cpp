#include <iostream>
#include "Coordonnees.h"
#include <vector>
#include "investigation.h"
#include "reseau.h"

using namespace std;



int main() {
    GestionnaireInvestigation rtc("googletransit");

    cout << "Temps moyen de dijsktra " << rtc.tester_n_paires_dijsktra(1000) << endl;

    cout << "Temps moyen de bellman " << rtc.tester_n_paires_bellman(1000) << endl;
    return 0;
}
