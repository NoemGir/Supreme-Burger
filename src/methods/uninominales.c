/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author  AIT-MESSAOUD TINHINANE
 *  \date 28/10/23
 *  \brief Implémentation des calculs du resultat du vote grace à la methode Uninominale
 */
/*-----------------------------------------------------------------*/

#include "uninominales.h"
#include "../datatypes/list.h"
#include "../datatypes/matrix.h"
#include "../utils_sd/utils_sd.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define N 100
char buffer[N];

/**

 * \brief va comparer un type void * avec type int car les elements de la matrice sont stockés en
 * tant que void*
 *
 * \param data
 * \param elem
 * \return true si les elements sont egaux
 * \return false si les elements ne sont pas egaux
 */
bool compare_avec_int(void *data, int elem) { return (*(int *)data == elem); }

/**
 * \brief cette fonction va renvoyer l'indice du max du vote (à noter que les votes sont classés
 * dans le sens inverse tel que 1 est considéré le maximum et 10 le minimum)
 *
 * \param l Liste des votes d'un votant
 * \return int renvoie l'indice du vote maximal
 */
bool max_votant(List *l, int *indiceMax) {
    ptrListIterator it = init_listIterator(l, FORWARD_ITERATION);
    *indiceMax = 0;
    int max = *((int *)listIterator_data(it));
    int valeur;
    bool unicite;
    for (it = listIterator_next(it); !listIterator_end(it); it = listIterator_next(it)) {
        valeur = *((int *)listIterator_data(it));
        if (valeur == max)
            unicite = false;
        else if (valeur != -1 && max > valeur) {
            max = valeur;
            *indiceMax = listIterator_index_current(it);
            unicite = true;
        }
    }
    delete_listIterator(it);
    return unicite;
}

/**
 * \brief cette fonction va renvoyer un tableau regroupant le numero representant un vote pour un
 * candidat sinon renvoie -1 si son vote n'est pas eligible (eligible si son vote max n'est present
 * qu'une seule fois)
 *
 * \param m matrice initiale
 * \return int* tableau renvoyant pour chaque ligne le vote max(le minimum ici étant le plus fort)
 */

int *maximum_lignes(Matrix *m) {
    int nb_lignes = matrix_rows(m);
    int *max = (int *)malloc(nb_lignes * sizeof(int));
    if (max == NULL) {
        free(max);
        fprintf(stderr, "erreur pendant l'allocation du tableau de votes \n");
        return NULL;
    }
    int imaxl;
    bool unicite;
    ptrList bulletin;
    for (int i = 0; i < nb_lignes; i++) {
        bulletin = get_row_at(m, i);
        unicite = max_votant(bulletin, &imaxl);
        if (unicite)
            max[i] = imaxl;
        else {
            sprintf(buffer, "votant %d a un vote non conforme-on dira qu'il ne se prononce pas", i);
            ajouter_texte_log(buffer);
            max[i] = -1;
        }
    }
    clear_list(bulletin);
    return max;
}
/**
 * \brief a partir de la matrice, la fonction va recuperer le tableau de score en calculant pour
 * chaque candidat le nombre de personnes qui ont voté pour eux (le max) on
 * considere ici que l'id du candidat est sa colonne dans le tableau (candidat 0 , colonne 0 du
 * tableau)
 *
 * \param m : matrice liant les votes de chaque votant aux candidats
 * \return int* recupere_vote : tableau du score de chaque candidat (score numerique et non
 * pourcentage)
 */

int *recup_tab_score(Matrix *m) {
    int *vote_ligne = maximum_lignes(m);

    if (vote_ligne == NULL) {
        free(vote_ligne);
        fprintf(stderr, "erreur\n");
        return NULL;
    }
    int nbCandidats = matrix_cols(m);
    int *recupere_vote = (int *)malloc((nbCandidats) * sizeof(int));
    if (recupere_vote == NULL) {
        free(recupere_vote);
        free(vote_ligne);

        fprintf(stderr, "erreur init tableau \n");
        return NULL;
    }
    memset(recupere_vote, 0, (nbCandidats) * sizeof(int)); // init le tableau à 0 partout
    for (int i = 0; i < matrix_rows(m); i++) {
        if (vote_ligne[i] != -1)
            recupere_vote[vote_ligne[i]]++;
    }
    free(vote_ligne);
    return recupere_vote;
}

