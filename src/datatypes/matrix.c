/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author Daoud LAMALMI and Noemie GIREAUD
 *  Implementation for the generic Matrix module.
 **/
/*-----------------------------------------------------------------*/

#include "matrix.h"
#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include "../../test/utils/utils.h"
#include <stdio.h>

/*-----------------------------------------------------------------*/


typedef struct s_listElement {
    struct s_listElement *previous;
    struct s_listElement *next;
    size_t data_len;
    void *data;
} ListElement;


typedef struct s_list {
    ListElement *sentinel;
    int size;
    char *tag;
    struct s_list *next;
    struct s_list *previous;
} List;


/** 
 *  \brief Structure d'une matrice
 */
typedef struct s_matrix {
    List *column_name; //!< Pointeur vers une liste qui contient le nom des colonnes
    List *sentinel; //!< Pointeur vers la sentinel de la matrice.
    int rows; //!< Le nombre de ligne de la matrice.
    int columns; //!< Le nombre de colonne de la matrice.
} Matrix;

ptrMatrix init_matrix(ptrList columns_name) {
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->sentinel = init_list();
    matrix->column_name = columns_name;
    set_list_tag(matrix->column_name, "Colonnes");
    matrix->sentinel->next = matrix->sentinel;
    matrix->sentinel->previous = matrix->sentinel;
    matrix->rows = 0;
    matrix->columns = list_size(columns_name);
    return matrix;
}

bool is_empty_matrix(ptrMatrix matrix) {
    return !(matrix->rows); 
}

int matrix_rows(ptrMatrix matrix) {
    return matrix->rows; 
}

ptrList get_row_names(ptrMatrix matrix){
    List * row_names = init_list();
    ptrList current = matrix -> sentinel -> next; 
    for (int i = 0; i< matrix->rows; i++ ){
        insert_back(row_names, current->tag, strlen(current->tag));
        current = current-> next;
    }
    return row_names;
}

ptrList get_column_names(ptrMatrix matrix) {
    List* column_names = init_list_from(matrix->column_name);
    return column_names;
}

void set_column_names(ptrMatrix matrix, ptrList columns_name) {
    matrix->column_name = columns_name;
}

int matrix_cols(ptrMatrix matrix) { return matrix->columns; }


ptrList go_to_list(ptrMatrix matrix, int row) {
    assert(row >= -1 && matrix->rows >= row);
    ptrList current = matrix->sentinel;
    if (row == -1) {
        return current;
    }
    if (row > matrix->rows / 2) {
        for (int i = 0; i < matrix->rows - row; i++) {
            current = current->previous;
        }
    } else {
        for (int i = 0; i <= row; i++) {
            current = current->next;
        }
    }
    return current;
}

ptrListElement go_to_element(ptrMatrix matrix, int row, int column) {
    assert(row >= 0 && column >= 0 && matrix->columns > column);
    ptrList current = go_to_list(matrix, row);
    ptrListElement element = current->sentinel;
    if (column > matrix->columns / 2) {
        for (int i = 0; i < matrix->columns - column; i++) {
            element = element->previous;
        }
    } else {
        for (int i = 0; i <= column; i++) {
            element = element->next;
        }
    }
    return element;
}

size_t matrix_get_element_size(ptrMatrix matrix, int index_row, int index_col){
    ptrListElement elt = go_to_element(matrix, index_row, index_col);
    return elt-> data_len;
}

void set_tag_row(ptrMatrix matrix, int row, char *tag) {
    
    List * list_row = go_to_list(matrix, row);
    set_list_tag(list_row, tag);
}

void set_tag_column(ptrMatrix matrix, int column, char *tag) {
    list_set_element_at(matrix->column_name, column, tag, strlen(tag));
}

char *get_tag_row(ptrMatrix matrix, int row) {
    char * tag = go_to_list(matrix, row)->tag; 
    return tag;
}

char *get_tag_column(ptrMatrix matrix, int column) {
    return (char *) list_get_element_at(matrix->column_name, column);
}

void *matrix_get_element_at(ptrMatrix matrix, int row, int column) {
    return go_to_element(matrix, row, column)->data;
}
void matrix_set_element_at(ptrMatrix matrix, int row, int column, void *element,size_t data_length) {
    ptrList check = go_to_list(matrix, row);
    ptrListElement current = go_to_element(matrix, row, column);


    free(current->data);

    current->data = malloc(data_length+1);
    memcpy ( current->data, element, data_length+1);
    current-> data_len = data_length;

}

