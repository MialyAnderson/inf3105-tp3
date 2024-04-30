#if !defined(_MONCEAU__H_)
#define _MONCEAU__H_

#include <vector>
#include <iostream>
#include "carte.h"

using namespace std;

class Monceau {
	private:
		vector<Carte::Arrete> valeurs;
		int parent (int indice) const { return (indice - 1)/2;}
		int enfant1 (int indice) const { return 2*indice + 1;}
		int enfant2 (int indice) const { return 2*indice + 2;}
		void remonter (int indice);		
		void descendre (int indice);
		void echanger (Carte::Arrete &arrete1, Carte::Arrete &arrete2); 
	public :
		void inserer (const Carte::Arrete& arrete);
		const Carte::Arrete& minium () const;
		Carte::Arrete enleverMinimum (); 
		bool estVide ();
		void modifier (Carte::Arrete &arrete);
		int recherche (const string s);
};

bool Monceau::estVide () {
	return valeurs.size() == 0;
}

void Monceau::echanger (Carte::Arrete &arrete1, Carte::Arrete &arrete2) {
	Carte::Arrete temp = arrete1;
	arrete1 = arrete2;
	arrete2 = temp;
} 

void Monceau::remonter (int indice) {
	if (indice == 0) return;
	int p = parent (indice);
	if (valeurs[indice] < valeurs[p]) {
		echanger(valeurs[indice], valeurs[p]);
		remonter(p);
	}
}

void Monceau::inserer (const Carte::Arrete& arrete) {
	int indice = valeurs.size();
	valeurs.push_back(arrete);
	remonter(indice);
}

Carte::Arrete Monceau::enleverMinimum () {
	Carte::Arrete arrete = valeurs[0];
	valeurs[0] = valeurs[valeurs.size() - 1];
	valeurs.pop_back(); 
	descendre(0);
	return arrete;
}

void Monceau::descendre (int indice) {
	int suivant = enfant1(indice);
	if (suivant>= valeurs.size()) return;
	if (suivant + 1 < valeurs.size() && valeurs[suivant + 1] < valeurs[suivant])
		suivant++;
	if (valeurs[suivant] < valeurs[indice]) {
		echanger(valeurs[suivant], valeurs[indice]);
		descendre(suivant);
	} 
}

void Monceau::modifier (Carte::Arrete &arrete) {
	int indice = 0;
	for (int i = 0; i < valeurs.size(); i++) {
		if (arrete.sommetArrive->s == valeurs[i].sommetDepart.s) {
			indice = i;
			valeurs[i] = arrete;
			cout << valeurs[i].poids << endl;
		}
	}
	
	remonter(indice);
}

int Monceau::recherche (const string s) {
	for (int i = 0; i < valeurs.size(); i++) {
		if (valeurs[i].sommetArrive->s == s) 
			return valeurs[i].poids;
	}
	return numeric_limits<int>::max();
}

#endif