/**
 *
 * \brief ceci est la fonction principale d'appel si on veut une methode uninominale à un tour
 *
 * \param matrice_initialise : matrice initialisee a partir du fichier csv regroupant pour chaque
 * ligne ,representant un votant, le classement de 1-10 pour chaque candidat (represente au niveau
 * des colonnes)
 * \return vainqueur : structure du vainqueur regroupant nom du vainqueur et son score
 */

vainqueur main_uninominale_1(Matrix *matrice_initialise) {

    ajouter_texte_log("Vous avez choisi la methode uninominale à 1 tour \n");

    int *votes_finaux = recup_tab_score(matrice_initialise);

    if (votes_finaux == NULL) {
        free(votes_finaux);
        fprintf(stderr, "erreur recuperation du tableau de scores \n");
        exit(EXIT_FAILURE);
    }

    /*****************************************ecriture log********************************/
    for (int i = 0; i < matrix_cols(matrice_initialise); i++) {
        sprintf(buffer, "candidat '%s' numero %d  a recu %d votes ",
                get_tag_column(matrice_initialise, i), i, votes_finaux[i]);
        ajouter_texte_log(buffer);
    }
    /*****************************************ecriture log********************************/

    List *recurrence_max = init_list();
    int id_max = recherche_max_tab(votes_finaux, matrix_cols(matrice_initialise), recurrence_max);
    sprintf(buffer, "Le vainqueur est ex-aequo avec %d personnes\n", list_size(recurrence_max));
    printf("%s", buffer);
    ajouter_texte_log(buffer);
    ptrListIterator it = init_listIterator(recurrence_max, FORWARD_ITERATION);
    for (it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it)) {
        int indice = *((int *)listIterator_data(it));

        sprintf(buffer, "ex-aequo avec %s", get_tag_column(matrice_initialise, indice));
        ajouter_texte_log(buffer);
    }
    delete_listIterator(it);

    /*prendre le plus vieux et mettre a jour id_max avant de
    passer à la suite

    Comme on ne peut pas choisir le plus vieux ici on prendra simplement le premier candidat apparu
    dans le parcours
    */

    int score_max = votes_finaux[id_max];
    vainqueur v;
    v.nom = get_tag_column(matrice_initialise, id_max);
    v.score = (float)score_max / matrix_rows(matrice_initialise);
    sprintf(buffer, "vainqueur %s avec score %f \n", v.nom, v.score);
    ajouter_texte_log(buffer);
    delete_list(recurrence_max);
    free(votes_finaux);
    return v;
}

/**
 * \brief cette fonction va ecrire dans les struct vainqueur les 2 premiers vainqueurs soit v1
 * possedant le plus haut score au premier tour et v2 qui le suit juste apres on va donc recuperer
 * le tableau des scores et on va comparer
 *
 * \param matrice_initialise : matrice initialisee du csv liant votants aux candidats
 * \param v1 : structure vainqueur initialisee dans la fonction main_uninominale_2, on y mettra la
 * personne ayant eu le plus haut score
 * \param v2 : structure vainqueur initialisee dans la fonction main_uninominale_2, on y mettra la
 * personne ayant eu le second plus haut score
 */

