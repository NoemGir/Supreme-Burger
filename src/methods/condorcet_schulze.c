/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noemie
 *  \date 11/11/23
 *  \file Implémentation des calculs du resultat du vote grace à la methode de Schulze ( Condorcet paradoxe )
 **/
/*-----------------------------------------------------------------*/

#include "../datatypes/graph.h"
#include "condorcet_schulze.h"
#include "../utils_sd/utils_sd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *  \brief Met les sommets du graphe a jour avec l'ensemble de Schwartz
 *  \param[in] graphe un pointeur vers un graphe
 *  \return Le graph aiyant été équilibré par rapport a l'ensemble de Schwartz
 */
Graph * put_ensemble_Schwartz(Graph * graphe){
 
    if(graph_num_node(graphe) > 1){
        List * nodes = get_nodes(graphe);
        ptrListIterator it_graphe = init_listIterator(nodes, FORWARD_ITERATION);
        char * toDelete[graph_num_node(graphe)];
        int curseur = 0;

        for(it_graphe = listIterator_begin(it_graphe); !listIterator_end(it_graphe); it_graphe =  listIterator_next(it_graphe)){
            char * node = (char *) listIterator_data(it_graphe);

            List * successors = get_successors(graphe, node);

            if (is_empty_list(successors)){
                toDelete[curseur] = node;
                curseur++;
            }
            delete_list(successors);
        }
        
        delete_listIterator(it_graphe);
        if(curseur > 0){
            do{
                curseur--;
                char * toSuppr = toDelete[curseur];
                delete_node(graphe,toSuppr);
            } while(curseur > 0);

            delete_list(nodes);
            return put_ensemble_Schwartz(graphe);
        }
          delete_list(nodes);   
    }

    return graphe;
}

/** \fn get_predecessors
 *  \brief Recherche le vainqueur des votes par la méthode de Condorcet en déjouant les ambiguités avec la methode de Schulze.
 *  \param[in] graph_duel A pointer to a graph.
 *  \return le nom du vainqueur défini grace a la methode de Schulze.
 */

char * main_condorcet_schulze(Graph * graphe_duel){
    char message[512];
    List * sources = NULL;

    do{
        char * first_node;
        char * second_node;
          
        arc_weight_min(graphe_duel,&first_node,&second_node,MAX_WEIGHT);

        sprintf(message, "L'arc de poids maximum le plus petit est l'arc : %s->%s", first_node, second_node);
        ajouter_texte_log(message);
;
        ajouter_texte_log("Suppréssion de l'arc : ");
        delete_arc(graphe_duel,first_node,second_node);
        ajouter_graphe_log(graphe_duel);

        ajouter_texte_log("Mise a jour du graphe avex l'ensemble de Schwartz :");
        graphe_duel = put_ensemble_Schwartz(graphe_duel);
        ajouter_graphe_log(graphe_duel);

 
        if(sources != NULL) delete_list(sources);
          
        sources = get_sources_nodes(graphe_duel);
   
    }  while(list_size(sources) != 1);

    char *premier  = (char *) list_get_element_at(sources, 0);

    /* Récuperer le candidat vainqueur dans son propre emplacment mémoire afin de pouvoir supprimer la liste des candidats */
      
    char * vainqueur = sauvegarde_string(premier);
    
    sprintf(message,"Un vainqueur a été trouvé ! c'est %s", vainqueur);
    ajouter_texte_log(message);

    delete_list(sources);
    return vainqueur;
}