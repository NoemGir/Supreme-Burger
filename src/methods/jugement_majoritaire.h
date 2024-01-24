/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author GIREAUD Noémie
 *  \date 22/10/23
 *  \file jugement_majoritaire.h
 *  \brief Interface des calculs du resultat du vote grace à la methode de Jugement Majoritaire
 **/
/*-----------------------------------------------------------------*/

#ifndef JUGEMENT_H
#define JUGEMENT_H

#include "../datatypes/matrix.h"

#define JUGEMENT 0
#define CONDORCET 1

/**
 *  \brief calcul le vainqueur par la methode du jugement majoritaire
 *
 *  \param[in] matrice_initial La matrice reliant les votes de chaque votants aux candidats
 *  \param[in] scrutin scrutin = JUGEMENT si on prend le fichier jugement majoritaire et scrutin = CONDORCET si on prend le fichier condorcet
 *
 *  \return  retourne le nom du candidat qui a gagné.
 */
char * main_jugement_majoritaire(Matrix * matrice_initiale, int scrutin);


#endif // JUGEMENT_H
