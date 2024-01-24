/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author RADIONOVA Veronika
 *  \date 28/10/23
 *  \file condorcet.h
 *  \brief Implémentation des calculs du resultat du vote grace à la methode de Condorcet ( sans paradoxe )
 **/
/*-----------------------------------------------------------------*/
#include "../datatypes/matrix.h"
#include "../datatypes/graph.h"


//void initialisation_matrice_graphe(Matrix *resMatrice, Matrix *matriceInit);

/**
 *  \brief générer une matrice des duels à partir d'une matrice des votes (nouvelle forme des fishiers csv)
 et un graphe des préférences à partir d'une liste des candidats et la matrice de duels (ils se créent en même temps)
 *
 *  \param[in] matrice_votes la matrice conenant les votes donnés pour chaques candidats
 *
 *  \return la matrice de duel obtenue à partir des votes donnés
 */
Matrix * initialisation_matrice(Matrix *matrice_votes);


/**
 *  \brief générer un graphe des préférences à partir d'une matrice des duels
 *
 *  \param[in] matrice_duels
 *
 *  \return un pointeur vers le graphe de duel initialisé;
 */

Graph * initialisation_graphe(Matrix *matrice_duels);


/**
 *  \brief recherche du vainqueur de condorcet à partir d'un graphe des préférences
 *
 *  \param[in] graphe_preferences
 *  \param[out] vainqueur
 *
 *  \return le vainqueur de condorcet, celui qui est le préféré de tous
 */

char* vainqueur_condorcet(Graph *graphe_preferences);