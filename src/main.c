#include "../test/utils/utils.h"
#include "datatypes/graph.h"
#include "datatypes/matrix.h"
#include "lecture_csv/lecture_csv.h"
#include "methods/condorcet.h"
#include "methods/condorcet_minimax.h"
#include "methods/condorcet_paires.h"
#include "methods/condorcet_schulze.h"

#include "methods/jugement_majoritaire.h"
#include "methods/uninominales.h"
#include "utils_sd/utils_sd.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNI1 0
#define UNI2 1
#define CM 2
#define CP 3
#define CS 4
#define JM 5
#define ALL 6

#define VoteCondorcet 10
#define jugement_majoritaire 11
#define MatriceDuel 12

/*********************************************AFFICHAGE********************************************************/

void affichage(char *methode, int nbCandidat, int nbVotes, char *vainqueur) {
    if (nbVotes != 0)
        printf(" Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s\n", methode,
               nbCandidat, nbVotes, vainqueur);
    else
        printf(" Mode de scrutin : %s, %d candidats, nombre votants inconnu, vainqueur = %s\n",
               methode, nbCandidat, vainqueur);
}

/*****************************************methodes utilitaires
 * ********************************************************/

bool methodExists(char *methode, int *indiceMethode) {
    char *possibleMethodes[] = {"uni1", "uni2", "cm", "cp", "cs", "jm", "all"};
    bool found = false;
    for (int i = 0; i < 7; i++) {
        if (strcmp(possibleMethodes[i], methode) == 0) {
            *indiceMethode = i;
            found = true;
            break;
        }
    }
    return found;
}

bool compatibilyArguments(int tag, char *method) {
    switch (tag) {
    case (MatriceDuel):
        printf("pour matrice de duel  \n");
        if (strstr(method, "c") != NULL)
            return true;
        break;
    case (jugement_majoritaire):
        printf("pour jugement majoritaire  \n");
        if (strstr(method, "jm") != NULL)
            return true;
        break;
    case (VoteCondorcet):
        printf("pour VoteCondorcet \n");
        return true;
        break;

    case (0):
        return true;
        break;
    }
    return false;
}

void help() {
    FILE *fichier = fopen("help.txt", "r");

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
        printf("%s", ligne);
    fclose(fichier);
}

/*********************************************RESULTAT POUR CHAQUE
 * VOTE********************************************************/

void resultatUninominal1(char *votingFile) {
    ptrMatrix matriceNormale = main_lecture_csv(votingFile, 1);
    char texteLog[100];
    sprintf(texteLog, "Vous avez choisi pour methode Uninomial à un tour");
    ajouter_texte_log(texteLog);
    ajouter_matrice_log(matriceNormale);
    vainqueur v = main_uninominale_1(matriceNormale);
    affichage_uninominale("uninominale 1 tour", matrix_cols(matriceNormale),
                          matrix_rows(matriceNormale), &v);
    delete_matrix(matriceNormale);
}

void resultatUninominal2(char *votingFile) {
    ptrMatrix matriceNormale = main_lecture_csv(votingFile, 1);
    char texteLog[100];
    sprintf(texteLog, "Vous avez choisi pour methode Uninominal à deux tours");
    ajouter_texte_log(texteLog);
    ajouter_matrice_log(matriceNormale);
    vainqueur v = main_uninominale_2(matriceNormale);
    affichage_uninominale("uninominale 2 tours", matrix_cols(matriceNormale),
                          matrix_rows(matriceNormale), &v);
    delete_matrix(matriceNormale);
}

void resultatCondorcetMinimax(char *votingFile, int tag) {
    ptrMatrix matriceDuel, matriceNormale;

    if (tag == VoteCondorcet) {
        matriceNormale = main_lecture_csv(votingFile, 1);
        matriceDuel = initialisation_matrice(matriceNormale);
    } else {
        matriceDuel = main_lecture_csv(votingFile, 2);
    }

    char texteLog[100];
    sprintf(texteLog, "Vous avez choisi pour methode Condorcet Minimax");
    ajouter_texte_log(texteLog);

    ajouter_matrice_log(matriceDuel);

    ptrGraph grapheNormale = initialisation_graphe(matriceDuel);
    char *nomVainqueur = main_condorcet_minimax(grapheNormale);

    sprintf(texteLog, "vainqueur final pour methode condorcet minimax %s  \n", nomVainqueur);
    ajouter_texte_log(texteLog);

    if (tag == VoteCondorcet) {
        affichage("Condorcet minimax ", matrix_cols(matriceDuel), matrix_rows(matriceNormale),
                  nomVainqueur);
        delete_matrix(matriceNormale);
    } else {

        affichage("Condorcet minimax ", matrix_cols(matriceDuel), 0, nomVainqueur);
    }
    delete_matrix(matriceDuel);
    delete_graph(grapheNormale);
    free(nomVainqueur);
}

