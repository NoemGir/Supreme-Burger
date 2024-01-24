/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 01/11/23
 *  Implementation for the graph module.
 */
/*-----------------------------------------------------------------*/

#include "graph.h"
#include "../../test/utils/utils.h"
#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------*/

/**
 *  \brief Structure d'un Arc
 */
typedef struct s_arc {
    char *first_node;  //!< Le noeud initial de l'arc.
    char *second_node; //!< Le noeud destinataire de l'arc.
    int min_weight;    //!< Le poids maximum de l'arc.
    int max_weight;    //!< Le poids minimum de l'arc.
} Arc;

/**
 *  \brief Structure d'un Graphe.
 */
typedef struct s_graph {
    List *arcs;  //!< La liste des arcs du graphe.
    List *nodes; //!< La liste des noeuds du graphe.
} Graph;

ptrGraph init_graph() {
    Graph *graph = malloc(sizeof(Graph));
    graph->arcs = init_list();
    set_list_tag(graph->arcs, "La liste des arcs");
    graph->nodes = init_list();
    set_list_tag(graph->nodes, "La liste des noeuds");
    return graph;
}

bool is_empty_graph(Graph *graph) { return (is_empty_list(graph->nodes)); }

int graph_num_arcs(Graph *graph) { return list_size(graph->arcs); }

int graph_num_node(Graph *graph) { return list_size(graph->nodes); }

List *get_arcs(Graph *graph) { return init_list_from(graph->arcs); }

List *get_nodes(Graph *graph) { return init_list_from(graph->nodes); }

char *get_first_node(Arc *arc) { return arc->first_node; }

char *get_second_node(Arc *arc) { return arc->second_node; }

int get_min_weight(Arc *arc) { return arc->min_weight; }

int get_max_weight(Arc *arc) { return arc->max_weight; }

void insert_node(Graph *graph, char *node) { insert_back(graph->nodes, node, strlen(node)); }

bool contains_node(Graph *graph, char *node) { return search_element(graph->nodes, node); }

bool contains_arc(Graph *graph, char *first_node, char *second_node) {

    ptrListIterator it = init_listIterator(graph->arcs, FORWARD_ITERATION);
    Arc *arc;

    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {

        arc = (Arc *)listIterator_data(it);
        if ((strcmp(arc->first_node, first_node) == 0 &&
             strcmp(arc->second_node, second_node) == 0))
            break;
    }

    if (!listIterator_end(it)) {
        delete_listIterator(it);
        return true;
    }
    delete_listIterator(it);
    return false;
}

void insert_arc(Graph *graph, char *first_node, char *second_node, int min_weight, int max_weight) {

    ptrArc new_arc = malloc(sizeof(Arc));
    size_t len_first_node = strlen(first_node);
    size_t len_second_node = strlen(second_node);

    char *new_first_node = (char *)malloc(len_first_node+1);
    memcpy(new_first_node, first_node, len_first_node+1);
    new_arc->first_node = new_first_node;

    char *new_second_node = (char *)malloc(len_second_node+1);
    memcpy(new_second_node, second_node, len_second_node+1);
    new_arc->second_node = new_second_node;

    new_arc->max_weight = max_weight;
    new_arc->min_weight = min_weight;

    insert_back(graph->arcs, new_arc, sizeof(Arc)-1);

    free(new_arc);

    if (!contains_node(graph, first_node))
        insert_back(graph->nodes, first_node, len_first_node);

    if (!contains_node(graph, second_node))
        insert_back(graph->nodes, second_node, len_second_node);
}

List *get_predecessors(Graph *graph, char *node) {
    List *predecessor = init_list();
    ptrListIterator it = init_listIterator(graph->arcs, FORWARD_ITERATION);

    char message[512];
    sprintf(message, "Les predecesseurs du noeud %s", node);
    set_list_tag(predecessor, message);

    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {
        Arc *arc = (Arc *)listIterator_data(it);

        if (strcmp(arc->second_node, node) == 0) {
            insert_back(predecessor, arc->first_node, strlen(arc->first_node));
        }
    }
    delete_listIterator(it);
    return predecessor;
}

