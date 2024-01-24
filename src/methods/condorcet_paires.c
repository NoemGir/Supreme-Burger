/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author RADIONOVA Veronika
 *  \date 03/12/23
 *  \file Implémentation des calculs du resultat du vote grace à la methode des Paires ( Condorcet paradoxe )
 **/
/*-----------------------------------------------------------------*/

#include "condorcet_paires.h"
#include "../../test/utils/utils.h"
#include "../utils_sd/utils_sd.h"
#include "condorcet.h"


/**
 *  \brief générer un graphe orienté avec des poids des arcs (la différence entre le poids max et le poids min).
 *
 *  \param[in] graph_vote le graphe représentant les votes pour chaque candidat.
 *
 *  \return Un pointeur vers le graphe orienté avec un seul poids max qui vaut poids_max - poids_min.
 */
Graph *init_graphe_oriente(Graph *graph_vote) {
    List *arcs = get_arcs(graph_vote);
    Graph *graph_oriente = init_graph();
    ListIterator * it = init_listIterator(arcs, FORWARD_ITERATION);

    for(it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)){
        Arc *arc = listIterator_data(it);
        int ponderation = get_max_weight(arc) - get_min_weight(arc);
        insert_arc(graph_oriente, get_first_node(arc), get_second_node(arc), 0, ponderation);
    }
    delete_listIterator(it);
    delete_list(arcs);
    return graph_oriente;
}

/**
 *  \brief Recherche le vainqueur d'un ballot de vote grace à la methode de condorcet paires.
 *
 *  \param[in] graph_preferences lPointeur vers le graphe de préférénce issus de la matrice de duel.
 *
 *  \return une chaine de charactère représntant le nom du vainqueur grace à la methode de condorcet paires.
 */
char *main_condorcet_paires(Graph *graph_preferences) {

    char *vainqueur;
    Graph * graph_oriente = init_graphe_oriente(graph_preferences);
    char message[512];

    ajouter_texte_log("graphe obtenue après initialisation valeurs :");
    ajouter_graphe_log(graph_oriente);

    trier_arcs_decroissant(graph_oriente, MAX_WEIGHT);

    ajouter_texte_log("graphe obtenue après mise en ordre décroissante :");
    ajouter_graphe_log(graph_oriente);

    Graph *graph_sans_cycle = init_graph();
    // ne znayu nado li dobavlyat' list nodes iz oriente v etot
    List *arcs = get_arcs(graph_oriente);

    ListIterator * it = init_listIterator(arcs, FORWARD_ITERATION);

    for(it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)){
        Arc *arc = listIterator_data(it);
        insert_arc(graph_sans_cycle, get_first_node(arc), get_second_node(arc), get_max_weight(arc), get_min_weight(arc));
        if (recherche_cycle(graph_sans_cycle)) {
            sprintf(message,"l'arc %s->%s creer un cycle dans le graphe, on le ne met pas", get_first_node(arc), get_second_node(arc));

            ajouter_texte_log(message);
            delete_arc(graph_sans_cycle, get_first_node(arc), get_second_node(arc));
        }
        else{
            sprintf(message,"ajout de l'arc %s->%s dans le graphe", get_first_node(arc), get_second_node(arc));

            ajouter_texte_log(message);
        }
    }

    ajouter_texte_log("\r\ngraphe final sans cycle : ");
    ajouter_graphe_log(graph_sans_cycle); 

    vainqueur = vainqueur_condorcet(graph_sans_cycle);

    delete_list(arcs);
    delete_listIterator(it);
    delete_graph(graph_oriente);
   
    delete_graph(graph_sans_cycle);
    return vainqueur;
}


