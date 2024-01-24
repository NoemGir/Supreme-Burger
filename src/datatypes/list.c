/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author Daoud LAMALMI And Noemie GIREAUD
 *  Implementation for the generic list module.
 **/
/*-----------------------------------------------------------------*/

#include "list.h"
#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*-------------------------------LIST----------------------------------*/

/**
 *  \brief Structure d'un élément d'une liste
 */
typedef struct s_listElement {
    struct s_listElement *previous; //!< Pointeur vers l'élément précédent dans la liste.
    struct s_listElement *next;     //!< Pointeur vers l'élément suivant dans la liste.
    size_t data_len;                //!< La taille de la donnée.
    void *data;                     //!< La donnée, qui peut etre de n'importe quel type.
} ListElement;

/**
 *  \brief Structure d'une liste
 */
typedef struct s_list {
    ListElement *sentinel;   //!< La sentinel, relié à la tête et à la queue de la liste.
    int size;                //!< Le nombre d'élément dans la liste (la sentinel ne compte pas).
    char *tag;               //!< Le nom de la liste.
    struct s_list *next;     //!< En cas de Matrice, pointeur vers la prochaine ligne, sinon NULL.
    struct s_list *previous; //!< En cas de Matrice, pointeur vers la ligne précédente, sinon NULL.
} List;

/**
 *  \brief Structure d'un itérateur sur une liste
 */
typedef struct s_listIterator {
    List *list;
    int direction;
    ListElement *current;
    int index;
    ListElement *begin;
    ListElement *(*next)(ListElement *);
} ListIterator;

ptrList init_list() {
    List *list = malloc(sizeof(List));
    list->next = list->previous = NULL;
    list->tag = NULL;
    list->sentinel = malloc(sizeof(ListElement));
    list->sentinel->previous = list->sentinel;
    list->sentinel->next = list->sentinel;
    list->sentinel->data = NULL;
    list->size = 0;
    return list;
}

ptrList init_list_from(List *origin) {
    List *new = init_list();
    int i = 0;
    ListIterator *it = init_listIterator(origin, FORWARD_ITERATION);

    for (it = listIterator_begin(it); !listIterator_end(it); listIterator_next(it)) {
        insert_back(new, listIterator_data(it), listIterator_data_size(it));
    }
    set_list_tag(new, origin->tag);
    delete_listIterator(it);
    return new;
}

void set_list_tag(ptrList list, char *tag) {

    char *new_tag = (char *)malloc(strlen(tag) + 1);
    strcpy(new_tag, tag);
    if(list->tag != NULL){
        free(list->tag);
    }
    list->tag = new_tag;
}

char *get_list_tag(ptrList list) {
    assert(list->tag != NULL);
    return list->tag;
}

bool is_empty_list(ptrList list) { return !(list->size); }

int list_size(ptrList list) { return list->size; }

size_t list_get_element_size(ptrList list, int index) {
    assert(index >= 0 && list->size > index);
    ListElement *current = list->sentinel->next;

    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data_len;
}

void insert_front(ptrList list, void *element, size_t data_length) {

    ListElement *new_element = malloc(sizeof(ListElement));
    list->sentinel->next->previous = new_element;
    new_element->next = list->sentinel->next;
    list->sentinel->next = new_element;
    new_element->previous = list->sentinel;

    new_element->data = malloc(data_length + 1);
    memcpy(new_element->data, element, data_length + 1);
    new_element->data_len = data_length;

    list->size++;
}

void insert_back(ptrList list, void *element, size_t data_length) {
    ListElement *new_element = malloc(sizeof(ListElement));
    list->sentinel->previous->next = new_element;
    new_element->previous = list->sentinel->previous;
    list->sentinel->previous = new_element;
    new_element->next = list->sentinel;

    new_element->data = malloc(data_length + 1);
    memcpy(new_element->data, element, data_length + 1);
    new_element->data_len = data_length;
    ListElement *sentinel = list->sentinel;
    list->size++;
}

void insert_at(ptrList list, int index, void *element, size_t data_length) {
    assert(index >= 0 && list->size > index);
    ListElement *current = list->sentinel;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    ListElement *new_element = malloc(sizeof(ListElement));
    current->next->previous = new_element;
    new_element->next = current->next;
    new_element->previous = current;
    current->next = new_element;

    new_element->data = malloc(data_length + 1);
    memcpy(new_element->data, element, data_length + 1);
    new_element->data_len = data_length;

    list->size++;
}

