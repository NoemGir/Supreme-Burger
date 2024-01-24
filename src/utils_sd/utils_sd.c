/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 24/10/2023
 *  \brief Implémentation des fonctions utiles
 **/
/*-----------------------------------------------------------------*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils_sd.h"

#define MAX 0
#define MIN 1

bool log_demande = false;
FILE *fichier_log;

/*-------------------------------UTILS----------------------------------*/

void erreur_primitive(char *message, int num_exit) {
    perror(message);
    exit(num_exit);
}

void affichage_uninominale(char *methode, int nbCandidat, int nbVotes, vainqueur *vainqueur) {
    printf(
        " Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s avec score : %0.2f %% \n",
        methode, nbCandidat, nbVotes, vainqueur->nom, vainqueur->score * 100);
}

char *sauvegarde_string(char *string) {

    char *sauv = malloc(strlen(string) + 1);
    memcpy(sauv, string, strlen(string) + 1);
    return sauv;
}

int recherche(List *liste, int *valeur, int categorie) {
    ptrListIterator it = init_listIterator(liste, FORWARD_ITERATION);
    int index = 0;
    int stock_min_max = *((int *)listIterator_data(it));

    for (it = listIterator_next(it); !listIterator_end(it); it = listIterator_next(it)) {

        int val = *((int *)listIterator_data(it));
        if ((categorie == MAX && val > stock_min_max) ||
            ((categorie == MIN && val < stock_min_max))) {

            stock_min_max = val;
            index = listIterator_index_current(it);
        }
    }
    delete_listIterator(it);
    if (valeur != NULL)
        *valeur = stock_min_max;
    return index;
}

int recherche_min(List *liste, int *valeur) { return recherche(liste, valeur, MIN); }
int recherche_max(List *liste, int *valeur) { return recherche(liste, valeur, MAX); }

int recherche_max_tab(int *tab, int longueur, List *autres_max) {
    int score_max = tab[0];
    int id_max = 0;

    for (int i = 1; i < longueur; i++) {

        if (tab[i] == score_max) {

            insert_back(autres_max, &i, sizeof(int));

        } else if (tab[i] > score_max) {
            score_max = tab[i];
            id_max = i;

            clear_list(autres_max);
        }
    }
    return id_max;
}

void liste_dans_fichier(List *liste, FILE *fichier) {

    fprintf(fichier, "%s\r\n", get_list_tag(liste));
    ListIterator *it = init_listIterator(liste, FORWARD_ITERATION);
    int numero;
    char *string;

    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {
        size_t taille = listIterator_data_size(it);

        switch (taille) {
        case sizeof(int):
            numero = *((int *)listIterator_data(it));
            fprintf(fichier, "    - %d \r\n", numero);
            break;
        default:
            string = (char *)listIterator_data(it);
            fprintf(fichier, "    - '%s' \r\n", string);

            break;
        }
    }
    fprintf(fichier, "\r\n\r\n\r\n");
    delete_listIterator(it);
}

void liste_horizontales_dans_fichier(List *liste, FILE *fichier) {

    int numero;
    double num_double;
    char *string;
    char *tag = get_list_tag(liste);
    fprintf(fichier, "%25s : ", tag);

    ListIterator *it = init_listIterator(liste, FORWARD_ITERATION);
    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {
        size_t taille = listIterator_data_size(it);

        switch (taille) {
        case sizeof(int):
            numero = *((int *)listIterator_data(it));
            fprintf(fichier, "%10d     ", numero);
            break;
        case sizeof(double):
            num_double = *((double *)listIterator_data(it));
            fprintf(fichier, "%10.2f     ", num_double);
            break;
        default:
            string = (char *)listIterator_data(it);
            fprintf(fichier, "%15s", string);
            break;
        }
    }
    fprintf(fichier, "\r\n");

    delete_listIterator(it);
}

void matrice_dans_fichier(Matrix *matrice, FILE *fichier) {
    List * nom_colonnes = get_column_names(matrice);
    liste_horizontales_dans_fichier(nom_colonnes, fichier);
    for (int i = 0; i < matrix_rows(matrice); i++) {

        List *ligne = get_row_at(matrice, i);
        liste_horizontales_dans_fichier(ligne, fichier);
    }
    fprintf(fichier, "\r\n\r\n");
    delete_list(nom_colonnes);
}

void graphe_dans_fichier(Graph *graphe, FILE *fichier) {
    int numero;
    char *string;
    List * nodes = get_nodes(graphe);
    List * arcs = get_arcs(graphe);
    liste_dans_fichier(nodes, fichier);

    ListIterator *it = init_listIterator(arcs, FORWARD_ITERATION);

    fprintf(fichier, "%s\r\n", get_list_tag(arcs));

    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {

        Arc *arc = listIterator_data(it);
        fprintf(fichier, " %-20s  ----> %-20s Ponderation : min = %d, max = %d\r\n",
                get_first_node(arc), get_second_node(arc), get_min_weight(arc),
                get_max_weight(arc));
    }

    fprintf(fichier, "\r\n\r\n");

    delete_list(nodes);
    delete_list(arcs);
    delete_listIterator(it);
}

/*-------------------------------LOG----------------------------------*/

void creer_log(char *nom_log) {

    log_demande = true;
    fichier_log = fopen(nom_log, "w");

    if (fichier_log == NULL) {
        fprintf(stderr, " Le fichier_log %s ne peut pas être ouvert\n", nom_log);
        exit(2);
    }

    fprintf(fichier_log,
            "-----------------------------------------------------------------\r\n"
            "|                                                               |\r\n"
            "|                          Fichier Log                          |\r\n"
            "|                                                               |\r\n"
            "-----------------------------------------------------------------\r\n\r\n\r\n");
}

void ajouter_matrice_log(Matrix *matrice) {
    if (log_demande) {
        matrice_dans_fichier(matrice, fichier_log);
    }
}

void ajouter_liste_log(List *liste) {
    if (log_demande) {
        liste_dans_fichier(liste, fichier_log);
    }
}

void ajouter_liste_horizontale_log(List *liste) {
    if (log_demande) {
        liste_horizontales_dans_fichier(liste, fichier_log);
    }
}

void ajouter_graphe_log(Graph *graphe) {
    if (log_demande) {
        graphe_dans_fichier(graphe, fichier_log);
    }
}

void ajouter_texte_log(char *texte) {
    if (log_demande) {
        fprintf(fichier_log, "%s", texte);
        fprintf(fichier_log, "\r\n");
    }
}

void fin_log() {
    if (log_demande) {
        fprintf(fichier_log, "Fin du fichier log");
        fclose(fichier_log);
    }
}
