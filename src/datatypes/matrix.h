/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author Daoud LAMALMI and Noemie GIREAUD
 *  \file matrix.h
 *  \brief Interface for the generic matrix module.
 *   
 **/
/*-----------------------------------------------------------------*/

#ifndef MATRIX_H
#define MATRIX_H

#include "list.h"
#include "stdbool.h"
#include <string.h>

/*-----------------------------------------------------------------*/

/** \defgroup matrix Matrix Management
 * @{
 */

/** \typedef Matrix
 *  \brief type generique sur les matrices
 */
typedef struct s_matrix Matrix;

/** \typedef PointerMatrix
 *  \brief pointeur sur Matrix
 */
typedef Matrix *ptrMatrix;

/**
 *  \brief initialise une matrice avec un nom associé à chaque colomne
 *  \param[in] columns_name pointeur sur un tableau de char* contenant le nom de chaque colomne (seulement char*)
 *  \return pointeur sur matrice initialisée
 */
ptrMatrix init_matrix(ptrList columns_name);

/**
 *  \brief Verifie si matrice vide
 *  \param[in] matrix pointeur sur matrice
 *  \return un booleen : Vrai si vide, Faux si contient au moins un element
 */
bool is_empty_matrix(ptrMatrix matrix);


/**
 *  \brief renvoie un pointeur sur la liste de noms de colomne
 *  \param[in] matrix pointeur sur matrice
 *  \return liste de (char *) representant les noms de colomnes
 */
ptrList get_column_names(ptrMatrix matrix);

/**
 *  \brief renvoie un pointeur sur la liste de noms de lignes
 *  \param[in] matrix pointeur sur matrice
 *  \return un pointeur sur la liste(char*) de noms de lignes
 */
ptrList get_row_names(ptrMatrix matrix);

/**
 *  \brief retourne nombre de lignes de la matrice
 *  \param[in] matrix pointeur sur matrice
 *  \return nombre de lignes de la matrice
 */
int matrix_rows(ptrMatrix matrix);

/**
 *  \brief retourne la taille d'un element specifique(coordonnée précisée en param) de la matrice
 *  \param[in] matrix pointeur sur matrice
 *  \param[in] index_row position ligne
 *  \param[in] index_col position colomne
 *  \return taille d'un element specifique à la position numeroLigne= index_row - numeroColomne=index_col.
 */
size_t matrix_get_element_size(ptrMatrix matrix, int index_row, int index_col);

/**
 *  \brief retourne nombre de colomnes de la matrice
 *  \param[in] matrix pointeur sur matrice
 *  \return nombre de colomnes de la matrice
 */
int matrix_cols(ptrMatrix matrix);

/**
 *  \brief modifie la balise de la ligne à la position demandée
 *  \param[in,out] matrix pointeur sur matrice
 *  \param[in] row position ligne
 *  \param[in] tag le nom de la nouvelle balise pour la ligne demandée
 */
void set_tag_row(ptrMatrix matrix, int row, char *tag);

/**
 *  \brief modifie la balise de la colomne à la position demandée
 *  \param[in,out] matrix pointeur sur matrice
 *  \param[in] column position colomne
 *  \param[in] tag le nom de la nouvelle balise pour la colomne demandée
 */
void set_tag_column(ptrMatrix matrix, int column, char *tag);


/**
 *  \brief retourne la balise de la ligne à la position demandée
 *  \param[in,out] matrix pointeur sur matrice
 *  \param[in] row position ligne
 *  \return tag le nom de la balise pour la ligne demandée
 */
char *get_tag_row(ptrMatrix matrix, int row);

/**
 *  \brief retourne la balise de la colomne à la position demandée
 *  \param[in,out] matrix pointeur sur matrice
 *  \param[in] column position colomne
 *  \return tag le nom de la balise pour la colomne demandée
 */
char *get_tag_column(ptrMatrix matrix, int column);

/**
 *  \brief recupere un element a une position précisée en parametre
 *  \param[in] matrix pointeur sur matrice
 *  \param[in] row position ligne
 *  \param[in] column position colomne
 *  \return pointeur sur l'element à la position demandée
 */
void *matrix_get_element_at(ptrMatrix matrix, int row, int column);

