/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 15/11/23
 *  \file Implementation de réalisation des tests
 **/
/*-----------------------------------------------------------------*/

#include "utils/utils.h"
#include "../src/datatypes/graph.h"
#include <stdio.h>

void test_unitaire_graphe(){
   
    printf("\ntest d'affichage de graphe : \n");

    Graph * graphe_1 = generer_graphe(4, 6, 1, 9);

    afficher_graphe(graphe_1);

    delete_graph(graphe_1);

    printf("\nFin du test\n");
}

void test_unitaire_insert(){
   Graph *graphe = init_graph();
   afficher_graphe(graphe);
   
   printf("ajout d'un arc A->B de poids 2-6\n");
   insert_arc(graphe, "A", "B", 2, 6);
   afficher_graphe(graphe);

   printf("ajout d'un arc B->C de poids 3-5\n");
   insert_arc(graphe, "B", "C", 3, 5);
   afficher_graphe(graphe);

   printf("ajout d'un arc D->C de poids 7-10\n");
   insert_arc(graphe, "D", "C", 7, 10);
   afficher_graphe(graphe);


   printf("ajout d'un sommet\n");
   insert_node(graphe, "premier sommet");
   afficher_graphe(graphe);

   printf("ajout d'un sommet\n");
   insert_node(graphe, "deuxieme  sommet");
   afficher_graphe(graphe);

   printf("ajout d'un sommet\n");
   insert_node(graphe, "troisieme sommet");
   afficher_graphe(graphe);

   delete_graph(graphe);
}


void test_unitaire_contains(){
   Graph * graphe = generer_graphe(4, 10, 0, 10);
   afficher_graphe(graphe);

   if(contains_node(graphe, "Noeud 1"))
      printf("correct : contient bien le noeuds 'Noeud 1'\n");
   else printf("TEST FAIL Ne contient pas 'Noeud 1' \n");

   if(contains_node(graphe, "Noeud 2"))
      printf("correct : contient bien le noeuds 'Noeud 2'\n");
   else printf("TEST FAIL Ne contient pas 'Noeud 2' \n");

   if(contains_node(graphe, "Noeud 3"))
      printf("correct : contient bien le noeuds 'Noeud 3'\n");
   else printf("TEST FAIL Ne contient pas 'Noeud 3' \n");

   if(contains_node(graphe, "Noeud 0"))
      printf("correct : contient bien le noeuds 'Noeud 0'\n");
   else printf("TEST FAIL Ne contient pas 'Noeud 0' \n");

   if(contains_node(graphe, "Noeud 5"))
      printf("TEST FAIL contient 'Noeud 5'\n");
   else printf("correct : ne contient pas 'Noeud 5' \n\n");


   if(contains_arc(graphe, "Noeud 1", "Noeud 2"))
      printf("contient 'Noeud 1' -> 'Noeud 2' \n");
   else printf("ne contient pas 'Noeud 1' -> 'Noeud 2' \n");

   if(contains_arc(graphe, "Noeud 3", "Noeud 0"))
      printf("contient 'Noeud 3' -> 'Noeud 0' \n");
   else printf("ne contient pas 'Noeud 3' -> 'Noeud 0' \n");

   if(contains_arc(graphe, "Noeud 0", "Noeud 1"))
      printf("contient 'Noeud 0' -> 'Noeud 1' \n");
   else printf("ne contient pas 'Noeud 0' -> 'Noeud 1' \n");

   if(contains_arc(graphe, "Noeud 2", "Noeud 1"))
      printf("contient 'Noeud 2' -> 'Noeud 1' \n");
   else printf("ne contient pas 'Noeud 2' -> 'Noeud 1' \n");

   if(contains_arc(graphe, "Noeud 0", "Noeud 2"))
      printf("contient 'Noeud 0' -> 'Noeud 2' \n");
   else printf("ne contient pas 'Noeud'0' -> 'Noeud 2' \n");


}

void test_unitaire_get_successors_predecessor(){

   Graph * graphe = generer_graphe(4, 10, 0, 10);
   afficher_graphe(graphe);

   List * successeurs = get_successors(graphe, "Noeud 1");
   afficher_liste(successeurs);
   
   List * predecesseurs = get_predecessors(graphe, "Noeud 1");
   afficher_liste(predecesseurs);

   delete_list(successeurs);
   delete_list(predecesseurs);

   successeurs = get_successors(graphe, "Noeud 2");
   afficher_liste(successeurs);
   
   predecesseurs = get_predecessors(graphe, "Noeud 2");
   afficher_liste(predecesseurs);


   delete_list(successeurs);
   delete_list(predecesseurs);
   delete_graph(graphe);

}

void test_unitaire_get_source_puit_node(){
   Graph * graphe = generer_graphe(4, 10, 0, 10);
   afficher_graphe(graphe);

   List * sources = get_sources_nodes(graphe);

   afficher_liste(sources);
   
   List * puits = get_puits_nodes(graphe);

   afficher_liste(puits);

   delete_list(sources);
   delete_list(puits);
   delete_graph(graphe);
}