void insert_row_at(ptrMatrix matrix, ptrList list, int row) {
    assert(list_size(list) == matrix->columns);
    ptrList suivent = go_to_list(matrix, row);
    list->previous = suivent->previous;
    list->previous->next = list;
    suivent->previous = list;
    list->next = suivent;
    matrix->rows++;
}

void insert_row_front(ptrMatrix matrix, ptrList list) {
    assert(list_size(list) == matrix->columns);
    matrix->sentinel->next->previous = list;
    list->next = matrix->sentinel->next;
    list->previous = matrix->sentinel;
    matrix->sentinel->next = list;
    matrix->rows++;
}

void insert_row_back(ptrMatrix matrix, ptrList list) {
    assert(list_size(list) == matrix->columns);
    matrix->sentinel->previous->next = list;
    list->next = matrix->sentinel;
    list->previous = matrix->sentinel->previous;
    matrix->sentinel->previous = list;
    matrix->rows++;
}

ptrList get_row_at(ptrMatrix matrix, int row) {
    return go_to_list(matrix, row); 
}

ptrList get_first_row(ptrMatrix matrix) {
    return go_to_list(matrix, 0);
}

ptrList get_last_row(ptrMatrix matrix) {
    return go_to_list(matrix, matrix->rows);
}


ptrList get_col_at(ptrMatrix matrix, int col_index){
    ptrList col = init_list();
    List * current = matrix->sentinel->next;
    for(int i = 0; i < matrix->rows; i++){
        ListElement * elt = go_to_element(matrix, i,  col_index);
        insert_back(col, elt->data, elt->data_len );
        current = current->next;
    }
    return col;
}


ptrList get_first_col(ptrMatrix matrix){
    ptrList col = init_list();
    List * current = matrix->sentinel->next;
    for(int i = 0; i < matrix->rows; i++){
        ListElement * elt = go_to_element(matrix, i,  0);
        insert_back(col, elt->data, elt->data_len );
        current = current->next;
    }
    return col;
}


ptrList get_last_col(ptrMatrix matrix){
    ptrList col = init_list();
    List * current = matrix->sentinel->next;
    for(int i = 0; i < matrix->rows; i++){
        ListElement * elt = go_to_element(matrix, i,  (matrix->columns)-1);
        insert_back(col, elt->data, elt->data_len );
        current = current->next;
    }
    return col;
}


void set_row_at(ptrMatrix matrix, ptrList list, int row) {
    assert(list_size(list) == matrix->columns);
    ptrList to_free = go_to_list(matrix, row);
    to_free->previous->next = list;
    to_free->next->previous = list;
    list->next = to_free->next;
    list->previous = to_free->previous;
    to_free->next = to_free->previous = NULL;
    delete_list(to_free);
}

void delete_row_at(ptrMatrix matrix, int row) {
    assert(!is_empty_matrix(matrix));
    ptrList to_free = go_to_list(matrix, row);
    to_free->next->previous = to_free->previous;
    to_free->previous->next = to_free->next;
    to_free->previous = to_free->next = NULL;
    delete_list(to_free);
    matrix->rows--;
}

void delete_first_row(ptrMatrix matrix) {
    assert(!is_empty_matrix(matrix));
    ptrList to_free = matrix->sentinel->next;
    matrix->sentinel->next = to_free->next;
    to_free->next->previous = matrix->sentinel;
    to_free->previous = to_free->next = NULL;
    delete_list(to_free);
    matrix->rows--;
}

void delete_last_row(ptrMatrix matrix) {
    assert(!is_empty_matrix(matrix));
    ptrList to_free = matrix->sentinel->previous;
    matrix->sentinel->previous = to_free->previous;
    to_free->previous->next = matrix->sentinel;
    to_free->next = to_free->previous = NULL;
    delete_list(to_free);
    matrix->rows--;
}

void clear_matrix(ptrMatrix matrix) {
    while (!is_empty_matrix(matrix)) {
        delete_last_row(matrix);
    }
    delete_list(matrix->column_name);
}

void delete_matrix(ptrMatrix matrix) {
    clear_matrix(matrix);
    delete_list(matrix->sentinel);
    free(matrix);
}
