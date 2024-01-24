/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 15/11/23
 *  \file Implementation de réalisation des tests
 **/
/*-----------------------------------------------------------------*/

#include "../src/methods/condorcet.h"
#include "../src/methods/condorcet_minimax.h"
#include "../src/methods/condorcet_paires.h"
#include "../src/methods/condorcet_schulze.h"
#include "../src/utils_sd/utils_sd.h"
#include "../src/lecture_csv/lecture_csv.h"
#include "utils/utils.h"
#include <stdio.h>

void test_unitaire_condorcet(int argc, char * argv[]) {

    creer_log("log_test.txt");

    Matrix *matrice_votes = generer_matrice_int(3, 2, 1, 10); // recuperer_fichier_vote(argc, argv);
    afficher_matrice(matrice_votes);
    
    Matrix * matrice_duels;
    Graph * graphe_preferences;
    if(argc == 1 || strcmp(argv[2],"1") == 0){
        matrice_duels = initialisation_matrice(matrice_votes);
        afficher_matrice(matrice_duels);

        graphe_preferences = initialisation_graphe(matrice_duels);
    }
    else{
        graphe_preferences = initialisation_graphe(matrice_votes);
    }
    
    afficher_graphe(graphe_preferences);
    
    char *resultat = "vainqueur"; //vainqueur_condorcet(graphe_preferences);

    printf("resultat = %s\n", resultat);
    char messageFin[512];
    sprintf(messageFin, "le resultat obtenue est : %s\n", resultat);
    ajouter_texte_log(messageFin);
    
    delete_graph(graphe_preferences);
    if(argc == 1 || strcmp(argv[2],"1") == 0){
        delete_matrix(matrice_duels);
    }
    delete_matrix(matrice_votes);
   // free(resultat);
    fin_log();
    printf("fin du test\n");

}

void test_unitaire_minimax(int argc, char * argv[]) {

    creer_log("log_test.txt");
    char message[512];

    Matrix *matrice_votes =  recuperer_fichier_vote(argc, argv);
    Matrix * matrice_duels;
    Graph * graphe_preferences;

    if(argc == 1 || strcmp(argv[2],"1") == 0){
        matrice_duels = initialisation_matrice(matrice_votes);
        afficher_matrice(matrice_duels);
        graphe_preferences = initialisation_graphe(matrice_duels);
    }
    else{ 
        graphe_preferences = initialisation_graphe(matrice_votes);
    }

    afficher_graphe(graphe_preferences);
    ajouter_graphe_log(graphe_preferences);


    char *  resultat = main_condorcet_minimax(graphe_preferences);

    printf("resultat = %s\n", resultat);
    
    if(argc == 1 || strcmp(argv[2],"1") == 0){
        delete_matrix(matrice_duels);
    }

    delete_matrix(matrice_votes);
    delete_graph(graphe_preferences);
    free(resultat);

    fin_log();
    printf("fin du test\n");
}

void test_unitaire_paires(int argc, char * argv[]){

    creer_log("log_test.txt");
    char message[512];
    char * resultat;
 
    Matrix *matrice_votes = recuperer_fichier_vote(argc, argv);
    Matrix * matrice_duels;
    Graph * graphe_preferences;
    
    if(argc == 1 || strcmp(argv[2],"1") == 0){
        matrice_duels = initialisation_matrice(matrice_votes);
        afficher_matrice(matrice_duels);

        graphe_preferences = initialisation_graphe(matrice_duels);
    }
    else{
        graphe_preferences = initialisation_graphe(matrice_votes);
    }

    afficher_matrice(matrice_votes);
    afficher_graphe(graphe_preferences);
    ajouter_graphe_log(graphe_preferences);

    resultat =  main_condorcet_paires(graphe_preferences);


    printf("resultat = %s\n", resultat);
    
    if(argc == 1 || strcmp(argv[2],"1") == 0){
        delete_matrix(matrice_duels);
    }
    delete_matrix(matrice_votes);
    delete_graph(graphe_preferences);
    free(resultat);
    
    fin_log();
    printf("fin du test\n");
}

void test_unitaire_schulze(int argc, char * argv[]) {

    creer_log("log_test.txt");
    char message[512];
    Matrix *matrice_votes =  recuperer_fichier_vote(argc, argv);

    Matrix * matrice_duels;
    Graph * graphe_preferences;
    if(argc == 1 || strcmp(argv[2],"1") == 0){
        matrice_duels = initialisation_matrice(matrice_votes);
        afficher_matrice(matrice_duels);

            graphe_preferences = initialisation_graphe(matrice_duels);
    }
    else{
        graphe_preferences = initialisation_graphe(matrice_votes);
    }

    afficher_graphe(graphe_preferences);
    ajouter_graphe_log(graphe_preferences);

    char * resultat = main_condorcet_schulze(graphe_preferences);

printf("resultat = %s\n", resultat);

    if(argc == 1 || strcmp(argv[2],"1") == 0){
        delete_matrix(matrice_duels);
    }
    delete_matrix(matrice_votes);
    delete_graph(graphe_preferences);
    free(resultat);

    fin_log();
    printf("fin du test\n");

}

int main(int argc, char *argv[]) {

   //test_unitaire_condorcet(argc,argv); //OK
   // test_unitaire_minimax(argc,argv); //OK
  //  test_unitaire_paires(argc,argv); //OK
    test_unitaire_schulze(argc,argv); //OK
    return 0;
}
