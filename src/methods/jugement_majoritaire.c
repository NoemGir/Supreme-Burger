/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 22/10/23
 *  \brief Implémentation des calculs du resultat du vote grace à la methode de Jugement Majoritaire
 **/
/*-----------------------------------------------------------------*/

#include "jugement_majoritaire.h"
#include "../datatypes/list.h"
#include "../datatypes/matrix.h"
#include "../utils_sd/utils_sd.h"

#include <stdio.h>
#include <stdlib.h>

#define TRES_BIEN 0
#define BIEN 1
#define ASSEZ_BIEN 2
#define PASSABLE 3
#define MEDIOCRE 4
#define A_FUIR 5

#define PARTISANT 0
#define OPPOSANT 2

int bulletin = JUGEMENT;

/** \fn get_categorie_name
 *  \brief recherche la catégorie indiquée par le numéro
 *
 *  \param[in] num_categorie le numero identificateur d'une catégorie
 *
 *  \return  retourne une chaine de caractère correspondant au numero de la catégorie
 */
char *get_categorie_name(int num_categorie) {
    switch (num_categorie) {
    case TRES_BIEN:
        return "Très Bien";
    case BIEN:
        return "Bien";
    case ASSEZ_BIEN:
        return "Assez Bien";
    case PASSABLE:
        return "Passable";
    case MEDIOCRE:
        return "Mediocre";
    case A_FUIR:
        return "A fuir";
    default:
        fprintf(stderr, "Erreur catégorie\n");
        return NULL;
    }
}

int categorie_du_vote(int vote) {
    if (bulletin == CONDORCET) {
        switch (vote) {
        case 1:
            return TRES_BIEN;
        case 2 ... 3:
            return BIEN;
        case 4 ... 5:
            return ASSEZ_BIEN;
        case 6 ... 7:
            return PASSABLE;
        case 8 ... 9:
            return MEDIOCRE;
        case 10:
            return A_FUIR;
        }
    } else {
        switch (vote) {
        case 1:
            return TRES_BIEN;
        case 2:
            return BIEN;
        case 3:
            return ASSEZ_BIEN;
        case 4:
            return PASSABLE;
        case 5:
            return MEDIOCRE;
        case 6:
            return A_FUIR;
        }
    }
    return -1;
}

/** \fn creer_histogramme
 *  \brief creer l'histogramme nous permettant de rechercher la mediane de chaque candidat
 *
 *  \param[in] matrice_initial La matrice possèdant reliant les votes de chaque votants aux
 * candidats
 *
 *  \return Retourne la matrice histogramme qui, pour chaque candidat, donne le nombre de vote
 * obtenue dans chaque catégories ( de Très bien à A Fuir)
 */
Matrix *creer_histogramme(Matrix *matrice_initiale) {

    List *ligne;
    int nb_TB;
    int nb_B;
    int nb_AB;
    int nb_P;
    int nb_M;
    int nb_AFuir;
    int element;

    List *columnName = init_list();
    insert_back(columnName, "Très Bien", strlen("Très Bien"));
    insert_back(columnName, "Bien", strlen("Bien"));
    insert_back(columnName, "Assez Bien", strlen("Assez Bien"));
    insert_back(columnName, "Passable", strlen("Passable"));
    insert_back(columnName, "Mediocre", strlen("Mediocre"));
    insert_back(columnName, "A Fuir", strlen("A Fuir"));

    Matrix *histogramme = init_matrix(columnName);

    for (int indice_colonne = 0; indice_colonne < matrix_cols(matrice_initiale); indice_colonne++) {

        ligne = init_list();
        nb_TB = 0;
        nb_B = 0;
        nb_AB = 0;
        nb_P = 0;
        nb_M = 0;
        nb_AFuir = 0;
        for (int indice_ligne = 0; indice_ligne < matrix_rows(matrice_initiale); indice_ligne++) {
            element =
                *((int *)matrix_get_element_at(matrice_initiale, indice_ligne, indice_colonne));
            switch (categorie_du_vote(element)) {
            case TRES_BIEN:
                nb_TB++;
                break;
            case BIEN:
                nb_B++;
                break;
            case ASSEZ_BIEN:
                nb_AB++;
                break;
            case PASSABLE:
                nb_P++;
                break;
            case MEDIOCRE:
                nb_M++;
                break;
            case A_FUIR:
                nb_AFuir++;
                break;
            }
        }
        insert_front(ligne, &nb_AFuir, sizeof(int));
        insert_front(ligne, &nb_M, sizeof(int));
        insert_front(ligne, &nb_P, sizeof(int));
        insert_front(ligne, &nb_AB, sizeof(int));
        insert_front(ligne, &nb_B, sizeof(int));
        insert_front(ligne, &nb_TB, sizeof(int));

        set_list_tag(ligne, get_tag_column(matrice_initiale, indice_colonne));
        insert_row_back(histogramme, ligne);
    }
    return histogramme;
}

