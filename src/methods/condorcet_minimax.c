/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author RADIONOVA Veronika
 *  \date 12/11/23
 *  \file Implémentation des calculs du resultat du vote grace à la methode des Minimax ( Condorcet
 *paradoxe )
 **/
/*-----------------------------------------------------------------*/

#include "condorcet_minimax.h"
#include "../utils_sd/utils_sd.h"
#include "../../test/utils/utils.h"
#include <stdio.h>
#include <stdlib.h>


List * obtenir_pires_resultats(Graph *graph_vote,List * candidats){
    char message_log[512];
    List *pires_resultats = init_list();

    /* Mise a jour du log */
    ajouter_texte_log("Le candidat vainqueur sera calculé ainsi : ");
    ajouter_texte_log(" - 1) Pour chaque candidat, prendre le poids maximum par pair du candidat relié avec un candidat gagnant (-> poids de préférénce du candidat gagnant)");
    ajouter_texte_log(" - 2) Pour chaque candidat, séléctionner le plus grand parmis les poids par pair obtenus");
    ajouter_texte_log(" - 3) Après avoir obtenue le pire poids par pair de tous les candidats, séléctionner le candidat qui a le plus petit pire poids par pair");

   
    ptrListIterator it_candidat = init_listIterator(candidats,FORWARD_ITERATION);
    /* récupération des pires resultats de vote pour tous les candidats (un pour chacun) */
    for(it_candidat = listIterator_begin(it_candidat); !listIterator_end(it_candidat); it_candidat = listIterator_next(it_candidat)) {
        
        char *candidat_observe = (char *) listIterator_data(it_candidat);

        List *arcs = get_predecessors(graph_vote, candidat_observe);
        int pire_resultat_max = 0;
        int pire_resultat;
        char * candidat_rival_gagnant = NULL;
        /* parcours de tous les arcs qui contiennent le candidat observé à la deuxième position, donc predessesseur */
        ListIterator * it_arcs = init_listIterator(arcs, FORWARD_ITERATION);

        for(it_arcs = listIterator_begin(it_arcs); !listIterator_end(it_arcs); it_arcs = listIterator_next(it_arcs)) {
            
           char * predecesseur = (char *) listIterator_data(it_arcs);

            get_weight(graph_vote, predecesseur, candidat_observe, NULL, &pire_resultat);
            if (pire_resultat_max < pire_resultat) {
                pire_resultat_max = pire_resultat;
                candidat_rival_gagnant = predecesseur;
            }
        }
        delete_listIterator(it_arcs);

        /* Mise a jour du log */
        sprintf(message_log,"le max des résultat perdant du candidat %s est %d contre le candidat %s", candidat_observe, pire_resultat_max,candidat_rival_gagnant );
        ajouter_texte_log(message_log);

        /* ajout d'un resultat dans la liste des pires scores suivant l'emplacement d'un candidat dans la liste des candidats */
        insert_back(pires_resultats, &pire_resultat_max, sizeof(pire_resultat_max));

        delete_list(arcs);
    }
    delete_listIterator(it_candidat);

    return pires_resultats;
}


/**
 *  \brief chercher le candidat qui va gagner le vote suivant le Méthode de Condorcet Minimax
 *
 *  \param[in] graph_vote
 *
 *  \return le vainqueur de la Méthode de Condorcet Minimax
 */
char *main_condorcet_minimax(Graph *graph_vote) {
    char *vainqueur;
    char message_log[512];
    List *pires_resultats;
    List *candidats;


    candidats = get_nodes(graph_vote);
    pires_resultats = obtenir_pires_resultats(graph_vote, candidats);

    /* recherche d'un candidant avec le meilleur resultat parmi les pires */
    int val;
    int position = 0; //recherche_min(pires_resultats, &val);
    delete_list(pires_resultats);

    /* Récuperer le candidat vainqueur dans son propre emplacment mémoire afin de pouvoir supprimer la liste des candidats */
    char * candidat_vainqueur =  list_get_element_at(candidats, position);


    vainqueur = sauvegarde_string(candidat_vainqueur);

    /* Mise a jour du log */
    sprintf(message_log, "Le candidat gagnant est donc %s avec un pire score de %d",candidat_vainqueur, val );
    ajouter_texte_log(message_log);

    delete_list(candidats);
    return vainqueur;
}