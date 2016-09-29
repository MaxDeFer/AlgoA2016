/*
 * Main.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */

#include <iostream>
#include "Coordonnees.h"
#include <vector>
#include "Auxiliaires.h"
using namespace std;


void printVector(vector<int> vect)
{
	for (int i = 0; i<vect.size();i++)
	{
		cout<<vect[i]<<endl;
	}
}

int main()
{
	Coordonnees test = Coordonnees(12.1,12.1);

	cout << test << endl;

	vector<int> test1;

	for (int i = 0; i<4; i++)
	{
		test1.push_back(i);
		cout<<test1[i]<<endl;
	}

	vector<vector<int>> vecteur1(10, vector<int>(10));
	for (int i = 0; i<4; i++)
	{

		for (int j=0;j<4;j++)
		{
			vecteur1[i][j] = i+j;
			cout<<"Colonne"<<j<<", Ligne"<<i<<"Valeur du vecteur:"<<vecteur1[i][j]<<endl;
		}
	}
	cout<<vecteur1[0][1];

	printVector(vecteur1[0]);

	Heure uneHeure(23,59,59);
	Heure autreHeure = uneHeure.add_secondes(3601);
	cout<<"Test operateurs"<<endl;
	cout<<(uneHeure<uneHeure)<<endl;
	cout<<(uneHeure<=uneHeure)<<endl;
	cout<<(uneHeure>uneHeure)<<endl;
	cout<<(uneHeure>=uneHeure)<<endl;
	cout<<(uneHeure==uneHeure)<<endl;
	cout<<(uneHeure==uneHeure)<<endl;
	cout<<(autreHeure-uneHeure)<<endl;


	std::string testString = "Test:Ok:Yo";
	std::vector<std::string> testVector = split(testString, ':');
	for (int i = 0; i < testVector.size(); i++)
	{
		cout<<testVector[i]<<endl;
	}


	return 0;



}