/**
 *  \brief modifie un element a une position précisée en parametre
 *  \param[in,out] matrix pointeur sur matrice
 *  \param[in] row position ligne
 *  \param[in] column position colomne
 *  \param[in] element pointeur sur le nouvel element à inserer
 *  \param[in] data_length taille de la donnée à inserer
 */
void matrix_set_element_at(ptrMatrix matrix, int row, int column, void *element,size_t data_length) ;

/**
 *  \brief Insere une ligne à la position demandée de la matrice
 *  \param[in,out] matrix pointeur sur matrice
 *  \param[in] list pointeur sur liste à inserer
 *  \param[in] row position à laquelle on insere la nouvelle ligne
 */
void insert_row_at(ptrMatrix matrix, ptrList list, int row);

/**
 *  \brief Insere une ligne au debut de la matrice
 *  \param[in,out] matrix pointeur sur matrice
 *  \param[in] list pointeur sur liste à inserer
 */
void insert_row_front(ptrMatrix matrix, ptrList list);

/**
 *  \brief Insere une ligne à la fin de la matrice
 *  \param[in,out] matrix pointeur sur matrice
 *  \param[in] list pointeur sur liste à inserer
 */
void insert_row_back(ptrMatrix matrix, ptrList list);

/**
 *  \brief Retourne la liste à la position demandée
 *  \param[in] matrix pointeur sur matrice
 *  \param[in] row position ligne
 *  \return pointeur sur liste correspondant à la liste à la position row
 */
ptrList get_row_at(ptrMatrix matrix, int row);

/**
 *  \brief Retourne la liste en debut de matrice
 *  \param[in] matrix pointeur sur matrice
 *  \return pointeur sur liste correspondant à la premiere liste de la matrice
 */
ptrList get_first_row(ptrMatrix matrix);

/**
 *  \brief Retourne la liste en derniere position de matrice
 *  \param[in] matrix pointeur sur matrice
 *  \return pointeur sur liste correspondant à la derniere liste de la matrice
 */
ptrList get_last_row(ptrMatrix matrix);

/**
 *  \brief Retourne la colomne à la position demandée
 *  \param[in] matrix pointeur sur matrice
 *  \param[in] col_index position colomne
 *  \return pointeur sur liste correspondant à la colomne à la position col_index
 */
ptrList get_col_at(ptrMatrix matrix,int col_index);

/**
 *  \brief Retourne la colomne à la 1re position de la matrice
 *  \param[in] matrix pointeur sur matrice
 *  \return pointeur sur liste correspondant à la colomne à la premiere position
 */
ptrList get_first_col(ptrMatrix matrix);

/**
 *  \brief Retourne la colomne à la derniere position de la matrice
 *  \param[in] matrix pointeur sur matrice
 *  \return pointeur sur liste correspondant à la colomne à la derniere position
 */
ptrList get_last_col(ptrMatrix matrix);


/**
 *  \brief Modifie ligne à la position demandée de la matrice
 *  \param[in,out] matrix pointeur sur matrice
 *  \param[in] list pointeur sur liste à inserer
 *  \param[in] row position à laquelle on insere la nouvelle ligne
 */
void set_row_at(ptrMatrix matrix, ptrList list, int row);

/**
 *  \brief supprime la ligne de la matrice à la position demandée 
 *  \param[in,out] matrix pointeur sur matrice
 *  \param[in] row position pour laquelle on supprime ligne
 */
void delete_row_at(ptrMatrix matrix, int row);

/**
 *  \brief supprime la ligne à la 1re position de la matrice
 *  \param[in,out] matrix pointeur sur matrice
 */
void delete_first_row(ptrMatrix matrix);

/**
 *  \brief supprime la ligne à la derniere position de la matrice
 *  \param[in,out] matrix pointeur sur matrice
 */
void delete_last_row(ptrMatrix matrix);

/**
 *  \brief Supprime tous les elements de la matrice et la matrice
 *  \param[in,out] matrix pointeur sur matrice
 */
void clear_matrix(ptrMatrix matrix); 


/**
 *  \brief Supprime tous les elements de la matrice et la matrice et libere l'espace alloué à cette structure
 *  \param[in,out] matrix pointeur sur matrice
 */
void delete_matrix(ptrMatrix matrix);

/** @} */

#endif // MATRIX_H
