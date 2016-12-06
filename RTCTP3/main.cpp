#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"

using namespace std;



int main() {
    GestionnaireInvestigation rtc("txt");


    /*Reseau r;
    r.ajouterSommet(12);
    r.ajouterSommet(14);
    r.ajouterSommet(16);
    r.ajouterSommet(18);
    r.ajouterSommet(22);
    r.ajouterSommet(20);
    r.ajouterArc(12,18,16,1);
    r.ajouterArc(12,22,111,1);
    r.ajouterArc(22,20,1,1);
    r.ajouterArc(20,18,10,1);
    r.ajouterArc(20,16,2,1);
    r.ajouterArc(16,18,1,1);
    r.ajouterArc(12,14,1,1);
    r.ajouterArc(14,16,4,1);
    r.ajouterArc(22,18,1,1);
    std::vector<unsigned int>  chemin;
    r.dijkstra(12,18,chemin);
    for (unsigned int k : chemin){
    	cout << k << endl;
    }
    r.meilleurPlusCourtChemin(12,18,chemin);
    for (unsigned int k : chemin){
    	cout << "Meilleur" << endl;
    	cout << k << endl;*/
    //}

    double totalMeilleur = 0;
    double totalBelleman = 0;
    double totalDijkstra = 0;
    double tempsMoyen;

    cout << "----------------Meilleur--------------------- " <<  endl;
    for (int i=1; i<=20; i++){
    	tempsMoyen = rtc.tester_n_paires_meilleur(500);
    	cout << "Temps moyen de meilleur " << tempsMoyen << endl;
    	totalMeilleur +=  tempsMoyen;
    }
    cout << "--------------------------------------------- " <<  endl;
    cout << "Moyenne des tests: " <<totalMeilleur/20 <<  endl;
    cout << "----------------Belleman--------------------- " <<  endl;

    for (int i=1; i<=20; i++){
    	tempsMoyen = rtc.tester_n_paires_bellman(500);
    	cout << "Temps moyen de bellman " << tempsMoyen << endl;
    	totalBelleman +=  tempsMoyen;
    }
    cout << "--------------------------------------------- " <<  endl;
    cout << "Moyenne des tests: " << totalBelleman/20 <<  endl;
    cout << "----------------Dijsktra--------------------- " <<  endl;
    for (int i=1; i<=20; i++){
    	tempsMoyen = rtc.tester_n_paires_dijsktra(500);
    	cout << "Temps moyen de Dijsktra " << tempsMoyen << endl;
    	totalDijkstra +=  tempsMoyen;
    }
    cout << "--------------------------------------------- " <<  endl;
    cout << "Moyenne des tests: " << totalDijkstra/20 <<  endl;


    return 0;
}
