/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 15/11/23
 *  \file Implementation de réalisation des tests
 **/
/*-----------------------------------------------------------------*/

#include "../src/datatypes/matrix.h"
#include "utils/utils.h"
#include <stdio.h>

void test_unitaire_affichage() {

    printf("\ntest d'affichage de matrice : \n");

    Matrix *matrice = generer_matrice_int(3, 4, 0, 10);

    afficher_matrice(matrice);

    delete_matrix(matrice);

    printf("\nFin du test\n");
}

void test_unitaire_get_element_at() {
    Matrix *matrice = generer_matrice_int(3, 4, 0, 10);
    afficher_matrice(matrice);

    for (int i = 0; i < matrix_rows(matrice); i++) {
        for (int j = 0; j < matrix_cols(matrice); j++) {
            printf("matrice[%d,%d] = %d\n", i, j, *((int *)matrix_get_element_at(matrice, i, j)));
        }
    }
    delete_matrix(matrice);
}

void test_unitaire_set_element_at() {
    Matrix *matrice = generer_matrice_int(3, 4, 1, 10);
    afficher_matrice(matrice);
    int nb = 0;
    printf("transformation matrice avec des valeurs uniquement a 0 \n\n");
    for (int i = 0; i < matrix_rows(matrice); i++) {
        for (int j = 0; j < matrix_cols(matrice); j++) {
            printf("matrice[%d,%d] = %d\t", i, j, *((int *)matrix_get_element_at(matrice, i, j)));
            matrix_set_element_at(matrice, i, j, &nb, sizeof(int));
            printf("nouvelle valeur matrice[%d,%d] = %d\n", i, j,
                   *((int *)matrix_get_element_at(matrice, i, j)));
        }
    }
    afficher_matrice(matrice);
    delete_matrix(matrice);
}

void test_unitaire_insert_row() {
    Matrix *matrice = generer_matrice_int(3, 3, 0, 5);
    afficher_matrice(matrice);

    List *l1 = generer_liste_int(3, 5, 10);
    List *l2 = generer_liste_int(3, 15, 17);
    List *l3 = generer_liste_int(3, 10, 15);

    printf("insertion d'une ligne au debut de la matrice \n");
    afficher_liste(l1);
    insert_row_front(matrice, l1);
    afficher_matrice(matrice);

    printf("insertion d'une ligne a la position 2 de la matrice \n");
    afficher_liste(l2);

    insert_row_at(matrice, l2, 2);
    afficher_matrice(matrice);

    printf("insertion d'une ligne à la fin de la matrice \n");
    afficher_liste(l3);

    insert_row_back(matrice, l3);
    afficher_matrice(matrice);

    delete_matrix(matrice);

    printf("fin test insert_row\n");
}

void test_unitaire_getset_row() {
    Matrix *matrice = generer_matrice_int(3, 3, 0, 5);
    afficher_matrice(matrice);
    ptrList l;

    List *l1 = generer_liste_int(3, 5, 10);
    List *l2 = generer_liste_int(3, 15, 17);

    printf("affichage de la matrice ligne par ligne\n");
    for (int i = 0; i < matrix_rows(matrice); i++) {
        l = get_row_at(matrice, i);
        afficher_liste(l);
    }

    printf("set row suivante dans la position 1 :\n");
    afficher_liste(l1);
    set_row_at(matrice, l1, 1);
    afficher_matrice(matrice);

    printf("set row suivante dans la position 2 :\n");
    afficher_liste(l2);
    set_row_at(matrice, l2, 2);
    afficher_matrice(matrice);

    delete_matrix(matrice);

    printf("fin test get et set row pour matrices \n");
}

void test_unitaire_delete_row() {
    Matrix *matrice = generer_matrice_int(5, 3, 0, 5);
    afficher_matrice(matrice);

    printf("suppression ligne 3\n");
    delete_row_at(matrice, 2);
    afficher_matrice(matrice);

    printf("suppression 1re ligne \n");
    delete_first_row(matrice);
    afficher_matrice(matrice);

    printf("suppression derniere ligne \n");
    delete_last_row(matrice);
    afficher_matrice(matrice);

    delete_matrix(matrice);
    printf("fin test delete_row\n");
}

void test_unitaire_tag() {
    Matrix *matrice = generer_matrice_int(5, 3, 0, 5);
    afficher_matrice(matrice);

    printf("affichage noms colomnes\n");
    ptrList nomsCol = get_column_names(matrice);
    afficher_liste(nomsCol);

    printf("affichage noms lignes\n");
    ptrList nomsLignes = get_row_names(matrice);
    afficher_liste(nomsLignes);

    printf("modification du tag d'une ligne\n");
    char *nom = get_tag_row(matrice, 2);
    printf("ancien nom de la ligne : %s  ", nom);
    set_tag_row(matrice, 2, "ligne N");
    nom = get_tag_row(matrice, 2);
    printf("devient: %s\n", nom);

    afficher_matrice(matrice);

    printf("modification du tag d'une colonne\n");
    nom = get_tag_column(matrice, 2);
    printf("ancien nom de la colonne : %s  ", nom);
    set_tag_column(matrice, 2, "colonne X");
    nom = get_tag_column(matrice, 2);
    printf("devient: %s\n", nom);

    afficher_matrice(matrice);

    delete_list(nomsLignes);
    delete_matrix(matrice);
    delete_list(nomsCol);
    printf("fin test tag\n");
}

void test_unitaire_getcol() {
    Matrix *matrice = generer_matrice_int(3, 5, 0, 15);
    afficher_matrice(matrice);
    ptrList l;
    printf("affichage de la matrice par colonne\n");

    for (int i = 0; i < matrix_cols(matrice); i++) {
        l = get_col_at(matrice, i);
        afficher_liste(l);
        delete_list(l);
    }

    printf("affichage premiere colonne \n");
    l = get_first_col(matrice);
    afficher_liste(l);
    delete_list(l);

    printf("affichage derniere colonne \n");
    l = get_last_col(matrice);
    afficher_liste(l);
    delete_list(l);

    delete_matrix(matrice);

    printf("fin test des get_column\n");
}

int main(int argc, const char *argv[]) {

    test_unitaire_affichage(); // marche sans probleme
    // test_unitaire_get_element_at(); //marche sans probleme
    // test_unitaire_insert_row(); //marche sans probleme
    // test_unitaire_getset_row(); // marche sans probleme
    // test_unitaire_delete_row(); // marche sans segFault
    // test_unitaire_tag(); // marche sans segFault
    // test_unitaire_getcol(); // marche sans segFault
    // test_unitaire_set_element_at(); //marche sans probleme
    return 0;
}
