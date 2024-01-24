/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author RADIONOVA Veronika
 *  \date 03/12/23
 *  \file condorcet_paires.h
 *  \brief Interface des calculs du resultat du vote grace à la methode des Paires ( Condorcet paradoxe )
 **/
/*-----------------------------------------------------------------*/

#include "../datatypes/graph.h"

/**
 *  \brief Recherche le vainqueur d'un ballot de vote grace à la methode de condorcet paires.
 *
 *  \param[in] graph_preferences lPointeur vers le graphe de préférénce issus de la matrice de duel.
 *
 *  \return une chaine de charactère représntant le nom du vainqueur grace à la methode de condorcet paires.
 */
char * main_condorcet_paires(Graph *graph_oriente);