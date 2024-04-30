/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique / TP3
 *
 *  Vos noms + codes permanents : Rakotondradano Mialy Anderson RAKM80300506
 */
 
#if !defined(_CARTE__H_)
#define _CARTE__H_
#include <cassert>
#include <istream>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

class Carte{
  public:
     Carte();
     ~Carte();
     void ajouter_sommets (const string sommet);
     void vider_carte (); 
     int rechercher (const string sommet); 
     void inserer_indices ();
     void afficher_sommets ();
     void afficher_indices ();
     void ajouter_arretes (string depart, string arrive, int poids, string rue);
     void afficher_arretes ();
     void primJarnik();
     
     
	 struct Valeur {
     		Valeur() : poids(0), rue("") {}
     		Valeur (const int &poids_, const string &rue_) : poids(poids_), rue(rue_) {}
     		int poids;
     		string rue;  
    };   
    
    struct Sommet {
        	Sommet(const string& s_): s(s_){}
        	string s;
        	map<int, Valeur> arretesSortantes;
        	Sommet& operator = (const Sommet &autre) {
        		if (this != &autre) {
        			s = autre.s;
        			arretesSortantes = autre.arretesSortantes;
        		}
        		return *this;
        	}
     };
  
  private:
     map<string, int> indices;
     vector<Sommet> sommets;
  friend istream& operator >> (istream& is, Carte& carte);
};

#endif

