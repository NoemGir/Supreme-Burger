/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 01/11/23
 *  \file graph.h
 *  \brief Interface pour la structure graphe.
 */
/*-----------------------------------------------------------------*/

#ifndef GRAPHE_H
#define GRAPHE_H

#include "stdbool.h"
#include <stddef.h>
#include "list.h"

#define MIN_WEIGHT 0
#define MAX_WEIGHT 1

/*-----------------------------------------------------------------*/

/** \defgroup graph Graph Management
 * @{
 */

/**
 *  \brief un type pour la définition d'un arc.
 */
typedef struct s_arc Arc;

/** 
 *  \brief un type pour définir un pointeur vers un arc.
 */
typedef Arc *ptrArc;

/**
 *  \brief un type pour la définition d'un graphe.
 */
typedef struct s_graph Graph;

/**
 *  \brief un type pour définir un pointeur vers un graphe.
 */
typedef Graph *ptrGraph;

/**
 *  \brief Initialise un nouveau graphe et retourne un pointeur vers celui-ci.
 *  \return Un pointeur vers le graphe créé.
 */
ptrGraph init_graph();


/**
 *  \brief Vérifie si le graphe est vide (il ne contient aucun sommet).
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \return True si le graphe est vide, false sinon.
 */
bool is_empty_graph(Graph* graphe);


/**
 *  \brief Retourne le nombre d'arcs dans le graphe.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \return Le nombre d'arcs dans le graphe.
 */
int graph_num_arcs(Graph* graphe);

/**
 *  \brief Retourne le nombre de sommet dans le graphe.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \return Le nombre de sommet dans le graphe.
 */
int graph_num_node(Graph* graphe);

/**
 *  \brief Retourne la liste des arcs composant le graphe.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \return La liste des arcs contenant le graphe.
 */
List * get_arcs(Graph* graphe);

/**
 *  \brief Retourne la liste des sommets composant le graphe.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \return La liste des sommets composant le graphe.
 */
List * get_nodes(Graph* graphe);

/**
 *  \brief Retourne le sommet source de l'arc (celui d'ou part la flèche)
 *  \param[in] arc Un pointeur vers un arc.
 *  \return Le sommet source de l'arc.
 */
char * get_first_node(Arc * arc);

/**
 *  \brief Retourne le sommet puit de l'arc (celui pointé par la flèche)
 *  \param[in] arc Un pointeur vers un arc.
 *  \return Le sommet puit de l'arc.
 */
char * get_second_node(Arc * arc);

/**
 *  \brief Retourne le poids minimum de l'arc donné.
 *  \param[in] arc Un pointeur vers un arc.
 *  \return Le poids minimum de l'arc.
 */
int get_min_weight(Arc * arc);

/**
 *  \brief Retourne le poids maximum de l'arc donné.
 *  \param[in] arc Un pointeur vers un arc.
 *  \return Le poids maximum de l'arc.
 */
int get_max_weight(Arc * arc);

/**
 *  \brief Insert un sommet dans l'arc (il ne sera relié à aucun autre sommet tant que un arc le connectant n'a pas été créé).
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \param[in] sommet une chaine de charactère repésentant le nom du sommet ajouté.
 */
void insert_node(Graph *graphe, char * sommet);


/**
 *  \brief Indique si un sommet est présent ou non dans le graphe.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \param[in] sommet une chaine de charactère repésentant le nom du sommet.
 *  \return un booléen :
 *           -  True : le sommet est présent dans le graphe.
 *           -  False : le sommet n'est pas présent dans le graphe.
 */
bool contains_node(Graph* graphe, char * sommet);


/**
 *  \brief Indique si un arc est présent ou non dans le graphe.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \param[in] sommet_source Une chaine de charactère repésentant le nom du sommet source ( source -> _ ).
 *  \param[in] sommet_puit Une chaine de charactère repésentant le nom du sommet puit ( _ -> puit ).
 *  \return un booléen :
 *           -  True : l'arc est présent dans le graphe.
 *           -  False : l'arc n'est pas présent dans le graphe.
 */
bool contains_arc(Graph *graphe, char * sommet_source, char * sommet_puit);

/**
 *  \brief Insert un arc dans le graphe donné 
 *         (si le graphe ne contient pas un des sommet donné, il l'ajoute automatiquement dans la liste des sommets).
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \param[in] sommet_source Une chaine de charactère repésentant le nom du sommet source ( source -> _ ).
 *  \param[in] sommet_puit Une chaine de charactère repésentant le nom du sommet puit ( _ -> puit ).
 *  \param[in] poids_max Le poids max de l'arc.
 *  \param[in] poids_min Le poids min de l'arc.
 */
void insert_arc(Graph *graphe, char * sommet_source, char * sommet_puit, int poids_min, int poids_max);


/**
 *  \brief Retourne une liste contenant tous les sommets prédécésseurs du sommet donné.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \param[in] sommet une chaine de charactère repésentant le nom du sommet.
 *  \return Un pointeur vers une liste contenant tous les sommets prédécésseurs du sommet donné.
 */
List *get_predecessors(Graph *graphe, char * sommet);