List *get_successors(Graph *graph, char *node) {
    List *successor = init_list();
    ptrListIterator it = init_listIterator(graph->arcs, FORWARD_ITERATION);

    char message[512];
    sprintf(message, "Les successeurs du noeud %s", node);
    set_list_tag(successor, message);

    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {

        Arc *arc = (Arc *)listIterator_data(it);
        if (strcmp(arc->first_node, node) == 0) {
            insert_back(successor, arc->second_node, strlen(arc->second_node));
        }
    }
    delete_listIterator(it);
    return successor;
}

List *get_sources_nodes(Graph *graph) {
    List *sources = init_list();
    set_list_tag(sources, "Liste des sources d'un graphe");

    ptrListIterator it = init_listIterator(graph->nodes, FORWARD_ITERATION);

    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {

        char *noeud = (char *)listIterator_data(it);
        List *predecessors = get_predecessors(graph, noeud);

        if (is_empty_list(predecessors))
            insert_back(sources, noeud, strlen(noeud));
        delete_list(predecessors);
    }
    delete_listIterator(it);
    return sources;
}

List *get_puits_nodes(Graph *graph) {
    List *puits = init_list();
    set_list_tag(puits, "Liste des puits du graphe");

    ptrListIterator it = init_listIterator(graph->nodes, FORWARD_ITERATION);

    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {

        char *noeud = (char *)listIterator_data(it);
        List *successors = get_successors(graph, noeud);

        if (is_empty_list(successors))
            insert_back(puits, noeud, strlen(noeud));
        delete_list(successors);
    }
    delete_listIterator(it);

    return puits;
}

/** \fn node_present_in_arcs
 *  \brief indicate whether a node is present in the list of arcs or not.
 *  \param graph A pointer to a graph.
 *  \param node A pointer to the string representing the node's name.
 *  \return the boolean :
 *           -  if true then the node is present in at least one arc of the graph
 *           -  if false then the node doesn't have any predecessors or successors
 */
bool node_present_in_arcs(Graph *graph, char *node) {

    ptrListIterator it = init_listIterator(graph->arcs, FORWARD_ITERATION);

    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {

        Arc *arc = (Arc *)listIterator_data(it);
        if (strcmp(arc->first_node, node) || strcmp(arc->second_node, node)) {
            delete_listIterator(it);
            return true;
        }
    }
    delete_listIterator(it);

    return false;
}

void get_weight(Graph *graph, char *first_node, char *second_node, int *min_weight,
                int *max_weight) {

    ptrListIterator it = init_listIterator(graph->arcs, FORWARD_ITERATION);
    Arc *arc;

    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {

        arc = (Arc *)listIterator_data(it);
        if ((strcmp(arc->first_node, first_node) == 0 &&
             strcmp(arc->second_node, second_node) == 0))
            break;
    }

    if (!listIterator_end(it)) {
        if (min_weight != NULL)
            *min_weight = arc->min_weight;
        if (max_weight != NULL)
            *max_weight = arc->max_weight;
    }
    delete_listIterator(it);
}

int arc_weight_min(Graph *graph, char **first_node, char **second_node, int categorie) {

    ptrListIterator it = init_listIterator(graph->arcs, FORWARD_ITERATION);
    Arc *min_arc = (Arc *)listIterator_data(it);
    Arc *arc;
    for (it = listIterator_next(it); !listIterator_end(it); it = listIterator_next(it)) {

        arc = (Arc *)listIterator_data(it);
        if (categorie == MIN_WEIGHT) {

            if (arc->min_weight < min_arc->min_weight)
                min_arc = (Arc *)listIterator_data(it);
        } else {
            if (arc->max_weight < min_arc->max_weight)
                min_arc = (Arc *)listIterator_data(it);
        }
    }
    *first_node = min_arc->first_node;
    *second_node = min_arc->second_node;
    delete_listIterator(it);
    return min_arc->min_weight;
}

