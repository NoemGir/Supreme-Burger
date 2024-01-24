/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 24/10/23
 *  \file Implementation des methodes utiles des testes.
 **/
/*-----------------------------------------------------------------*/


#include "utils.h"
#include "../../src/utils_sd/utils_sd.h"
#include "../../src/lecture_csv/lecture_csv.h"
#include <sys/time.h>
#include<unistd.h>

Matrix * recuperer_generation_test(){
    if (system("python3 test/utils/votation.py -i test/utils/candidats.txt -v 5 -o csv/test.csv -s ','") != 0) perror("echec system 1");
    if (system("chmod +r csv/test.csv") != 0) perror("echec system 2");

    Matrix * resultat = main_lecture_csv("csv/test.csv", 1);
    return resultat;
}

Matrix * recuperer_fichier_vote(int argc, char * argv[]){

    if(argc == 1){
        return recuperer_generation_test();
    }

    if(argc <  3) {
        fprintf(stderr, "Usage : %s nomFichier mode(1 : vote, 2: duel)", argv[0]);
        exit(1);
    }

    char * nomFichier = (char *) argv[1];
    int mode = atoi(argv[2]);

    Matrix * matrice = main_lecture_csv(nomFichier, mode);
    return matrice;
}

Matrix * generer_matrice_int(int nb_ligne, int nb_colonne, int min, int max){
    printf("génération d'une matrice de %d ligne sur %d colonne d'entier entre %d et %d...\n", nb_ligne, nb_colonne, min, max);

    List * nom_colonne = init_list();

    for(int i = 1; i <= nb_colonne; i++){
        char nom[512];
        sprintf(nom,"colonne %d",i);
        insert_back(nom_colonne, nom, strlen(nom));
    }
     
    Matrix * matrice = init_matrix(nom_colonne);
    
    for (int i = 0; i < nb_ligne; i++){
        char nom[512];
        List * ligne = generer_liste_int(nb_colonne, min,max);
        sprintf(nom, "ligne %d", i+1);
        set_list_tag(ligne, nom);
        insert_row_back(matrice, ligne);
    }
    return matrice;
}

List * generer_liste_int(int nb_element, int min, int max){
    struct timeval currentTime;
	gettimeofday(&currentTime, NULL);

    List * liste = init_list();

    for (int i = 0; i < nb_element; i++){
            int valeur = (int)(((double)rand() * (double)(max+1 - min) / (double)RAND_MAX)) + min;
            srand(i*(currentTime.tv_sec * (int)1e6 + currentTime.tv_usec*time(NULL)));
            insert_back(liste, &valeur, sizeof(valeur));
    }
    set_list_tag(liste, "liste aléatoire d'entier");
    return liste;
}

List * generer_liste_char(int nb_element){

    List * liste = init_list();
    char element[50];
    for (int i = 0; i < nb_element; i++){
            
        sprintf(element, "Element %d", i);
        insert_back(liste, element, strlen(element));
    }
    set_list_tag(liste, "liste de chaine de charactère");
    return liste;
}

Graph * generer_graphe(int nb_noeuds, int nb_arcs, int min, int max){

    printf("génération d'un graphe de %d noeuds et %d arcs entre %d et %d...\n", nb_noeuds,nb_arcs, min, max);

    struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
    Graph * graphe = init_graph();
    char node_name[20];
    char first_node_name[20];
    char second_node_name[20];

    for (int i = 0; i < nb_noeuds; i++){
        sprintf(node_name, "Noeud %d", i);
        insert_node(graphe, node_name);
    }

    for (int i = 0; i < nb_arcs; i++){
        int nb_first_node = (int)(((double)rand() * (double)(nb_noeuds - 0) / (double)RAND_MAX)) + 0;
        sprintf(first_node_name, "Noeud %d", nb_first_node);
        srand((i+nb_first_node )*(currentTime.tv_sec * (int)1e6 + currentTime.tv_usec));
        
        int nb_second_node = (int)(((double)rand() * (double)(nb_noeuds - 0) / (double)RAND_MAX)) + 0;
        sprintf(second_node_name, "Noeud %d", nb_second_node);
        srand((i*nb_first_node+nb_second_node )*(currentTime.tv_sec * (int)1e6 + currentTime.tv_usec));
        
        if (!contains_arc(graphe,first_node_name, second_node_name)
         && strcmp(first_node_name, second_node_name) != 0
        && !contains_arc(graphe,second_node_name, first_node_name)){

            int valeur_1 = (int)(((double)rand() * (double)(max+1 - min) / (double)RAND_MAX)) + min;
            srand(i*(currentTime.tv_sec * (int)1e6 + currentTime.tv_usec));
            
            int valeur_2 = (int)(((double)rand() * (double)(max+1 - min) / (double)RAND_MAX)) + min;
            srand(i*valeur_1*(currentTime.tv_sec * (int)1e6 + currentTime.tv_usec));

            if(valeur_1 < valeur_2)
                insert_arc(graphe, first_node_name, second_node_name, valeur_1, valeur_2);
            else
            insert_arc(graphe, first_node_name, second_node_name, valeur_2, valeur_1);
        }
        
        

        
    }
    return graphe;
}

void afficher_liste(List * liste){
    liste_dans_fichier(liste, stdout);
}

void afficher_graphe(Graph * graphe){
    graphe_dans_fichier(graphe, stdout);
}

void afficher_matrice(Matrix * matrice){
    matrice_dans_fichier(matrice, stdout);
}