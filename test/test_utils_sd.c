/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 15/11/23
 *  \file Implementation de réalisation des tests
 **/
/*-----------------------------------------------------------------*/

#include "../src/datatypes/matrix.h"
#include "../src/utils_sd/utils_sd.h"
#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h>

void test_unitaire_log() {
    printf("\ntest creation d'un fichier\n");
    creer_log("log_test.txt");

    printf("\ntest d'écriture dans un fichier\n");
    ajouter_texte_log("Creation du log : success!");

    printf("\ntest d'écriture de listes dans un fichier\n");
    List *liste = generer_liste_int(5, 0, 10);
    ajouter_texte_log("Ajouter une liste de int : ");
    ajouter_liste_log(liste);
    delete_list(liste);

    liste = generer_liste_int(7, 6, 20);
    ajouter_texte_log("Ajouter une liste horizontale de int : ");
    ajouter_liste_horizontale_log(liste);

    clear_list(liste);

    char *c = "element char";
    insert_back(liste, c, strlen(c));
    insert_back(liste, c, strlen(c));
    insert_back(liste, c, strlen(c));
    ajouter_texte_log("Ajouter une liste de char : ");
    ajouter_liste_log(liste);
    ajouter_texte_log("Ajouter une liste horizontale de char : ");
    ajouter_liste_horizontale_log(liste);

    printf("\ntest d'écriture de matrice dans un fichier\n");

    Matrix *matrice = generer_matrice_int(3, 4, 0, 10);
    ajouter_texte_log("Ajouter une matrice de int : ");
    ajouter_matrice_log(matrice);

    delete_matrix(matrice);
    delete_list(liste);

    fin_log();

    printf("\nFin du test\n");
}

void test_unitaire_rechercheMin() {

    printf("debut test recherche Min\n");

    ptrList l1 = generer_liste_int(10, 0, 15);
    ptrList l2 = generer_liste_int(15, -5, 25);
    ptrList l3 = generer_liste_int(5, -10, 0);

    int ind1, min1, ind2, min2, ind3, min3;
    ind1 = recherche_min(l1, &min1);
    ind2 = recherche_min(l2, &min2);
    ind3 = recherche_min(l3, &min3);

    afficher_liste(l1);
    printf("minimum de la liste est à la position %d: %d\n\n", ind1 + 1, min1);

    afficher_liste(l2);
    printf("minimum de la liste est à la position %d: %d\n\n", ind2 + 1, min2);

    afficher_liste(l3);
    printf("minimum de la liste est à la position %d: %d\n\n", ind3 + 1, min3);

    delete_list(l1);
    delete_list(l2);
    delete_list(l3);

    printf("fin test recherche Min\n");
}

void test_unitaire_rechercheMax() {

    printf("debut test recherche Max\n");

    ptrList l1 = generer_liste_int(10, 0, 15);
    ptrList l2 = generer_liste_int(15, -5, 25);
    ptrList l3 = generer_liste_int(5, -10, 0);

    int ind1, max1, ind2, max2, ind3, max3;
    ind1 = recherche_max(l1, &max1);
    ind2 = recherche_max(l2, &max2);
    ind3 = recherche_max(l3, &max3);

    afficher_liste(l1);
    printf("maximum de la liste est à la position %d: %d\n\n", ind1 + 1, max1);

    afficher_liste(l2);
    printf("maximum de la liste est à la position %d: %d\n\n", ind2 + 1, max2);

    afficher_liste(l3);
    printf("maximum de la liste est à la position %d: %d\n\n", ind3 + 1, max3);

    delete_list(l1);
    delete_list(l2);
    delete_list(l3);

    printf("fin test recherche Max\n");
}

void test_unitaire_rechercheMaxTab() {
    printf("debut test rechercheMax tableau\n");

    int taille = 10;

    int max1, max2;

    int *tab1 = (int *)malloc(taille * sizeof(int));
    int *tab2 = (int *)malloc(taille * sizeof(int));

    if (tab1 == NULL || tab2 == NULL) {
        fprintf(stderr, "Allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));

    ptrList l1, l2;

    printf("init tableaux\n");
    for (int i = 0; i < taille; ++i) {
        tab1[i] = rand() % 10;
        printf("tab1 : %d \t", tab1[i]);
        tab2[i] = rand() % 10;
        printf("tab2 : %d \n", tab2[i]);
    }
       
    l1 = init_list(); 
    max1 = recherche_max_tab(tab1, taille, l1);
    printf("max du tableau est %d, et il est present %d dans le tableau\n", tab1[max1],
           list_size(l1) + 1);

    l2 = init_list();
    max2 = recherche_max_tab(tab2, taille, l2);
    printf("max du tableau est %d, et il est present %d dans le tableau\n", tab2[max2],
           list_size(l2) + 1);
    
    free(tab1);
    free(tab2);
    delete_list(l1);
    delete_list(l2);

    printf("fin test \n\n");
}

void test_ecriture_fichier() {
    FILE *file = fopen("fichier_tests.txt", "w+");
    if (file == NULL) {
        erreur_primitive("Erreur lors de l'ouverture du fichier", 1);
    }
    printf("ajout liste dans fichier : ");
    ptrList liste = generer_liste_char(15);
    afficher_liste(liste);
    liste_dans_fichier(liste, file);
    delete_list(liste);
    printf("\n********************\n");

    printf("ajout liste horizontale dans fichier : ");
    ptrList liste2 = generer_liste_int(10, 0, 15);
    afficher_liste(liste2);
    liste_dans_fichier(liste2, file);
    delete_list(liste2);

    printf("\n********************\n");

    printf("ajout matrice dans fichier : ");
    ptrMatrix matrice = generer_matrice_int(2, 2, 0, 10);
    afficher_matrice(matrice);
    matrice_dans_fichier(matrice, file);
    delete_matrix(matrice);

    printf("\n********************\n");

    printf("ajout graphe dans fichier : ");
    ptrGraph g = init_graph();
    insert_node(g, "hello");

    graphe_dans_fichier(g, file);
    delete_graph(g);
    printf("\n********************\n");
    fclose(file);
    printf(
        "fin test fonctions fichier : voir les changements dans le fichier : fichier_tests.txt\n");
}

int main(int argc, const char *argv[]) {
    // test_unitaire_log(); // marche sans probleme
    // test_unitaire_rechercheMin(); // marche sans probleme
    // test_unitaire_rechercheMax(); // marche sans probleme
    // test_unitaire_rechercheMaxTab(); // marche sans probleme
     //test_ecriture_fichier(); // marche sans problème
    return 0;
}
