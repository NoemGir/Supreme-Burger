/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author Daoud LAMALMI and Noemie GIREAUD
 *  \file list.h
 *  \brief Interface for the generic list module.
 **/
/*-----------------------------------------------------------------*/

#ifndef LIST_H
#define LIST_H

#include "stdbool.h"
#include <stddef.h>

#define FORWARD_ITERATION 1
#define BACKWARD_ITERATION 0

/*-----------------------------------------------------------------*/

/** \defgroup list List Management
 * @{
 */

/** \typedef ListElement
 *  \brief definition d'un type elemen d'une liste
 */
typedef struct s_listElement ListElement;

/** \typedef ptrListElement
 *  \brief type pointeur pour un element d'une liste
 */
typedef ListElement *ptrListElement;

/** \typedef List
 *  \brief type generique d'une liste
 */
typedef struct s_list List;

/** \typedef ptrList
 *  \brief pointeur d'une liste
 */
typedef List *ptrList;

/** \typedef ListIterator
 *  \brief type iterateur sur les listes
 */
typedef struct s_listIterator ListIterator;

/** \typedef ptrListIterator
 *  \brief un pointeur de type iterateur sur les listes
 */
typedef ListIterator *ptrListIterator;


/** 
 *  \brief initialise une liste (List) et renvoie un pointeur sur cette liste
 *  \return pointeur sur liste vide 
 */
ptrList init_list();

/** 
 *  \brief initialise une liste (List) à partir d'une autre liste et renvoie un pointeur sur cette liste
 *  \param[in] origin pointeur sur une liste
 *  \return pointeur sur la nouvelle liste créée, copie de la liste *origin
 */
ptrList init_list_from(List *origin);

/** 
 *  \brief ajout d'une balise(balise revient à donner un identifiant) a une liste
 *  \param[in,out] list Pointeur sur liste à laquelle on ajoute la balise
 *  \param[in] tag tableau de caractere qui represente la balise
 */
void set_list_tag(ptrList list, char *tag);

/**
 *  \brief ajout d'une balise(balise revient à donner un identifiant) a une liste
 *  \param[in] list Pointeur sur liste
 *  \return tag: tableau de caractere qui represente la balise de la liste list
 */
char *get_list_tag(ptrList list);

/**
 *  \brief renvoie un booleen sur si liste est vide
 *  \param[in] list Pointeur sur liste
 *  \return True(vrai) si listeest vide, sinon False(faux)
 */
bool is_empty_list(ptrList list);

/** 
 *  \brief Retourne la taille de la liste
 *  \param[in] list Apointeur sur liste
 *  \return taille de la liste en parametre
 */
int list_size(ptrList list);

/**
 *  \brief retourne la taille d'un certain element demande d'une liste
 *  \param[in] list pointeur sur liste
 *  \param[in] index index/position de l'element dans la liste
 *  \return taille de l'element
 */
size_t list_get_element_size(ptrList list, int index);

/**
 *  \brief insere un element au debut de la liste
 *  \param[in,out] list pointeur sur liste
 *  \param[in] data_length taille de la donnée/element à inserer dans la liste : (si :int -> sizeof(int), char* -> strlen(char * data)).
 *  \param[in] element pointeur sur l'element a inserer dans la liste
 */
void insert_front(ptrList list, void *element, size_t data_length);

/**
 *  \brief insere un element a la fin de la liste
 *  \param[in,out] list pointeur sur liste
 *  \param[in] data_length taille de la donnée/element à inserer dans la liste : (si :int -> sizeof(int), char* -> strlen(char * data)).
 *  \param[in] element pointeur sur l'element a inserer dans la liste
 */
void insert_back(ptrList list, void *element, size_t data_length);

/**
 *  \brief insere un element a la position index de la liste
 *  \param[in,out] list pointeur sur liste
 *  \param[in] index position a laquelle on veut placer la donnée
 *  \param[in] data_length taille de la donnée/element à inserer dans la liste : (si :int -> sizeof(int), char* -> strlen(char * data)).
 *  \param[in] element pointeur sur l'element a inserer dans la liste
 */
void insert_at(ptrList list, int index, void *element, size_t data_length);

/**
 *  \brief recupere l'element à la position index de la liste
 *  \param[in] list pointeur sur liste
 *  \param[in] index position de l'element a recuperer
 *  \return pointeur sur l'element de l'index
 */
void *list_get_element_at(ptrList list, int index);
 
