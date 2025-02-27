#include "evolution.hpp"
#include <cstdlib>
#include <string>
int main(int argc, char* argv[]){
    Grille grille;
    int l, h, p;
    if (argc == 4){
         l = atoi(argv[1]);
         h = atoi(argv[2]);
         p = atoi(argv[3]);
         grille = Grille(l, h, p);
    }else{
        if (argc == 2){
            string file = argv[1];
            grille = lireGrilleDepuisFichier(file);
            
        }else{
             l = 20;



            h = 20;
            p = 80;
            grille = Grille(l, h, p);
        }
    }

    
    
    std::cout << grille;
    string s;
    string numero_text = "Turn : ";





    do{
        if (grille.cellulesVivantes > 0){
            std::cout << "Turn : " << grille.generation <<endl;
            std::cout << "Alives cells : "<<grille.cellulesVivantes<<endl;
            s = getchar();
            grille.tour();
            std::cout << grille <<endl;
    
        }else{
            
        }
       
    }while (s == "\n" and grille.cellulesVivantes != 0);

    if (grille.cellulesVivantes == 0){
        cout << "Simulation ended. All cells died after "<< grille.generation << " generations "<<endl;
    }else{
        std::cout << grille;
    }
    
   
    return 0;
}