void resultatJugement(char *votingFile, int scrutin) {
    ptrMatrix matriceNormale = main_lecture_csv(votingFile, 1);
    char texteLog[100];
    sprintf(texteLog, "Vous avez choisi pour methode Jugement majoritaire");
    ajouter_texte_log(texteLog);
    ajouter_matrice_log(matriceNormale);

    char *nomVainqueur;
    nomVainqueur = main_jugement_majoritaire(matriceNormale, scrutin);

    sprintf(texteLog, "vainqueur final pour methode Jugement majoritaire %s  \n", nomVainqueur);
    ajouter_texte_log(texteLog);

    affichage("jugement majoritaire", matrix_cols(matriceNormale), matrix_rows(matriceNormale),
              nomVainqueur);

    delete_matrix(matriceNormale);
    free(nomVainqueur);
}

void resultatCondorcetSchulze(char *votingFile, int tag) {
    ptrMatrix matriceDuel, matriceNormale;

    if (tag == VoteCondorcet) {
        matriceNormale = main_lecture_csv(votingFile, 1);

        matriceDuel = initialisation_matrice(matriceNormale);
    } else {
        matriceDuel = main_lecture_csv(votingFile, 2);
    }

    char texteLog[100];
    sprintf(texteLog, "Vous avez choisi pour methode Condorcet Schulze");
    ajouter_texte_log(texteLog);

    ajouter_matrice_log(matriceDuel);

    ptrGraph grapheNormale = initialisation_graphe(matriceDuel);
    char *nomVainqueur = main_condorcet_schulze(grapheNormale);

    sprintf(texteLog, "vainqueur final pour methode condorcet schulze %s  \n", nomVainqueur);
    ajouter_texte_log(texteLog);

    if (tag == VoteCondorcet) {
        affichage("Condorcet Schulze", matrix_cols(matriceDuel), matrix_rows(matriceNormale),
                  nomVainqueur);
            delete_matrix(matriceNormale);
    } else {

        affichage("Condorcet Schulze", matrix_cols(matriceDuel), 0, nomVainqueur);
    }
    delete_graph(grapheNormale);
    delete_matrix(matriceDuel);
    free(nomVainqueur);
}

void resultatCondorcetPair(char *votingFile, int tag) {
    ptrMatrix matriceDuel, matriceNormale;

    if (tag == VoteCondorcet) {
        matriceNormale = main_lecture_csv(votingFile, 1);

        matriceDuel = initialisation_matrice(matriceNormale);
    } else {
        matriceDuel = main_lecture_csv(votingFile, 2);
    }
    ptrGraph grapheNormale = initialisation_graphe(matriceDuel);
 
    char texteLog[100];
    sprintf(texteLog, "Vous avez choisi pour methode Condorcet Pair");
    ajouter_texte_log(texteLog);
    ajouter_matrice_log(matriceDuel);
    ajouter_graphe_log(grapheNormale);
 
   char *nomVainqueur = main_condorcet_paires(grapheNormale);

    sprintf(texteLog, "vainqueur final pour methode condorcet pair %s  \n", nomVainqueur);
    ajouter_texte_log(texteLog);

    if (tag == VoteCondorcet) {
        affichage("Condorcet Pair", matrix_cols(matriceDuel), matrix_rows(matriceNormale),
                  nomVainqueur);
        delete_matrix(matriceNormale);

    } else {

        affichage("Condorcet Pair", matrix_cols(matriceDuel), 0, nomVainqueur);
    }
    delete_matrix(matriceDuel);
    delete_graph(grapheNormale);
    free(nomVainqueur);
}

/*********************************************DEBUT
 * MAIN********************************************************/