/**
 *  \brief modifie la donnée à la position index avec l'element passé en parametre 
 *  \param[in,out] list pointeur sur liste
 *  \param[in] index position de l'element a modifier
 *  \param[in] element Pointeur sur l'element a être placé à la position 
 *  \param[in] data_length taille de l'element a inserer (int -> sizeof(int), char* -> strlen(char * data)).
 */
void list_set_element_at(ptrList list, int index, void *element, size_t data_length);


/**
 *  \brief supprime l'element à la position donnée de la liste
 *  \param[in,out] list pointeur sur liste
 *  \param[in] index position de l'element à supprimer
 */
void delete_at(ptrList list, int index);

/**
 *  \brief Recherche si un element existe dans la liste
 *  \param[in] list pointeur sur liste
 *  \param[in] element pointeur sur l'element recherché
 *  \return True si element existe sinon False
 */
bool search_element(ptrList list, void *element);

/**
 *  \brief Recherche si un element existe dans la liste si oui renvoie sa position 
 *  \param[in] list pointeur sur liste
 *  \param[in] element pointeur sur l'element recherché
 *  \return entier de la position de l'element sinon -1
 */
int find_element(ptrList list, void *element);

/**
 *  \brief Supprime tous les elements de la liste 
 *  \param[in,out] list pointeur sur liste
 */
void clear_list(ptrList list);

/**
 *  \brief supprime les elements de la liste et libere l'espace memoire de celle-ci
 *  \param[in,out] list A pointer to a list.
 */
void delete_list(ptrList list);


/**
 *  \brief supprime l'element à la position donnée de la liste d'arc
 *  \param[in,out] list pointeur sur liste
 *  \param[in] index position de l'element à supprimer
 */
void delete_at_arc(ptrList list, int index);


/**
 *  \brief Supprime tous les elements de la liste d'arcs.
 *  \param[in,out] list pointeur sur liste
 */
void clear_list_arc(ptrList list);

/**
 *  \brief supprime une liste d'arcs.
 *  \param[in,out] list A pointer to a list.
 */
void delete_list_arc(ptrList list);

/**
 *  \brief Cree un iterateur sur une liste
 *  \param[in] list liste sur laquelle on cree un iterateur
 *  \param[in] direction (FORWARD_ITERATION or BACKWARD_ITERATION) indique la direction de lecture (du debut à la fin de la liste ou inversement)
 *  \return Iterateur créé
 */
ptrListIterator init_listIterator(List *list, int direction);

/**
 *  \brief Retourne l'iterateur incrementé sur l'element suivant de la liste itérée
 *  \param[in] iterator Pointeur sur iterateur sur liste
 *  \return pointeur sur l'element suivant de l'iterateur
 */
ptrListIterator listIterator_next(ptrListIterator iterator);

/**
 *  \brief Retourne l'iterateur sur le 1er element  de la liste itérée
 *  \param[in] iterator Pointeur sur iterateur sur liste
 *  \return pointeur sur l'element suivant de l'iterateur
 */
ptrListIterator listIterator_begin(ptrListIterator iterator);

/**
 *  \brief verifie si l'iterateur a atteint la fin de la liste
 *  \param[in] iterator Pointeur sur iterateur sur liste
 *  \return booleen :
 *             - true(vrai) -> iterator a atteint la fin de la liste
 *             - false(faux) -> titerator pointe sur un element
 */
bool listIterator_end(ptrListIterator iterator);

/**
 *  \brief renvoie la valeur pointée par l'iterateur
 *  \param[in] iterator Pointeur sur iterateur sur liste
 *  \return valeur pointée par l'iterateur
 */
void *listIterator_data(ptrListIterator iterator);

/**
 *  \brief retourne taille de la donnée/element pointé par l'iterateur
 *  \param[in] iterator Pointeur sur iterateur sur liste
 *  \return taille de la donnée/element pointé par l'iterateur
 */
size_t listIterator_data_size(ptrListIterator iterator);

/**
 *  \brief retourne la position dans la liste de la donnée pointée par l'iterateur
 *  \param[in] iterator Pointeur sur iterateur sur liste
 *  \return position dans la liste de la donnée pointée par l'iterateur
 */
int listIterator_index_current(ptrListIterator iterator);

/**
 *  \brief supprime l'iterateur
 *  \param[in,out] iterator Pointeur sur iterateur sur liste
 */
void delete_listIterator(ptrListIterator iterator);

/** @} */

#endif // LIST_H
