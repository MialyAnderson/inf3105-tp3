/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique / TP3
 *
 *  Vos noms + codes permanents : Rakotondradano Mialy Anderson RAKM80300506
 */

#include <cstdio>
#include <limits>
#include <math.h>
#include <queue>
#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>
#include <limits>
#include "carte.h"		
#include <utility>

using namespace std;

Carte::Carte() {}

void Carte::vider_carte () {
	indices.clear();
	sommets.clear();
}

Carte::~Carte() {
   vider_carte();
}

int Carte::rechercher (const string sommet) {
	for (int i = 0; i < sommets.size(); i++) {
	   if (sommet == sommets[i].s)
	      return i;
	}
	return -1; 
}

void Carte::ajouter_sommets (const string sommet) {
    Sommet nouveauSommet(sommet);
    sommets.push_back(nouveauSommet);
    sort(sommets.begin(), sommets.end(), [](const Sommet &a, const Sommet &b) {
       return a.s[0] < b.s[0];
    }); 
}

void Carte::inserer_indices () {
	for (int i = 0; i < sommets.size(); i++) {
	   indices[sommets[i].s] = rechercher (sommets[i].s);
	}
}

void Carte::afficher_sommets () {
   for (int i = 0; i < sommets.size(); i++) {
      cout << sommets[i].s << endl;
   }
}

void Carte::afficher_indices () {
   for (map<string, int>::const_iterator it = indices.begin(); it != indices.end(); ++it) {
      cout << "Clé: " << it->first << ", Valeur: " << it->second << endl;
   }
}

void Carte::ajouter_arretes (string depart, string arrive, int poids, string rue) {
   Valeur nouveauValeur(poids, rue);
   int indices_tableau = rechercher(depart);
   int indices_sommets = indices[arrive];
   sommets[indices_tableau].arretesSortantes[indices_sommets] = nouveauValeur;
}

void Carte::afficher_arretes () {
	for (int i = 0; i < sommets.size(); i++) {
		cout << "Sommets : " << sommets[i].s << endl;
		for (map<int, Valeur>::const_iterator it = sommets[i].arretesSortantes.begin(); it != sommets[i].arretesSortantes.end(); ++it) {
        	cout << "Clé: " << it->first << ", Poids: " << it->second.poids << ", Rue: " << it->second.rue << endl;
   		}
	}
}

void Carte::primJarnik() {
	int sommePoids =0;
	int nbSommets = sommets.size();
        vector<int> minCout(nbSommets, numeric_limits<int>::max());
        vector<bool> inclusMST(nbSommets, false);
        minCout[0] = 0; 
        for (int count = 0; count < nbSommets; ++count) {
            int minIndex = -1; 
            int minValue = numeric_limits<int>::max();
            for (int i = 0; i < nbSommets; ++i) {
                if (!inclusMST[i] && minCout[i] < minValue) {
                    minValue = minCout[i];
                    minIndex = i;
                }
            }
            inclusMST[minIndex] = true;
            for (auto &voisin : sommets[minIndex].arretesSortantes) {
                int sommetVoisin = voisin.first;
                int poids = voisin.second.poids;
                if (!inclusMST[sommetVoisin] && poids < minCout[sommetVoisin]) {
                    minCout[sommetVoisin] = poids;
                    cout << sommets[minIndex].s << " - " << sommets[sommetVoisin].s << " : " << poids << endl;
                    sommePoids += poids;
                }
            }
             
        }
        cout << "---" << endl;
        cout << sommePoids << endl;
}



istream& operator >> (istream& is, Carte& carte) {
    string line, rue, deuxPoints, depart, arrive;
    int poids;
    bool apresTiret = false;

    while (getline(is, line)) {
        if (line.empty()) continue;  

        stringstream ss(line);
        if (!apresTiret) {
            if (line == "---") {
                apresTiret = true;
                carte.inserer_indices();
                continue;
            }
            ss >> line;
            carte.ajouter_sommets(line);
        } else {
            ss >> rue;
            if (ss.fail()) break; 

            ss >> deuxPoints >> depart >> arrive >> poids;
            if (ss.fail()) {
                cerr << "Erreur de lecture des détails de l'arête." << endl;
                continue;  
            }

            carte.ajouter_arretes(depart, arrive, poids, rue);
        }
    }

    return is;
}