/**
 *  \brief Retourne une liste contenant tous les sommets successeurs du sommet donné.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \param[in] sommet une chaine de charactère repésentant le nom du sommet.
 *  \return Un pointeur vers une liste contenant tous les sommets successeurs du sommet donné.
 */
List *get_successors(Graph *graphe, char * sommet);

/**
 *  \brief Retourne une liste contenant tous les sommets qui n'ont pas de précécésseurs.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \return Un pointeur vers une liste contenant tous les sommets qui n'ont pas de précécésseurs.
 */
List * get_sources_nodes(Graph *graphe);

/**
 *  \brief Retourne une liste contenant tous les sommets qui n'ont pas de successeurs.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \return Un pointeur vers une liste contenant tous les sommets qui n'ont pas de successeurs.
 */
List * get_puits_nodes(Graph *graphe);

/**
 *  \brief Retourne les poids (min et max) de l'arc donné.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \param[in] sommet_source Une chaine de charactère repésentant le nom du sommet source ( source -> _ ).
 *  \param[in] sommet_puit Une chaine de charactère repésentant le nom du sommet puit ( _ -> puit ).
 *  \param[out] poids_min Le poids min de l'arc (NULL si non interesé par la valeur).
 *  \param[out] poids_max Le poids max de l'arc (NULL si non interesé par la valeur).
 */
void get_weight(Graph * graphe, char * sommet_source, char * sommet_puit, int * poids_min, int * poids_max);

/**
 *  \brief Cherche le poids le plus petit parmis la catégorie poids minimum ou poids maximum et donne le nom des sommets source et puits de l'arc ainsi que le poids obtenu.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \param[out] sommet_source Une chaine de charactère repésentant le nom du sommet source de l'arc qui à le poids le plus petit.
 *  \param[out] sommet_puit Une chaine de charactère repésentant le nom du sommet puit de l'arc qui à le poids le plus petit.
 *  \param[in] categorie MIN_WEIGHT ou MAX_WEIGHT en fonction de la catégorie voulu (respectivement poids minimun, poids maximum).
 *  \return Le poids le plus petit parmis la catégorie donnée.
 */
int arc_weight_min(Graph * graphe, char ** sommet_source, char ** sommet_puit, int categorie);

/**
 *  \brief Cherche le poids le plus grand parmis la catégorie poids minimum ou poids maximum et donne le nom des sommets source et puits de l'arc ainsi que le poids obtenu.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \param[out] sommet_source Une chaine de charactère repésentant le nom du sommet source de l'arc qui à le poids le plus grand.
 *  \param[out] sommet_puit Une chaine de charactère repésentant le nom du sommet puit de l'arc qui à le poids le plus grand.
 *  \param[in] categorie MIN_WEIGHT ou MAX_WEIGHT en fonction de la catégorie voulu (respectivement poids minimun, poids maximum).
 *  \return Le poids le plus grand parmis la catégorie donnée.
 */
int arc_weight_max(Graph * graphe, char ** sommet_source, char ** sommet_puit, int categorie);

/**
 *  \brief Indique si un cycle est présent ou non dans le graphe.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \return True si un cycle est présent, False sinon.
 */
bool recherche_cycle(Graph *graphe);


/**
 *  \brief tri les arcs du graphe dans l'odre décroissant en fonction du poids de la catégorie donnée.
 *  \param[in,out] graphe Un pointeur vers un graphe.
 *  \param[in] categorie WIN_WEIGHT ou MAX_WEIGHT selon si on veux trier en fonction du poids minimum ou du poids maximum
 */
void trier_arcs_decroissant(Graph * graph, int categorie);

/**
 *  \brief tri les arcs du graphe dans l'odre croissant en fonction du poids de la catégorie donnée.
 *  \param[in,out] graphe Un pointeur vers un graphe.
 *  \param[in] categorie WIN_WEIGHT ou MAX_WEIGHT selon si on veux trier en fonction du poids minimum ou du poids maximum
 */
void trier_arcs_croissant(Graph * graph, int categorie);

/**
 *  \brief Supprime l'arc indiqué du graphe.
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \param[in] sommet_source Une chaine de charactère repésentant le nom du sommet source  ( source -> _ ).
 *  \param[in] sommet_puit Une chaine de charactère repésentant le nom du sommet puit ( _ -> puit ).
 */
void delete_arc(Graph *graphe, char * sommet_source, char * sommet_puit);

/**
 *  \brief Supprime le sommet indiqué du graphe (tous les arcs le reliant à d'autres sommet seront également supprimés).
 *  \param[in] graphe Un pointeur vers un graphe.
 *  \param[in] sommet Une chaine de charactère repésentant le nom du sommet à supprimer.
 */
void delete_node(Graph *graph, char * node);

/**
 *  \brief Supprime tous les sommets et arcs du graphe.
 *  \param[in] graphe Un pointeur vers un graphe.
 */
void clear_graph(Graph *graphe);

/**
 *  \brief Supprime le graphe et tous les éléments à l'intérieur.
 *  \param[in] graphe Un pointeur vers un graphe.
 */
void delete_graph(ptrGraph graphe);

/** @} */

#endif // GRAPHE_H