/** \fn s
 *  \brief Recherche le / les candidat(s) avec la meilleur mediane
 *
 *  \param[in] histogramme la matrice histogramme
 *  \param[in] nbVotants le nombre total de votants
 *  \param[out] categorie la categorie de la meilleur mediane (Très bien à A Fuir).
 *
 *  \return  Retourne la liste contenant les indices des candidats en égalité sur la meilleur
 * catégorie. Le tag de la liste correspond au nom du premier candidat sur la liste
 */
List *calcul_meilleures_medianes(Matrix *histogramme, int nbVotants, int *categorie) {

    int mediane = nbVotants % 2 == 0 ? nbVotants / 2 : (nbVotants - 1) / 2 + 1;
    List *meilleures_medianes = init_list();
    int categorie_max = A_FUIR;
    int compteur;
    int element;
    int categorie_candidat;
    for (int indice_candidat = 0; indice_candidat < matrix_rows(histogramme); indice_candidat++) {

        compteur = 0;
        ptrListIterator it =
            init_listIterator(get_row_at(histogramme, indice_candidat), FORWARD_ITERATION);

        element = *((int *)listIterator_data(it));

        while (!listIterator_end(it) && (compteur + element) < mediane) {
            compteur += element;
            it = listIterator_next(it);
            element = *((int *)listIterator_data(it));
        }

        categorie_candidat = listIterator_index_current(it);

        if (categorie_candidat < categorie_max) {
            categorie_max = categorie_candidat;
            clear_list(meilleures_medianes);
            insert_front(meilleures_medianes, &indice_candidat, sizeof(int));
            set_list_tag(meilleures_medianes, get_tag_row(histogramme, indice_candidat));
        } else if (categorie_candidat == categorie_max) {
            insert_back(meilleures_medianes, &indice_candidat, sizeof(int));
        }
        delete_listIterator(it);
    }
    *categorie = categorie_max;
    return meilleures_medianes;
}

/** \fn obtenir_matrice_pourcentage
 *  \brief Methode des groupes d'insatisfaits : retourne la matrice comportants les pourcentages de
 * votes suppérieurs et inférieurs à la medianes pour chaque candidat
 *
 *  \param[in] histogramme la matrice histogramme
 *  \param[in] candidats_egaux la liste des candidats ayant la même meilleur médiane.
 *  \param[in] categorie la categorie de la meilleur mediane (Très bien à A Fuir).
 *
 *  \return  retourne la matrice qui, pour chaque candidat égal, met d'un coté le pourcentage des
 * partisants et d'un autre le pourcentage des opposants.
 */
Matrix *obtenir_matrice_pourcentage(Matrix *histogramme, List *candidats_egaux, int nbVotants,
                                    int categorie) {
    List *infoCandidat;
    double somme_pourcentage;
    List *ligne_candidat;
    int nbVote;
    char *nom_categorie = get_categorie_name(categorie);
    ptrListIterator it_candidats_egaux = init_listIterator(candidats_egaux, FORWARD_ITERATION);
    ptrListIterator it_info_candidat;

    List *columnName = init_list();
    insert_back(columnName, "% partisants", strlen("% partisants"));
    insert_back(columnName, "    Meilleure catégorie", strlen("    Meilleure catégorie"));
    insert_back(columnName, "% opposants", strlen("% opposants"));
    Matrix *matrice_pourcentage = init_matrix(columnName);

    for (it_candidats_egaux = listIterator_begin(it_candidats_egaux);
         !listIterator_end(it_candidats_egaux);
         it_candidats_egaux = listIterator_next(it_candidats_egaux)) {

        ligne_candidat = init_list();
        int row = *((int *)listIterator_data(it_candidats_egaux));
        infoCandidat = get_row_at(histogramme, row);

        set_list_tag(ligne_candidat, get_list_tag(infoCandidat));

        it_info_candidat = init_listIterator(infoCandidat, FORWARD_ITERATION);

        somme_pourcentage = 0;
        while (listIterator_index_current(it_info_candidat) < categorie) {
            nbVote = *((int *)listIterator_data(it_info_candidat));
            somme_pourcentage += (double)nbVote / nbVotants * 100;
            it_info_candidat = listIterator_next(it_info_candidat);
        }
        it_info_candidat = listIterator_next(it_info_candidat);

        insert_front(ligne_candidat, &somme_pourcentage, sizeof(double));
        insert_back(ligne_candidat, nom_categorie, strlen(nom_categorie) + 1);

        somme_pourcentage = 0;
        while (!listIterator_end(it_info_candidat)) {
            nbVote = *((int *)listIterator_data(it_info_candidat));
            somme_pourcentage += (double)nbVote / nbVotants * 100;
            it_info_candidat = listIterator_next(it_info_candidat);
        }
        insert_back(ligne_candidat, &somme_pourcentage, sizeof(double));

        insert_row_back(matrice_pourcentage, ligne_candidat);
        delete_listIterator(it_info_candidat);
    }
    delete_listIterator(it_candidats_egaux);
    return matrice_pourcentage;
}

