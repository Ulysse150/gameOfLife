#include "evolution.hpp"


Grille::Grille(int l, int h, int p){
    if (l <=0){
        throw invalid_argument("La largeur de la grille doit etre superieur a .");

    }
    if (h <=0){
        throw invalid_argument("La hauteur de la grille doit etre superieur a .");

    }
    largeur = l;
    hauteur = h;
    generation = 0;
    g = createGrille(largeur, hauteur, p);

    for (int i = 0; i < hauteur ; i++){
        for (int j = 0; j <largeur ; j++){
            if (g[i][j]){
                cellulesVivantes++;
            }
        }
    }

}


Grille::Grille(){

}

Grille::Grille(int l, int h, vector<vector<bool>> layout){
    if (l <=0){
        throw invalid_argument("La largeur de la grille doit etre superieur a .");

    }
    if (h <=0){
        throw invalid_argument("La hauteur de la grille doit etre superieur a .");

    }
    largeur = l;
    hauteur = h;
    generation = 0;
    g =layout;
    cellulesVivantes = 0;

    for (int i = 0; i < hauteur ; i++){
        for (int j = 0; j <largeur ; j++){
            if (g[i][j]){
                cellulesVivantes = cellulesVivantes + 1;
            }
        }
    }
}

Grille lireGrilleDepuisFichier(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);
    if (!fichier) {
        std::cerr << "Erreur lors de l'ouverture du fichier " << nomFichier << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::vector<bool>> grilleTemporaire;
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        std::vector<bool> ligneGrille;
        for (char c : ligne) {
            if (c == '0') {
                ligneGrille.push_back(false);
            } else if (c == '1') {
                ligneGrille.push_back(true);
            }
        }
        grilleTemporaire.push_back(ligneGrille);
    }

    int hauteur = grilleTemporaire.size();
    int largeur = hauteur > 0 ? grilleTemporaire[0].size() : 0;
    Grille grille = Grille(largeur, hauteur,grilleTemporaire);

    return grille;
}

void Grille::vivreCell(int i, int j){
    this->g[i][j] = true;
    totalCellules++;
    cellulesVivantes++;
    }

void Grille::tuerCell(int i, int j){
    this->g[i][j] = false;
    cellulesVivantes--;
    cellulesMortes++;
}

void Grille::action(int i, int j){
    if (i <0 || i >= largeur){
        throw invalid_argument("L'indice x de la cellule doit etre comprise entre 0 et la largeur de la grille - 1.");
    }
    if (j < 0 || j >= hauteur){
        throw invalid_argument("L'indice y de la cellule doit etre comprise entre 0 et la hauteur de la grille - 1.");
    }
    if (this->g[i][j]){
        tuerCell(i,j);
    }else{
        vivreCell(i, j);
    }
}

ostream& operator<<(ostream& out,Grille grille){

    out << "┌";
    for (int j = 0; j < grille.largeur; ++j) {
        out << "─";
    }
    out << "┐\n";

    for (int i = 0; i < grille.hauteur; ++i) {
        out << "│"; 
        for (int j = 0; j < grille.largeur; ++j) {
            if (grille.g[i][j] == 1) {
                out << "*";
            } else {
                out << " ";
            }
        }
        out << "│\n"; 
    }

   
    out << "└";
    for (int j = 0; j < grille.largeur; ++j) {
        out << "─";
    }
    out << "┘\n";

    return out;
}




vector<vector<bool>> createGrille(int l, int h, int p){
    vector<vector<bool>> layout;

    for (int i = 0; i < h; i++){
        layout.push_back(vector<bool>(l, false));
    }

    int largeurCarre = (p*l) / 100;

    int centrex = (l-1) / 2;
    int centrey = (h-1) / 2;
    int debutx =  centrex - largeurCarre/2;
    int debuty =  centrey - largeurCarre/2;
    
    for (int i = debuty; i < debuty + largeurCarre ; i++){
        for (int j = debutx; j < debutx + largeurCarre ; j++){
            layout[i][j] = true;
        }
    }



    return layout;
}

bool caseValide(array<int ,2> C, int h, int l){
    int i = C[0];
    int j = C[1];
    return (( i>= 0) && (i < l) && (j >= 0) && (j < h));
}


vector<array<int,2>> voisins(int i, int j, int h, int l){
    vector<array<int, 2>> rep;

    vector<array<int, 2>> cases = {{i-1,j-1},{i-1,j},{i-1,j+1},{i, j+1},{i+1, j+1},{i+1,j},{i+1, j-1}, {i, j-1}};
    for (long unsigned int x = 0; x < cases.size(); x++){
        if (caseValide(cases[x], h, l)){
            rep.push_back(cases[x]);
        }
    }

    return rep;

}




vector<array<int,2>> cellules(Grille grille){
    vector<array<int,2>> rep;


    for (int i = 0; i < grille.hauteur ; i++){
        for (int j = 0; j < grille.largeur; j++){
            int nbvoisins = 0;
            vector<array<int, 2>> cases = voisins(i, j, grille.hauteur, grille.largeur);

            for (array<int, 2> C:cases){
                if (grille.g[C[0]][C[1]]){
                    nbvoisins++;
                }

            }

            if (grille.g[i][j]){
                if (nbvoisins < 2 || nbvoisins > 3){
                    rep.push_back({i, j});
                }
            }else{
                if (nbvoisins ==3){
                    rep.push_back({i,j});
                }
            }



        }
    }return rep;
}


void Grille::tour(){
    vector<array<int, 2>> cel = cellules(*this);

    for (array<int, 2> C:cel){
        int i = C[0];
        int j = C[1];
        action(i, j);
    }
    generation = generation + 1;

    int cpt = 0;
    for (int i = 0; i < hauteur; i++){
        for (int j = 0; j < largeur; j++){
            if (g[i][j] == 1){
                cpt = cpt + 1;
            }
        }
    }
    cellulesVivantes = cpt;

}