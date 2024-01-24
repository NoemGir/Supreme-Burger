/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 24/10/23
 *  \file Interface pour les méthodes utiles des testes.
 **/
/*-----------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../../src/datatypes/matrix.h"
#include "../../src/datatypes/graph.h"




/**
 *  \brief execute le scripte python et retourne une matrice du resultat.
 *
 *  \return  retourne un pointeur vers la matrice générée aleatoirement avec le code python.
 **/
Matrix * recuperer_generation_test();


/**
 *  \brief Récupère le fichier donné en argument et le place dans une matrice.
 *
 *  \param[in] argc le nombre d'arguments données
 *  \param[in] argv tableaux des arguments données
 *
 *  \return  un pointeur vers la matrice représentant le fichier donné.
 **/
Matrix * recuperer_fichier_vote(int argc, char * argv[]);
/**
 *  \brief génère une matrice de int de taille définie dont les valeures a l'interieurs sont bornées.
 *
 *  \param[in] nb_ligne Le nombre de ligne de la matrice.
 *  \param[in] nb_colonne Le nombre de colonne de la matrice.
 *  \param[in] min La borne minimale pour la valeurs des entiers dans la matrice.
 *  \param[in] max La borne maximale pour la valeurs des entiers dans la matrice.
 *  \return  retourne un pointeur vers la matrice générée.
 */
Matrix * generer_matrice_int(int nb_ligne, int nb_colonne, int min, int max);

/**
 *  \brief génère une liste de int de taille définie dont les valeures a l'interieurs sont bornées.
 *
 *  \param[in] nb_element Le nombre d'entiers dans la liste.
 *  \param[in] min La borne minimale pour la valeurs des entiers dans la liste.
 *  \param[in] max La borne maximale pour la valeurs des entiers dans la liste.
 *  \return  retourne un pointeur vers la liste générée.
 */
List * generer_liste_int(int nb_element, int min, int max);

/**
 *  \brief génère une liste de chaine de charactère de taille définie.
 *
 *  \param[in] nb_element Le nombre d'élément dans la liste.
 *  \return  retourne un pointeur vers la liste générée.
 */
List * generer_liste_char(int nb_element);

/**
 *  \brief génère un graphe de taille définie dont les valeurs min et max sont bornées.
 *
 *  \param[in] nb_noeuds Le nombre de noeuds du graphe.
 *  \param[in] nb_arcs Le nombre d'arcs du graphe.
 *  \param[in] min La borne minimale pour la valeurs des min et max.
 *  \param[in] max La borne maximale pour la valeurs des min et max.
 *  \return  retourne un pointeur vers la liste générée.
 */
Graph * generer_graphe(int nb_noeuds, int nb_arcs, int min, int max);

/**
 *  \brief Affiche la liste donnée dans le terminal.
 *
 *  \param[in] liste un pointeur vers une liste.
 */
void afficher_liste(List * liste);

/**
 *  \brief Affiche le graphe donnée dans le terminal.
 *
 *  \param[in] graphe un pointeur vers un graphe.
 */
void afficher_graphe(Graph * graphe);


/** \fn afficher_matrice
 *  \brief Affiche la matrice donnée dans le terminal.
 *
 *  \param[in] matrice un pointeur vers une matrice.
 */
void afficher_matrice(Matrix * matrice);