/** \fn recherche_vainqueur
 *  \brief recherche le vainqueur parmi les candidats à la mention egal.
 *
 *  \param[in] matrice_pourcentage la matrice composée des pourcentages des mentions supperieurs et
 * inférieurs de tous les candidats à la mention égale.
 *
 *  \return  retourne le nom du vainqueur.
 */
char *recherche_vainqueur(Matrix *matrice_pourcentage) {
    int vainqueur = 0;
    double valeur_max = 0;
    int categorie_max;
    /// \var ici, categorie_max appartient a : {partisants = 0 ; opposants = 1}

    if (matrix_rows(matrice_pourcentage) == 1) {
        return get_tag_row(matrice_pourcentage, vainqueur);
    }

    for (int candidat = 0; candidat < matrix_rows(matrice_pourcentage); candidat++) {
        ListIterator *it =
            init_listIterator(get_row_at(matrice_pourcentage, candidat), BACKWARD_ITERATION);
        while (!listIterator_end(it)) {

            if (listIterator_index_current(it) == 1)
                listIterator_next(it);

            int indice = listIterator_index_current(it);

            double pourcentage = *((double *)listIterator_data(it));

            if (pourcentage > valeur_max) {
                valeur_max = pourcentage;
                vainqueur = candidat;
                categorie_max = indice;
            }
            listIterator_next(it);
        }
        delete_listIterator(it);
    }

    if (categorie_max == PARTISANT) {
        return get_tag_row(matrice_pourcentage, vainqueur);
    } else {
        ajouter_texte_log(
            "Le pourcentage principal est celui d'un opposant, on enlève sa ligne : ");
        delete_row_at(matrice_pourcentage, vainqueur);
        ajouter_matrice_log(matrice_pourcentage);
        return recherche_vainqueur(matrice_pourcentage);
    }
}

/** \fn main_jugement_majoritaire
 *  \brief calcul le vainqueur par la methode du jugement majoritaire
 *
 *  \param[in] matrice_initial La matrice reliant les votes de chaque votants aux candidats
 *  \param[in] scrutin scrutin = 0 si on prend le fichier jugement majoritaire et scrutin = 1 si on
 * prend le fichier condorcet
 *
 *  \return  retourne le nom du candidat qui a gagné.
 */
char *main_jugement_majoritaire(Matrix *matrice_initiale, int scrutin) {

    char message[60];
    char *vainqueur;
    int meilleure_categorie;
    bulletin = scrutin;
    int nbVotant = matrix_rows(matrice_initiale);
    Matrix *histogramme = creer_histogramme(matrice_initiale);
    ajouter_texte_log("Histogramme obtenue : ");
    ajouter_matrice_log(histogramme);

    List *meilleures_medianes =
        calcul_meilleures_medianes(histogramme, nbVotant, &meilleure_categorie);
    char messageCategorie[50];
    sprintf(messageCategorie, "la meilleure catégorie est : %s",
            get_categorie_name(meilleure_categorie));

    if (list_size(meilleures_medianes) == 1) {

        vainqueur = sauvegarde_string(get_list_tag(meilleures_medianes));
    } else {
        // Cas d'égalités de plusieurs candidats
        ajouter_texte_log(
            "Cas de resolution des ambiguités : (methode des groupes d'insatisfaits) ");

        Matrix *matrice_pourcentage = obtenir_matrice_pourcentage(histogramme, meilleures_medianes,
                                                                  nbVotant, meilleure_categorie);

        ajouter_texte_log("Matrice pourcentage: ");
        ajouter_matrice_log(matrice_pourcentage);

        vainqueur = sauvegarde_string(recherche_vainqueur(matrice_pourcentage));
        delete_matrix(matrice_pourcentage);
    }

    
    delete_list(meilleures_medianes);
    delete_matrix(histogramme);
    return vainqueur;
}