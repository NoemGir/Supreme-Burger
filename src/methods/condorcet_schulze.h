/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author  Noemie GIREAUD
 *  \date 11/11/23
 *  \file condorcet_shulze.h
 *  \brief Interface des calculs du resultat du vote grace à la methode de Schulze ( Condorcet paradoxe )
 **/
/*-----------------------------------------------------------------*/

#include "../datatypes/graph.h"

/**
 *  \brief Recherche le vainqueur des votes par la méthode de Condorcet en déjouant les ambiguités avec la methode de Schulze.
 *  \param[in] graph_duel A pointer to a graph.
 *  \return le nom du vainqueur défini grace a la methode de Schulze.
 */

char * main_condorcet_schulze(Graph * graphe_duel);