void test_unitaire_get_source_puit_node2(){
   Graph *  graphe = init_graph();
   insert_node(graphe, "Noeud Sans Arc 1");
   insert_node(graphe, "Noeud Sans Arc 2");

   afficher_graphe(graphe);

   List *sources = get_sources_nodes(graphe);

   afficher_liste(sources);
   
   List *puits = get_puits_nodes(graphe);

   afficher_liste(puits);

   delete_list(sources);
   delete_list(puits);
   delete_graph(graphe);
}

void test_unitaire_get_min_max_weight(){
   Graph * graphe = generer_graphe(5, 12, -2, 15);
   afficher_graphe(graphe);

   char * source;
   char * puit;
   int poids;


   poids = arc_weight_min(graphe, &source, &puit, MIN_WEIGHT);
   printf("l'arc %s -> %s de poids min %d possède le plus petit poids min\n", source, puit, poids);

   poids = arc_weight_min(graphe, &source, &puit, MAX_WEIGHT);
   printf("l'arc %s -> %s de poids max %d possède le plus petit poids max\n", source, puit, poids);


   poids = arc_weight_max(graphe, &source, &puit, MIN_WEIGHT);
   printf("l'arc %s -> %s de poids min %d possède le plus grand poids min\n", source, puit, poids);

   poids = arc_weight_max(graphe, &source, &puit, MAX_WEIGHT);
   printf("l'arc %s -> %s de poids max %d possède le plus grand poids max\n", source, puit, poids);

   delete_graph(graphe);

}

void test_unitaire_delete_arc(){

   Graph * graphe = generer_graphe(3, 10, 0, 10);
   afficher_graphe(graphe);

   printf("suppression de l'arc 2->1\n");
   delete_arc(graphe, "Noeud 2", "Noeud 1");
   afficher_graphe(graphe);

   printf("suppression de l'arc 2->2\n");
   delete_arc(graphe, "Noeud 2", "Noeud 2");
   afficher_graphe(graphe);

    printf("suppression de l'arc 2->0\n");
   delete_arc(graphe, "Noeud 2", "Noeud 0");
   afficher_graphe(graphe);

   delete_graph(graphe);
}

void test_unitaire_delete_node(){

   Graph * graphe = generer_graphe(8, 50, 0, 10);
   afficher_graphe(graphe);

   printf("suppression du noeud 4\n");
   delete_node(graphe, "Noeud 4");
   afficher_graphe(graphe);

   printf("suppression du noeud 1\n");
   delete_node(graphe, "Noeud 1");
   afficher_graphe(graphe);

   printf("suppression du noeud 6\n");
   delete_node(graphe, "Noeud 6");
   afficher_graphe(graphe);

   printf("suppression du noeud 3\n");
   delete_node(graphe, "Noeud 3");
   afficher_graphe(graphe);

   printf("suppression du noeud 0\n");
   delete_node(graphe, "Noeud 0");
   afficher_graphe(graphe);

   printf("suppression du noeud 7\n");
   delete_node(graphe, "Noeud 7");
   afficher_graphe(graphe);

   printf("suppression du noeud 2\n");
   delete_node(graphe, "Noeud 2");
   afficher_graphe(graphe);

   printf("suppression du noeud 5\n");
   delete_node(graphe, "Noeud 5");
   afficher_graphe(graphe);

   delete_graph(graphe);
}

void test_unitaire_recherche_cycle(){
   
   Graph * graphe = generer_graphe(5, 20, 0, 10);

   afficher_graphe(graphe);
   if(recherche_cycle(graphe)){
      printf("il y a un cycle dans le graphe\n");
   }
   else{
      printf("il n'y a pas de cycle dans le graphe\n");
   }
   delete_graph(graphe);
}

void test_unitaire_trie(){
   printf("test de trie d'un graphe\n");

   Graph * graphe = generer_graphe(5, 20, 0, 10);
   afficher_graphe(graphe);

   printf(" ---  Tri croissant selon le poids minimum  ---\n");
   trier_arcs_croissant(graphe, MIN_WEIGHT);
   afficher_graphe(graphe);

   printf(" ---  Tri croissant selon le poids maximum  ---\n");
   trier_arcs_croissant(graphe, MAX_WEIGHT);
   afficher_graphe(graphe);

   printf(" ---  Tri décroissant selon le poids minimum  ---\n");
   trier_arcs_decroissant(graphe, MIN_WEIGHT);
   afficher_graphe(graphe);

   printf(" ---  Tri décroissant selon le poids maximum  ---\n");
   trier_arcs_decroissant(graphe, MAX_WEIGHT);
   afficher_graphe(graphe);

   delete_graph(graphe);
   printf("fin du test\n");
}

int main(int argc, const char * argv[]){
    
  // test_unitaire_graphe(); //OK
  // test_unitaire_insert(); //OK
   //test_unitaire_contains(); //OK
   //test_unitaire_get_successors_predecessor(); //OK
   //test_unitaire_get_source_puit_node(); //OK
   //test_unitaire_get_source_puit_node2(); //OK
   //test_unitaire_get_min_max_weight(); //OK
   //test_unitaire_delete_arc(); //OK
   //test_unitaire_delete_node(); //OK
   test_unitaire_recherche_cycle(); // OK
   test_unitaire_trie(); //OK
   return 0;
}