int main(int argc, char **argv) {

    int choice; // ceci permettra de recuperer les choix obligatoires
    char *votingFile = NULL;
    char *logFile = NULL;
    char *votingMethod = NULL;
    int tag = 0; // sera =1 si i ;et =-1 si d
    int indiceMethode = -1;
    int presenceLog = 0;

    /*********************************************Verification
     * arguments********************************************************/

    if ((argc == 2) && (strcmp(argv[1], "-h") == 0)) {
        help();
        exit(0);

    } else if (argc < 3) {
        fprintf(stderr, "Il n'y a pas assez d'arguments \n");
        printf("aide\n");
        help();
        exit(EXIT_FAILURE);
    }

    while ((choice = getopt(argc, argv, "i:d:o:m:j:")) != -1) {
        switch (choice) {
        case 'i':

            if (tag != 0) {
                fprintf(stderr, "Balises incompatibles : on ne peut pas mettre -i et -d pour la "
                                "même commande\n ");
                exit(EXIT_FAILURE);
            }
            votingFile = optarg;
            tag = VoteCondorcet;

            if (votingMethod != NULL) {

                if (!compatibilyArguments(tag, votingMethod)) {
                    fprintf(stderr, "balises incompatibles 3\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

        case 'd':
            if (tag != 0) {
                fprintf(stderr, "Balises incompatibles : on ne peut pas mettre -i -d et -j pour la "
                                "même commande\n ");
                help();
                exit(EXIT_FAILURE);
            }
            votingFile = optarg;
            tag = MatriceDuel;

            if (votingMethod != NULL) {

                if (!compatibilyArguments(tag, votingMethod)) {
                    fprintf(stderr, "balises incompatibles \n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

        case 'j':
            if (tag != 0) {
                fprintf(stderr, "Balises incompatibles : on ne peut pas mettre -i -d et -j pour la "
                                "même commande\n ");
                help();
                exit(EXIT_FAILURE);
            }
            votingFile = optarg;
            tag = jugement_majoritaire;

            if (votingMethod != NULL) {
                if (!compatibilyArguments(tag, votingMethod)) {
                    fprintf(stderr, "balises incompatibles 2\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

        case 'o':
            if (logFile != NULL) {
                fprintf(stderr, " Vous avez déjà choisi un fichier de log  ");
                exit(EXIT_FAILURE);
            }
            logFile = optarg;
            presenceLog = 1;
            break;

        case 'm':
            if (votingMethod != NULL) {
                fprintf(stderr, "On ne peut choisir qu'une seule methode\n");
                exit(EXIT_FAILURE);
            }

            votingMethod = optarg;
            if (!methodExists(votingMethod, &indiceMethode)) {
                fprintf(stderr, "Methode choisie est incorrecte \n");
                exit(EXIT_FAILURE);
            }

            if (!compatibilyArguments(tag, votingMethod)) {
                fprintf(stderr, "balises incompatibles 1\n");
                exit(EXIT_FAILURE);
            }

            break;

        case '?':
            if (optopt == 'i' || optopt == 'd' || optopt == 'm' || optopt == 'j' || optopt == 'o')
                fprintf(stderr, "parametre balise absent\n");
            else
                fprintf(stderr, "balise inconnue \n");
            exit(EXIT_FAILURE);
            break;
        }
    }

    if ((votingFile == NULL) || (votingMethod == NULL)) {
        printf("%d %s \n", tag, votingFile);
        fprintf(stderr, "Vous n'avez pas mis les elements necessaires au programme \n");
        help();
        exit(EXIT_FAILURE);
    }

    if (presenceLog)

        creer_log(logFile);

    /*****************************************************************************************************************/

    switch (indiceMethode) {
    case (UNI1): {
        resultatUninominal1(votingFile);
        break;
    }
    case (UNI2):
        resultatUninominal2(votingFile);
        break;
    case (CM):
        resultatCondorcetMinimax(votingFile, tag);

        break;
    case (CP):
        resultatCondorcetPair(votingFile, tag);
        break;
    case (CS):
        resultatCondorcetSchulze(votingFile, tag);
        break;
    case (JM):
        if (tag == jugement_majoritaire)
            resultatJugement(votingFile, JUGEMENT);
        else
            resultatJugement(votingFile, CONDORCET);
        break;
    case (ALL):
        resultatUninominal1(votingFile);

        resultatUninominal2(votingFile);

        resultatCondorcetMinimax(votingFile, tag);

        resultatJugement(votingFile, CONDORCET);

        resultatCondorcetSchulze(votingFile, tag);

        resultatCondorcetPair(votingFile, tag);

        break;
    default:
        fprintf(stderr, "erreur dans le programme veuillez recommencer \n");
        exit(EXIT_FAILURE);
        break;
    }

    fin_log();

    return 0;
}
