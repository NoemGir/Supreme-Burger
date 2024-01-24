/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author RADIONOVA Veronika
 *  \date 12/11/23
 *  \file condorcet_minimax.h
 *  \brief Interface des calculs du resultat du vote grace à la methode des Minimax ( Condorcet paradoxe )
 **/
/*-----------------------------------------------------------------*/

#include "../datatypes/graph.h"

/**
 *  \brief chercher le candidat qui va gagner le vote suivant le Méthode de Condorcet Minimax
 *
 *  \param[in] graph_vote
 *
 *  \return le vainqueur de la Méthode de Condorcet Minimax
 */
char * main_condorcet_minimax (Graph *graph_vote);

