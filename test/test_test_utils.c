/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 15/11/23
 *  \file Implementation de réalisation des tests
 **/
/*-----------------------------------------------------------------*/

#include "utils/utils.h"
#include "../src/datatypes/matrix.h"
#include "../src/utils_sd/utils_sd.h"
#include <stdio.h>

void test_unitaire_afficher_listes(){
    List * liste = generer_liste_int(5, 0, 10);
    afficher_liste(liste);
    delete_list(liste);
    printf("fin du test");
}

void test_unitaire_afficher_matrice(){
    Matrix * matrice = generer_matrice_int(3, 4, 0, 10);

    afficher_matrice(matrice);
    
    delete_matrix(matrice);

    printf("fin du test");
}

void test_unitaire_afficher_graphe(){
    Graph * graphe_1 = generer_graphe(4, 6, 1, 9);
   
    afficher_graphe(graphe_1);

    delete_graph(graphe_1);

    printf("fin du test");
}


void test_unitaire_affichage(){
    printf("\ntest d'affichage de liste\n");

    List * liste = generer_liste_int(5, 0, 10);
    afficher_liste(liste);

    clear_list(liste);
    
    char * c = "element char";
    insert_back(liste, c, strlen(c));
    insert_back(liste, c, strlen(c));
    insert_back(liste, c, strlen(c));

    afficher_liste(liste);

    delete_list(liste);

    printf("\ntest d'affichage de matrice : \n");

    Matrix * matrice = generer_matrice_int(3, 4, 0, 10);
    Matrix * matrice2 = generer_matrice_int(5, 3, 20, 100);

    afficher_matrice(matrice);
    afficher_matrice(matrice2);
    
    delete_matrix(matrice);
    delete_matrix(matrice2);
    printf("\ntest d'affichage de graphe : \n");
    
    Graph * graphe_1 = generer_graphe(4, 6, 1, 9);
    Graph * graphe_2 = generer_graphe(5, 9, 4, 20);
   
    afficher_graphe(graphe_1);
    afficher_graphe(graphe_2);

    delete_graph(graphe_1);
    delete_graph(graphe_2);

    printf("\nFin du test\n");
}


int main(int argc, const char * argv[]){
    
  // test_unitaire_affichage(); //OK
    //test_unitaire_afficher_listes(); //OK
   // test_unitaire_afficher_matrice(); //OK

    //test_unitaire_afficher_graphe(); OK
    return 0;
}






