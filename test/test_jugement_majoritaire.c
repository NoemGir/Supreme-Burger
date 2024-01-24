/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 15/11/23
 *  \file Implementation de réalisation des tests
 **/
/*-----------------------------------------------------------------*/

#include "../src/datatypes/matrix.h"
#include "../src/methods/jugement_majoritaire.h"
#include "../src/utils_sd/utils_sd.h"
#include "utils/utils.h"
#include <stdio.h>

void test_unitaire_jugement_majoritaire(int argc, char * argv[]) {

    
    char * resultat;
    if(argc != 1 && argc != 4){
        fprintf(stderr,"Utils %s nomFichier mode(1-> vote et 2 -> duel) categorie(1->jugement et 2 -> condorcet)\n", argv[0]);
        exit(1);

    }
    if(argc == 3 && atoi(argv[2]) == 2){
        fprintf(stderr,"Vous ne pouvez pas utiliser une matrice de duel pour calculer le vainqueur par jugement majoritaire\n");
        exit(2);
    }
   creer_log("log_test.txt");
    Matrix *matrice_votes;
    if(argc == 1){
        matrice_votes =  generer_matrice_int(20, 5, 1, 6);
    }
    else{
        matrice_votes =  recuperer_fichier_vote(argc, argv);
    }
    
    afficher_matrice(matrice_votes);

    if(argc == 1 || atoi(argv[3]) == 2){
        resultat = main_jugement_majoritaire(matrice_votes, CONDORCET);
    }
    else{
        resultat = main_jugement_majoritaire(matrice_votes, JUGEMENT);
    }
    printf("resultat = %s\n", resultat);

    char messageFin[512];
    sprintf(messageFin, "le resultat obtenue est : %s\n", resultat);
    ajouter_texte_log(messageFin);

    free(resultat);
    
    delete_matrix(matrice_votes);
    fin_log();
}

int main(int argc, char *argv[]) {

    test_unitaire_jugement_majoritaire(argc, argv);
    return 0;
}
