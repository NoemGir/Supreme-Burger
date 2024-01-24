/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 15/11/23
 *  \file Implementation de réalisation des tests
 **/
/*-----------------------------------------------------------------*/

#include "utils/utils.h"
#include "../src/lecture_csv/lecture_csv.h"
#include "../src/datatypes/matrix.h"
#include <stdio.h>



void test_differents_fichiers(char * nomFichier, int mode){
    Matrix * matrice = main_lecture_csv(nomFichier, mode);
    afficher_matrice(matrice);
    delete_matrix(matrice);
}


void test_lecture_csv_generation(){

    Matrix * matrice_vote = recuperer_generation_test();
    afficher_matrice(matrice_vote);
    delete_matrix(matrice_vote);

}

int main(int argc, const char * argv[]){
    if(argc !=  3) {
        fprintf(stderr, "Usage : %s nomFichier mode(1 : vote, 2: duel)", argv[0]);
        exit(1);
    }

    char * nomFichier = (char *) argv[1];
    int mode = atoi(argv[2]);

    test_differents_fichiers(nomFichier, mode);
    return 0;
}






