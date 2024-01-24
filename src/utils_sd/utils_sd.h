/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 24/10/23
 *  \file utils_sd.h
 *  \brief Interface des fonctions utiles
 */
/*-----------------------------------------------------------------*/

#ifndef UTILS_SD_H
#define UTILS_SD_H

#include "../datatypes/list.h"
#include "../datatypes/matrix.h"
#include "../datatypes/graph.h"
#include <stdio.h>



/*-------------------------------UTILS----------------------------------*/

/**
 *  \brief Pour uninominal : definition d'un type renvoyant le nom et les score du vainqueur (à utiliser dans la
 * fonction d'affichage)
 */
typedef struct s_vainqueur {
    char *nom; //!< Le nom du vainqueur.
    float score; //!< Le score du vainqueur.
} vainqueur;

/**
 *  \brief A utiliser en cas d'erreur après l'utilisation d'une primitive.
 *
 *  \param[in] message Le message indiquant la source de l'erreur.
 *  \param[in] num_exit le numero de status de exit.
 */
void erreur_primitive(char * message,int num_exit);

/**
 *  \brief Sauvegarde la string donnée dans un nouvel emplacemement mémoire (ne pas oublier de le free ensuite)
 *
 *  \param[in] string La chaine de charactère a sauvegarder.
 *  \return un pointeur vers la chaine de caractère sauvegardée dans un nouvel emplacement.
 *
 */
char * sauvegarde_string(char * string);

/**
 *  \brief Genere l'affichage du vainqueur avec les methodes uninominales.
 *
 *  \param[in] methode chaine de charactère représentant la methode utilisée.
 *  \param[in] nbCandidat le nombre de candidat.
 *  \param[in] nbVotes le nombre de votant.
 *  \param[in] vainqueur pointeur vers un vainqueur.
 */
void affichage_uninominale(char *methode, int nbCandidat, int nbVotes, vainqueur *vainqueur);

/**
 *  \brief Recherche le minimum parmis les entiers placés dans la liste.
 *
 *  \param[in] liste un pointeur vers une liste.
 *  \param[out] la valeur du minimum.
 *  \return l'index du minimum dans la liste.
 */
int recherche_min(List * liste, int * valeur);

/**
 *  \brief Recherche le maximum parmis les entiers placés dans la liste.
 *
 *  \param[in] liste un pointeur vers une liste.
 *  \param[out] la valeur du maximum.
 *  \return l'index du maximum dans la liste.
 */
int recherche_max(List * liste, int * valeur);

/**
 *  \brief Recherche le maximum parmis les entiers placés dans le tableau.
 *
 *  \param[in] un tableau
 *  \param[in] longueur du tableau
 *  \param[in] liste contenant les indices des autres occurences du maximum
 *  \param[out] la valeur du maximum.
 *  \return l'index du maximum dans le tableau.
 */
int recherche_max_tab(int *tab, int longueur, List *autres_max);

/**************************ECRITURE DANS FICHIER***************************/

/**
 *  \brief Ajouter une liste dans le fichier donné.
 *
 *  \param[in] liste pointeur vers la liste a ajouter dans le fichier.
 *  \param[in] fichier le fichier.
 */
void liste_dans_fichier(List * liste, FILE * fichier);

/**
 *  \brief Ajouter une liste de façon horizontale dans le fichier donné.
 *
 *  \param[in] liste pointeur vers une liste.
 *  \param[in] fichier le fichier.
 */
void liste_horizontales_dans_fichier(List* liste, FILE * fichier);

/**
 *  \brief Ajouter une matrice dans le fichié donné.
 *
 *  \param[in] matrice un pointeur vers une matrice.
 *  \param[in] fichier le fichier.
 */
void matrice_dans_fichier(Matrix * matrice, FILE * fichier);


/**
 *  \brief Ajouter un graphe dans le fichier donné.
 *
 *  \param[in] graphe un pointeur vers un graphe.
 *  \param[in] fichier le fichier.
 */
void graphe_dans_fichier(Graph* graphe, FILE * fichier);  


/*-------------------------------LOG----------------------------------*/

/**
 *  \brief ouvre le fichier log et permet d'y ajouter des éléments.
 *  \param[in] nom_log chaine de charactere représentant le nom du fichier log créé.
 */
void creer_log(char * nom_log);

/**
 *  \brief ferme le fichier log.
 */
void fin_log();

/**
 *  \brief Ajouter une matrice dans le log.
 *
 *  \param[in] matrice un pointeur vers une matrice.
 */
void ajouter_matrice_log(Matrix * matrice);

/**
 *  \brief  pointeur vers une liste.
 *
 *  \param[in] liste la liste a ajouter dans le log.
 */
void ajouter_liste_log(List * liste);

/**
 *  \brief Ajouter une liste de façon horizontale dans le log.
 *
 *  \param[in] liste pointeur vers une liste.
 */
void ajouter_liste_horizontale_log(List * liste);

/**
 *  \brief Ajouter un texte dans le log.
 *
 *  \param[in] texte le texte a ajouter dans le log ( pas besoin de \n a la fin).
 */
void ajouter_texte_log(char * texte);

/**
 *  \brief Ajouter un graphe dans le log.
 *
 *  \param[in] graphe un pointeur vers un graphe.
 */
void ajouter_graphe_log(Graph * graphe);

#endif //UTILS_SD_H

