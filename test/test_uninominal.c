/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 15/11/23
 *  \file Implementation de réalisation des tests
 **/
/*-----------------------------------------------------------------*/

#include "../src/methods/uninominales.h"
#include "utils/utils.h"

#include "../src/datatypes/matrix.h"
#include "../src/utils_sd/utils_sd.h"

#include <stdio.h>

void test_uninominal_1_tour(int argc, char *argv[]) {

    // Matrix *matrice_votes = generer_matrice_int(15, 10, 1, 10);
    Matrix *matrice_votes = recuperer_fichier_vote(argc, argv);

    if (argc == 3 && atoi(argv[2]) == 2) {
        fprintf(stderr, "Vous ne pouvez pas utiliser une matrice de duel pour calculer le resultat "
                        "uninominal\n");
        exit(2);
    }

    char texteLog[100];
    printf("Vous avez choisi pour methode uni 1 tour\n");
    creer_log("log_test.txt");

    afficher_matrice(matrice_votes);
    vainqueur resultat = main_uninominale_1(matrice_votes);

    printf("vainqueur est  %s avec score %f\n", resultat.nom, resultat.score);

    delete_matrix(matrice_votes);
    fin_log();
}

void test_uninominal_2_tours(int argc, char *argv[]) {

    Matrix *matrice_votes = recuperer_fichier_vote(argc, argv);

    if (argc == 2 && atoi(argv[2]) == 2) {
        fprintf(stderr, "Vous ne pouvez pas utiliser une matrice de duel pour calculer le resultat "
                        "uninominal\n");
        exit(2);
    }

    // Matrix *matrice_votes = generer_matrice_int(15, 10, 1, 10);
    printf("\n");

    afficher_matrice(matrice_votes);
    printf("\n");
    creer_log("log_test.txt");

    vainqueur resultat = main_uninominale_2(matrice_votes);

    printf("vainqueur est  %s avec score %f\n", resultat.nom, resultat.score);

    delete_matrix(matrice_votes);
    fin_log();
}

int main(int argc, char *argv[]) {
    test_uninominal_1_tour(argc, argv);
    test_uninominal_2_tours(argc, argv);
    return 0;
}