int arc_weight_max(Graph *graph, char **first_node, char **second_node, int categorie) {

    ptrListIterator it = init_listIterator(graph->arcs, FORWARD_ITERATION);
    Arc *max_arc = (Arc *)listIterator_data(it);

    for (it = listIterator_next(it); !listIterator_end(it); it = listIterator_next(it)) {

        Arc *arc = (Arc *)listIterator_data(it);

        if (categorie == MIN_WEIGHT) {

            if (arc->min_weight > max_arc->min_weight)
                max_arc = (Arc *)listIterator_data(it);
        } else {
            if (arc->max_weight > max_arc->max_weight)
                max_arc = (Arc *)listIterator_data(it);
        }
    }
    *first_node = max_arc->first_node;
    *second_node = max_arc->second_node;
    delete_listIterator(it);
    return max_arc->max_weight;
}

typedef struct {
    char *nom;
    int indice;

} Sommet;

int indice_depuis_nom(char *nom, Sommet sommets[], int taille) {
    for (int i = 0; i < taille; i++) {
        Sommet sommet = sommets[i];
        if (strcmp(sommet.nom, nom) == 0)
            return sommet.indice;
    }
    printf("erreur recherche cycle dans graphe, sommet %s non trouvé\n", nom);
    return -1;
}

bool circuit(Graph *graphe, int status[], int indice_x, Sommet sommets[]) {
    bool resultat = false;
    List *successeurs = get_successors(graphe, sommets[indice_x].nom);
    ptrListIterator it = init_listIterator(successeurs, FORWARD_ITERATION);
    int indice_sommet_y = 0;
    int nb_succ = list_size(successeurs);
    int ensemble_sommets_succ[nb_succ];
    int i = 0;
    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {
        char *sommet_y = (char *)listIterator_data(it);
        int indice_sommet_y = indice_depuis_nom(sommet_y, sommets, graph_num_node(graphe));
        if (status[indice_sommet_y] == -1) {
            status[indice_sommet_y] = 0;
            resultat = circuit(graphe, status, indice_sommet_y, sommets);
            if (resultat){
                delete_list(successeurs);
                  delete_listIterator(it);
                return resultat;
            }
        } else if (status[indice_sommet_y] == 0) {
            delete_list(successeurs);
            delete_listIterator(it);
            return true;
        }
        i++;
    }
    status[indice_x] = 1;
    delete_list(successeurs);
    delete_listIterator(it);
    return false;
}

bool recherche_cycle(Graph *graphe) {

    int nb_sommet = graph_num_node(graphe);
    Sommet sommets[nb_sommet];
    int status[nb_sommet];
    int i = 0;
    int trouve = false;

    /*Initialisation du tableau sommets qui a chaque sommet associe un indice*/
    ptrListIterator it = init_listIterator(graphe->nodes, FORWARD_ITERATION);
    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {
        status[i] = -1;
        sommets[i].indice = i;
        sommets[i].nom = (char *)listIterator_data(it);
        i++;
    }
    /* Pour tous les sommets, rechercher un cycle*/
    for (i = 0; i < nb_sommet; i++) {
        if (circuit(graphe, status, i, sommets)) {
            trouve = true;
        }
    }
    delete_listIterator(it);
    return trouve;
}