void *list_get_element_at(ptrList list, int index) {
    assert(index >= 0 && list->size > index);
    ListElement *current = list->sentinel->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

void *list_get_ListElement_at(ptrList list, int index) {
    assert(index >= 0 && list->size > index);
    ListElement *current = list->sentinel->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

void list_set_element_at(ptrList list, int index, void *element, size_t data_length) {
    assert(index >= 0 && list->size > index);
    ListElement *current = list->sentinel->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    free(current->data);

    current->data = malloc(data_length + 1);
    memcpy(current->data, element, data_length + 1);
    current->data_len = data_length;
}

void delete_last_element(ptrList list) {
    assert(!is_empty_list(list));
    ListElement *hold = list->sentinel->previous;
    hold->previous->next = list->sentinel;
    list->sentinel->previous = hold->previous;
    hold->next = hold->previous = NULL;
    list->size--;
    free(hold->data);
    free(hold);
}

void delete_at(ptrList list, int index) {
    assert(index >= 0 && list->size > index);
    ListElement *hold = list->sentinel->next;
    for (int i = 0; i < index; i++) {
        hold = hold->next;
    }
    hold->next->previous = hold->previous;
    hold->previous->next = hold->next;
    list->size--;

    free(hold->data);
    free(hold);
}


void delete_at_arc(ptrList list, int index){
     assert(index >= 0 && list->size > index);
    ListElement *hold = list->sentinel->next;
    for (int i = 0; i < index; i++) {
        hold = hold->next;
    }
    hold->next->previous = hold->previous;
    hold->previous->next = hold->next;
    list->size--;

    Arc * arc_to_delete = (Arc *) hold->data;
    free(get_first_node(arc_to_delete));
    free(get_second_node(arc_to_delete));
    free(arc_to_delete);
    free(hold);
}

bool search_element(ptrList list, void *element) {
    ListElement *current = list->sentinel->next;
    while (current != list->sentinel) {
        if (memcmp(current->data, element, current->data_len) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int find_element(ptrList list, void *element) {
    assert(search_element(list, element));
    ListElement *current = list->sentinel->next;
    int index = 0;
    while (current != list->sentinel) {
        if (memcmp(current->data, element, current->data_len) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

void clear_list(ptrList list) {
    while (!is_empty_list(list)) {
        delete_last_element(list);
    }
}

void clear_list_arc(ptrList list) {
    while (!is_empty_list(list)) {
        delete_at_arc(list, 0);
    }
}

void delete_list_arc(ptrList list) {
    clear_list_arc(list);
    free(list->sentinel);
    if(list->tag != NULL){
        free(list->tag);
    }
    free(list);
}

void delete_list(ptrList list) {
    clear_list(list);
    free(list->sentinel);
    if(list->tag != NULL){
        free(list->tag);
    }
    free(list);
}

/*------------------------------ITERATOR-----------------------------------*/

ptrListElement goto_next(ptrListElement elt) { return elt->next; }

ptrListElement goto_previous(ptrListElement elt) { return elt->previous; }

ptrListIterator init_listIterator(List *list, int direction) {

    ptrListIterator iterator = malloc(sizeof(ListIterator));
    iterator->list = list;
    iterator->direction = direction;

    if (direction == FORWARD_ITERATION) {
        iterator->begin = list->sentinel->next;
        iterator->next = goto_next;
        iterator->index = 0;

    } else {
        iterator->begin = list->sentinel->previous;
        iterator->next = goto_previous;
        iterator->index = list->size - 1;
    }
    iterator->current = iterator->begin;
    return iterator;
}

ptrListIterator listIterator_begin(ptrListIterator iterator) {
    iterator->current = iterator->begin;
    if (iterator->direction == FORWARD_ITERATION) {
        iterator->index = 0;
    } else {
        iterator->index = iterator->list->size - 1;
    }
    return iterator;
}

bool listIterator_end(ptrListIterator iterator) {
    return iterator->current == iterator->list->sentinel;
}

ptrListIterator listIterator_next(ptrListIterator iterator) {
    iterator->current = iterator->next(iterator->current);
    if (iterator->direction == FORWARD_ITERATION) {
        (iterator->index)++;
    } else {
        (iterator->index)--;
    }
    return iterator;
}

void *listIterator_data(ptrListIterator iterator) { return iterator->current->data; }

size_t listIterator_data_size(ptrListIterator iterator) { return iterator->current->data_len; }

int listIterator_index_current(ptrListIterator iterator) { return iterator->index; }

void delete_listIterator(ptrListIterator iterator) { free(iterator); }
