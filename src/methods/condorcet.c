/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author RADIONOVA Veronika
 *  \date 28/10/23
 *  \file Implémentation des calculs du resultat du vote grace à la methode de Condorcet ( sans paradoxe )
 **/
/*-----------------------------------------------------------------*/
#include <stdio.h>

#include "../datatypes/matrix.h"
#include "../datatypes/graph.h"
#include "../utils_sd/utils_sd.h"

#include "condorcet.h"


/**
 *  \brief générer une matrice des duels à partir d'une matrice des votes (nouvelle forme des fishiers csv)
 et un graphe des préférences à partir d'une liste des candidats et la matrice de duels (ils se créent en même temps)
 *
 *  \param[in] matrice_votes la matrice conenant les votes donnés pour chaques candidats
 *
 *  \return la matrice de duel obtenue à partir des votes donnés
 */
Matrix * initialisation_matrice(Matrix *matrice_votes) {
 
    Matrix * matrice_duels = init_matrix(get_column_names(matrice_votes));
    
    int i;
    /* parcours de la matrice initiale (des votes) colonne par colonne */
    for (i = 0; i < matrix_cols(matrice_votes); i++) {

        List *ligne = init_list();
        int j;
        for (j = 0; j < matrix_cols(matrice_votes); j++) {
   

            int l = 0;
            int nb_votant = 0;
            while (l < matrix_rows(matrice_votes) && j!=i) {
                int vote1 = *((int *) matrix_get_element_at(matrice_votes, l, i));
                int vote2 = *((int *) matrix_get_element_at(matrice_votes, l, j));
                if (vote1 < vote2) {
                    nb_votant++;
                }
                l++; 
            }

            /* construction des lignes pour la matrice des duels */
            insert_back(ligne, &nb_votant, sizeof(int));
        }
        /* initialisation de la matrice des duels avec des lignes complètes */
        insert_row_back(matrice_duels, ligne); 

        set_tag_row(matrice_duels, i, get_tag_column(matrice_votes, i));
    }
    return matrice_duels;
}


/**
 *  \brief générer un graphe des préférences à partir d'une matrice des duels
 *
 *  \param[in] graphe_preferences
 *  \param[in] matrice_duels
 *
 *  \return il n'y a pas de retour classique, juste l'initialisation d'un graphe des préférences
 */
Graph * initialisation_graphe(Matrix *matrice_duels) {
    Graph *graphe_preferences = init_graph();

        for (int l = 0; l < matrix_rows(matrice_duels)-1; l++) {

            for(int i = l+1; i < matrix_cols(matrice_duels); i++){

                /* initialisation des poids min et max et de deux candidats pour un future arc */
                int nb_vote1 = *((int *) matrix_get_element_at(matrice_duels, l, i));
                int nb_vote2 = *((int *) matrix_get_element_at(matrice_duels, i, l));
                char *tag_col1 = get_tag_column(matrice_duels, l);
                char *tag_col2 = get_tag_column(matrice_duels, i);

                /* comparaison des poids afin de correctement construire un arc de candidat qui perd vers celui qui gagne */
                if (nb_vote1 > nb_vote2) {
                    insert_arc(graphe_preferences, tag_col1, tag_col2,
                    nb_vote2, nb_vote1);
                } else if (nb_vote1 < nb_vote2) {
                    insert_arc(graphe_preferences, tag_col2, tag_col1,
                    nb_vote1, nb_vote2);
                }
            }
        }
    
    return graphe_preferences;
}
 

/** \fn vainqueur_condorcet
 *  \brief recherche du vainqueur de condorcet à partir d'un graphe des préférences
 *
 *  \param[in] graphe_preferences
 *  \param[out] list_get_element_at(...)
 *
 *  \return le vainqueur de condorcet, celui qui est le préféré de tous
 */

char *vainqueur_condorcet(Graph *graphe_preferences) {
    /* recupereation de tous les nodes qui puissent gagner */
    List *liste_vainqueurs_potentiels = get_sources_nodes(graphe_preferences);
  
    /* vérification de l'erreur, du paradoxe */
    /* il faudra vérifier si il nous reste 1 node - vainqueur; 0 ou >1 - NULL */
    if (is_empty_list(liste_vainqueurs_potentiels) || list_size(liste_vainqueurs_potentiels) > 1) {
        delete_list(liste_vainqueurs_potentiels);
        return NULL;
    }

    char * candidat_vainqueur = (char *) list_get_element_at(liste_vainqueurs_potentiels, 0);

    candidat_vainqueur = sauvegarde_string(candidat_vainqueur);
    delete_list(liste_vainqueurs_potentiels);

    return candidat_vainqueur;
}