int partition(Arc tab[], int indice_min, int indice_max, int pivot, int categorie) {
    int curseur_droite = indice_max - 1;
    int gauche;
    int droite;
    do {

        gauche =
            (categorie == MIN_WEIGHT) ? tab[indice_min].min_weight : tab[indice_min].max_weight;
        droite = (categorie == MIN_WEIGHT) ? tab[curseur_droite].min_weight
                                           : tab[curseur_droite].max_weight;

        while (indice_min < indice_max && gauche <= pivot) {
            indice_min++;
            gauche =
                (categorie == MIN_WEIGHT) ? tab[indice_min].min_weight : tab[indice_min].max_weight;
        }

        while (indice_max > 0 && droite >= pivot) {
            curseur_droite--;
            droite = (categorie == MIN_WEIGHT) ? tab[curseur_droite].min_weight
                                               : tab[curseur_droite].max_weight;
        }

        if (indice_min < curseur_droite) {
            Arc stock = tab[indice_min];
            tab[indice_min] = tab[curseur_droite];
            tab[curseur_droite] = stock;
        }
    } while (indice_min < curseur_droite);

    Arc stock = tab[indice_min];
    tab[indice_min] = tab[indice_max];
    tab[indice_max] = stock;

    return indice_min;
}

void quickSort(Arc tab[], int indice_min, int indice_max, int categorie) {
    if (indice_max - indice_min <= 0) {
        return;
    }

    int pivot = categorie == MIN_WEIGHT ? tab[indice_max].min_weight : tab[indice_max].max_weight;
    int part = partition(tab, indice_min, indice_max, pivot, categorie);

    quickSort(tab, indice_min, part - 1, categorie);
    quickSort(tab, part + 1, indice_max, categorie);
}

void trier_arcs(Graph *graph, int categorie, bool croissant) {
    Arc *arc;
    int poids;
    List *arcs = graph->arcs;
    int nb_arcs = list_size(arcs);
    Arc tab_arcs[nb_arcs];
    ptrListIterator it = init_listIterator(graph->arcs, FORWARD_ITERATION);
    int i = 0;

    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {
        arc = (Arc *)listIterator_data(it);
        tab_arcs[i] = *arc;
        i++;
    }

    quickSort(tab_arcs, 0, nb_arcs - 1, categorie);
    clear_list(arcs);

    if (croissant) {
        for (i = 0; i < nb_arcs; i++) {
            insert_back(arcs, &tab_arcs[i], sizeof(Arc)-1);
        }
    } else {
        for (i = 0; i < nb_arcs; i++) {
            insert_front(arcs, &tab_arcs[i], sizeof(Arc)-1);
        }
    }
    delete_listIterator(it);
}

void trier_arcs_decroissant(Graph *graph, int categorie) { trier_arcs(graph, categorie, false); }

void trier_arcs_croissant(Graph *graph, int categorie) { trier_arcs(graph, categorie, true); }

void delete_arc(Graph *graph, char *first_node, char *second_node) {

    ptrListIterator it = init_listIterator(graph->arcs, FORWARD_ITERATION);
    Arc *arc;

    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {

        arc = (Arc *)listIterator_data(it);
        if ((strcmp(arc->first_node, first_node) == 0 &&
             strcmp(arc->second_node, second_node) == 0))
            break;
    }

    if (!listIterator_end(it)) {  
        delete_at_arc(graph->arcs, listIterator_index_current(it));
    }
    delete_listIterator(it);
}

void delete_node(Graph *graph, char *node) {

    ptrListIterator it = init_listIterator(graph->arcs, FORWARD_ITERATION);

    int index = find_element(graph->nodes, node);
    Arc *arc;
    if (index != -1) {

        delete_at(graph->nodes, index);

        int toDelete[graph_num_arcs(graph)];
        int curseur = 0;
        for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {

            arc = (Arc *)listIterator_data(it);
            if (strcmp(arc->first_node, node) == 0 || strcmp(arc->second_node, node) == 0) {

                toDelete[curseur] = listIterator_index_current(it);
                curseur++;
            }
        }
        while (curseur > 0) {
            curseur--;
            delete_at_arc(graph->arcs, toDelete[curseur]);
        }
    }
    delete_listIterator(it);
}

void clear_graph(Graph *graph) {
    clear_list(graph->nodes);
    clear_list_arc(graph->arcs);
}

void delete_graph(ptrGraph graph) {
    delete_list(graph->nodes);
    delete_list_arc(graph->arcs);
    free(graph);
}