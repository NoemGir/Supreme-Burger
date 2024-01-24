/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author MARTIN Benoit
 *  \date 07/09/2023
 *  \brief Implémentation de la lecture des fichiers csv
 **/
/*-----------------------------------------------------------------*/

#include "../datatypes/list.h"
#include "../datatypes/matrix.h"
#include "../utils_sd/utils_sd.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1000

FILE *ouvrir_fichier_lecture(char *nomFichier) {
    FILE *csvFile = fopen(nomFichier, "r");
    if (csvFile == NULL) {
        erreur_primitive("Erreur lors de l'ouverture du fichier CSV", 1);
    }
    return csvFile;
}

ptrMatrix remplir_matrice_duel(char *nomFichier) {
    FILE *fichier_vote = ouvrir_fichier_lecture(nomFichier);
    char buffer[512];
    char nomcol[128];
    int nombre;
    int i = 0;
    char tag[20];
    int ligne = 1;
    bool inc;
    int nbcol = 0;
    int compteur = 0;
    char *curseur;
    int taille;

    ptrList nomColonnes = init_list();
    set_list_tag(nomColonnes, "nomColonnes");
    if (fgets(buffer, sizeof(buffer), fichier_vote) == NULL) {
        perror("erreur lors de l'appel à fgets");
        exit(2);
    }
    // traitement ligne d'initialisation
    curseur = buffer;
    while (*curseur != '\0') {
        if (*curseur == ',') {
            curseur++;
            nbcol++;
            nomcol[i] = ' ';
            taille = i - 1;
            if (taille == 8 || taille == 4) {
                strcat(nomcol, " ");
                taille += 1;
            }
            insert_back(nomColonnes, nomcol, taille);
            for (int j = 0; j < i; j++) {
                nomcol[j] = ' ';
            }
            i = 0;
        }
        nomcol[i] = *curseur;
        curseur++;
        i++;
    }
    taille = i - 2;
    if (taille == 8 || taille == 4) {
        strcat(nomcol, " ");
        taille += 1;
    }
    insert_back(nomColonnes, nomcol, taille);
    i = 0;
    // initialisation matrice
    ptrMatrix matrice_duel = init_matrix(nomColonnes);
    // traitement des lignes de votes
    ptrList duel = init_list();

    while (fgets(buffer, sizeof(buffer), fichier_vote) != NULL) {
        curseur = buffer;

        while (sscanf(curseur, "%d", &nombre) > 0) {

            do {
                curseur++;
            } while (*curseur != ',' && *curseur != ' ');
            curseur++;
            inc = true;
            insert_back(duel, &nombre, sizeof(nombre));
            if (i == nbcol) {
                i = 0;
                inc = false;
                sprintf(tag, "%d", ligne);
                set_list_tag(duel, tag);
                ligne++;
                insert_row_back(matrice_duel, duel);
                duel = init_list();
            }
            if (inc)
                i++;
        }
    }
    delete_list(duel);
    fclose(fichier_vote);
    return matrice_duel;
}

ptrMatrix remplir_matrix(char *nomFichier) {
    FILE *fichier_vote = ouvrir_fichier_lecture(nomFichier);
    char buffer[512];
    char nomcol[128];
    int nombre;
    int i = 0;
    int ligne = 1;
    char tag[20];
    bool inc;
    int nbcol = 0;
    int compteurv = 0;
    char *curseur;
    int taille;

    // traitement ligne d'initialisation
    ptrList nomColonnes = init_list();
    set_list_tag(nomColonnes, "nomColonnes");
    if (fgets(buffer, sizeof(buffer), fichier_vote) == NULL)
        erreur_primitive("erreur lors de l'appel à fgets", 2);
    curseur = buffer;
    while (compteurv != 4) {
        if (*curseur == ',') {
            compteurv++;
        }
        curseur++;
    }
    while (*curseur != '\0') {
        if (*curseur == ',') {
            curseur++;
            nbcol++;
            nomcol[i] = ' ';
            taille = i - 1;
            if (taille == 8 || taille == 4) {
                strcat(nomcol, " ");
                taille += 1;
            }
            insert_back(nomColonnes, nomcol, taille);
            for (int j = 0; j < i; j++) {
                nomcol[j] = ' ';
            }
            i = 0;
        }
        nomcol[i] = *curseur;
        curseur++;
        i++;
    }
    taille = i - 3;
    if (taille == 8 || taille == 4) {
        strcat(nomcol, " ");
        taille += 1;
    }
    insert_back(nomColonnes, nomcol, taille);
    i = 0;
    // initialisation matrice
    ptrMatrix matrice_vote = init_matrix(nomColonnes);

    // traitement des lignes de votes
    ptrList vote = init_list();
    while (fgets(buffer, sizeof(buffer), fichier_vote) != NULL) {
        compteurv = 0;
        curseur = buffer;
        while (compteurv != 4) {
            if (*curseur == ',') {
                compteurv++;
            }
            curseur++;
        }
        while (sscanf(curseur, "%d", &nombre) > 0) {
            do {
                curseur++;
            } while (*curseur != ',');
            curseur++;

            inc = true;
            insert_back(vote, &nombre, sizeof(nombre));
            if (i == nbcol) {
                i = 0;
                inc = false;
                sprintf(tag, "vote %d", ligne);
                set_list_tag(vote, tag);
                ligne++;
                insert_row_back(matrice_vote, vote);
                vote = init_list();
            }
            if (inc)
                i++;
        }
    }
    delete_list(vote);
    fclose(fichier_vote);
    return matrice_vote;
}

ptrMatrix main_lecture_csv(char *nomFichier, int choix) {
    ptrMatrix matrice;
    if (choix == 1)
        matrice = remplir_matrix(nomFichier);
    if (choix == 2)
        matrice = remplir_matrice_duel(nomFichier);

    return matrice;
}
