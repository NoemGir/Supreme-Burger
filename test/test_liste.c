/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 15/11/23
 *  \file Implementation de réalisation des tests
 **/
/*-----------------------------------------------------------------*/

#include "utils/utils.h"
#include "../src/datatypes/list.h"
#include <stdio.h>

void test_unitaire_liste_insert(){
   
   printf("\ntest d'affichage de liste\n");

   List * liste = init_list();

   printf("insertion au debut de 'element debut 1'\n");
   char * c = "element debut 1";
   insert_front(liste, c, strlen(c));
   afficher_liste(liste);

   printf("insertion au debut de 'element debut 2'\n");
   c = "element debut 2";
   insert_front(liste, c, strlen(c));
   afficher_liste(liste);

   printf("insertion au debut de 'element debut 3'\n");
   c = "element debut 3";
   insert_front(liste, c, strlen(c));
   afficher_liste(liste);

   printf("insertion en position 1 de 'position 1'\n");
   c = "position 1";
   insert_at(liste,1, c, strlen(c));
   afficher_liste(liste);

   printf("insertion en position 1 de 'nouveau position 1'\n");
   c = "nouveau position 1";
   insert_at(liste,1, c, strlen(c));
   afficher_liste(liste);

   printf("insertion a la fin de 'element fin 1'\n");
   c = "element fin 1";
   insert_back(liste, c, strlen(c));
   afficher_liste(liste);

   printf("insertion a la fin de 'element fin 2'\n");
   c = "element fin 2";
   insert_back(liste, c, strlen(c));
   afficher_liste(liste);

   printf("insertion a la fin de 'element fin 3'\n");
   c = "element fin 3";
   insert_back(liste, c, strlen(c));
   afficher_liste(liste);
    
   delete_list(liste);

   printf("fin du test\n");
}

void test_unitaire_set_get_element_at(){
   List * liste = generer_liste_int(6, 0, 15);
   afficher_liste(liste);
   
   int element;
   for(int i = 0; i < list_size(liste); i++){
      element = *((int *) list_get_element_at(liste, i));
      printf("obtenir element en position %d : %d\n", i, element);
   }

   for(int i = 0; i < list_size(liste); i++){
      element = i;
      printf("mettre %d en position %d\n", i, element);
      list_set_element_at(liste, i, &element, sizeof(int));
      afficher_liste(liste);
   }
   printf("fin du test\n");
   delete_list(liste);

}

void test_unitaire_liste_delete_at(){

   List * liste = generer_liste_char(7);
   afficher_liste(liste);

   printf("suppression de l'élément en position 4 :\n");
   delete_at(liste, 4);
   afficher_liste(liste);

   printf("suppression de l'élément en position 2 :\n");
   delete_at(liste, 2);
   afficher_liste(liste);

   printf("suppression de l'élément en position 0 :\n");
   delete_at(liste, 0);
   afficher_liste(liste);

   printf("suppression de l'élément en position 6 :\n");
   delete_at(liste, 0);
   afficher_liste(liste);

   printf("suppression de l'élément en position 3 :\n");
   delete_at(liste, 0);
   afficher_liste(liste);

   printf("suppression de l'élément en position 1 :\n");
   delete_at(liste, 0);
   afficher_liste(liste);

   printf("suppression de l'élément en position 5 :\n");
   delete_at(liste, 0);
   afficher_liste(liste);

   delete_list(liste);
   printf("fin du tes \n");
}

void test_unitaire_search_find(){
   printf("test unitaire de recherche d'un élément dans une liste\n");

   List * liste = generer_liste_char(6);
   afficher_liste(liste);

   char nomElement[20];
   int indice;

   for(int i = 0; i < list_size(liste)+2; i++){
      sprintf(nomElement, "Element %d", i);
      if(search_element(liste, nomElement)){
         indice = find_element(liste, nomElement);
         printf("élement : '%s' trouvé a l'indice %d\n", nomElement, indice);
      }
      else{
         printf("element '%s' introuvable\n", nomElement);
      }
   }
   delete_list(liste);
   printf("fin du test\n");
}

void test_uniraire_iterateur(){

   List * liste = generer_liste_char(6);
   ListIterator * it = init_listIterator(liste, FORWARD_ITERATION);

   for(it = listIterator_begin(it); !listIterator_end(it) ; it = listIterator_next(it)){
      printf("val = %s a l'indice %d, de taille %zu\n",(char *)listIterator_data(it), listIterator_index_current(it), listIterator_data_size(it) );
   }
   
   delete_listIterator(it);
   delete_list(liste);
   printf("fin du test\n");
}

void test_unitaire_init_from_liste(){
   List * liste = generer_liste_char(6);
   List * nouvelle = init_list_from(liste);
   afficher_liste(liste);
   afficher_liste(nouvelle);

   delete_list(liste);
   delete_list(nouvelle);
   printf("fin du test");
}

int main(int argc, const char * argv[]){
   test_unitaire_liste_insert(); //OK
   //test_unitaire_set_get_element_at(); //OK
   //test_unitaire_search_find(); //OK
   //test_unitaire_liste_delete_at(); //OK
   //test_uniraire_iterateur(); //OK
    //test_unitaire_init_from_liste();
   return 0;
}