void uni2_premier_tour(Matrix *matrice_initialise, vainqueur *v1, vainqueur *v2) {

    int *votes_finaux = recup_tab_score(matrice_initialise);

    if (votes_finaux == NULL) {
        fprintf(stderr, "erreur recuperation du tableau de scores \n");
        exit(EXIT_FAILURE);
    }

    /*****************************************ecriture log********************************/
    ajouter_texte_log("\n Les votes finaux sont : \n");
    for (int i = 0; i < matrix_cols(matrice_initialise); i++) {
        sprintf(buffer, "candidat '%s' numero %d  a recu %d votes \n",
                get_tag_column(matrice_initialise, i), i, votes_finaux[i]);
        ajouter_texte_log(buffer);
    }
    /*****************************************ecriture log********************************/

    int score_max1, score_max2;
    int id_max1, id_max2;

    if (votes_finaux[0] > votes_finaux[1]) {
        score_max1 = votes_finaux[0];
        score_max2 = votes_finaux[1];
        id_max1 = 0;
        id_max2 = 1;
    } else {
        score_max1 = votes_finaux[1];
        score_max2 = votes_finaux[0];
        id_max1 = 1;
        id_max2 = 0;
    }
    for (int i = 2; i < matrix_cols(matrice_initialise); i++) {

        if (votes_finaux[i] > score_max1) {
            score_max2 = score_max1;
            id_max2 = id_max1;
            score_max1 = votes_finaux[i];
            id_max1 = i;
        } else if (votes_finaux[i] > score_max2) {
            score_max2 = votes_finaux[i];
            id_max2 = i;
        }
    }

    v1->nom = get_tag_column(matrice_initialise, id_max1);
    v1->score = (float)score_max1 / matrix_rows(matrice_initialise);
    affichage_uninominale("uninominale 2 tours", matrix_cols(matrice_initialise),
                          matrix_rows(matrice_initialise), v1);
    v2->nom = get_tag_column(matrice_initialise, id_max2);
    v2->score = (float)score_max2 / matrix_rows(matrice_initialise);
    affichage_uninominale("uninominale 2 tours", matrix_cols(matrice_initialise),
                          matrix_rows(matrice_initialise), v2);

    /*****************************************ecriture log********************************/
    ajouter_texte_log("Les 2 vainqueurs du premier tour sont : \n");
    sprintf(buffer, "vainqueur  %s avec score %f \n", v1->nom, v1->score);
    ajouter_texte_log(buffer);
    sprintf(buffer, "vainqueur %s avec score %f \n", v2->nom, v2->score);
    ajouter_texte_log(buffer);
    /*****************************************ecriture log********************************/
    int scoreDeuxiemeTour = score_max1 + score_max2;

    v1->score = (float)score_max1 / scoreDeuxiemeTour;

    v2->score = (float)score_max2 / scoreDeuxiemeTour;

    free(votes_finaux);
}

/**
 *
 * \brief ceci est la fonction principale d'appel si on veut une methode uninominale à deux tours
 *
 * \param matrice_initialise : matrice initialisee a partir du fichier csv regroupant pour chaque
 * ligne ,representant un votant, le classement de 1-10 pour chaque candidat (represente au niveau
 * des colonnes)
 * \return vainqueur : structure du vainqueur regroupant nom du vainqueur et son score
 */

vainqueur main_uninominale_2(Matrix *matrice_initialise) {

    /*****************************************ecriture log********************************/
    ajouter_texte_log("Vous avez choisi la methode uninominale à 2 tours \n");
    /*****************************************ecriture log********************************/

    vainqueur v1, v2;
    uni2_premier_tour(matrice_initialise, &v1, &v2);

    if (v1.score > 0.5) {
        sprintf(buffer, "vainqueur  %s avec score %f \n", v1.nom, v1.score);
        ajouter_texte_log(buffer);
        return v1;
    }

    /* on pourrait faire un 2e tour mais ceci ne servirait a rien dans notre cas ...
    Verifier si egalite voir l'age du candidat (hors ici les burgers n'ont pas d'age)
    sinon comparer les scores (hors on a déjà comparer les scores )
    if (v1.score == v2.score){
        if (v1.age >v2.age)
            return v1;
        else
            return v2;
    }

    */
    /* simulation d'un second tour*/
    if (v2.score > v1.score) {
        sprintf(buffer, "vainqueur final %s avec score %f \n", v2.nom, v2.score);
        ajouter_texte_log(buffer);
        return v2;
    } else {
        sprintf(buffer, "vainqueur final %s avec score %f \n", v1.nom, v1.score);
        ajouter_texte_log(buffer);
        return v1;
    }
}
