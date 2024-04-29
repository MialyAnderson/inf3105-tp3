/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique / TP3
 *
 *  Vos noms + codes permanents :
 */

#include <cstdio>
#include <limits>
#include <math.h>
#include <queue>
#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>
#include "carte.h"

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

istream& operator >> (istream& is, Carte& carte)
{

    
    return is;
}

int main () {
   Carte carte;
   carte.ajouter_sommets ("a");
   carte.ajouter_sommets ("b");
   carte.ajouter_sommets ("c");
   carte.ajouter_sommets ("d");
   carte.ajouter_sommets ("e");
   carte.ajouter_sommets ("f");
   carte.ajouter_sommets ("g");
   carte.ajouter_sommets ("h");
   carte.ajouter_sommets ("i");
   carte.inserer_indices();
   carte.ajouter_arretes ("a", "b", 4, "rue 0");
   carte.ajouter_arretes ("a", "h", 8, "rue 1");
   carte.ajouter_arretes ("b", "h", 11, "rue 2");
   carte.ajouter_arretes ("b", "c", 8, "rue 3");
   carte.ajouter_arretes ("c", "i", 2, "rue 4");
   carte.ajouter_arretes ("c", "f", 4, "rue 5");
   carte.ajouter_arretes ("c", "d", 7, "rue 6");
   carte.ajouter_arretes ("d", "f", 14, "rue 7");
   carte.ajouter_arretes ("d", "e", 9, "rue 8");
   carte.ajouter_arretes ("e", "f", 10, "rue 9");
   carte.ajouter_arretes ("f", "g", 2, "rue 10");
   carte.ajouter_arretes ("g", "i", 6, "rue 11");
   carte.ajouter_arretes ("g", "h", 1, "rue 12");
   carte.ajouter_arretes ("h", "i", 7, "rue 13");
   carte.afficher_arretes();
   
}

