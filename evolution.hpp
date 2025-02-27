#include <iostream>
#include <vector>
#include <array>
#include <fstream>

using namespace std;

class Grille{
    public:
        int largeur;
        int hauteur;
        //au début on créé un carré centre de dimension en fonction de 
        // la largeur et du pourcentage
        double pourcentage;
        
        //nombre de cellules vivantes actuellement
        int cellulesVivantes;

        //nombre de cellules mortes actuellement
        int cellulesMortes;

        //nombre cellules ayant vécu depuis le début de la simulation
        int totalCellules;
        
        //On tue une cellule vivante aux coordonees (i,j)
        //on diminue cellulesVivantes et on augmente cellulesMortes
        void tuerCell(int i, int j);
        
        //met une cellule vivante aux coordonées (i,j)
        //on augmente egalement cellulesVivantes et totalCellules
        void vivreCell(int i, int j);

        // interagit avec une cellule en (i,j)
        void action(int i, int j);

        vector<vector<bool>> g;
        Grille(int l, int h, int p);
        Grille(int l, int h, vector<vector<bool>> layout);
        Grille();
        //on effectue un tour
        void tour();

        int generation;
};
ostream& operator<<(ostream& out,Grille grille);
vector<vector<bool>> createGrille(int l, int h, int p);
Grille lireGrilleDepuisFichier(const std::string& nomFichier);

//renvoie toutes les positions des voisins 
//d'une cellulle, on fait comme si la position
//de la cellule en question est valable
//si il n'y a pas d'erreurs possibles
vector<array<int,2>> voisins(int i, int j, int l, int h);

vector<array<int,2>> cellules(Grille grille);

//renvoie si une case existe pour une taille de grille donnée
bool caseValide(int i, int j, int l, int h);
