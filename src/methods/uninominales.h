/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author Ait-Messaoud Tinhinane
 *  \date 27/10/23
 *  \file uninominales.h
 *  \brief Interface des calculs du resultat du vote grace à la methode Uninominale
 **/
/*-----------------------------------------------------------------*/
#include "../datatypes/matrix.h"
#include "../utils_sd/utils_sd.h"
#include <stdio.h>

#ifndef UNINOMINAL_H
#define UNINOMINAL_H


/**
 * \brief ceci est la fonction principale d'appel si on veut une methode uninominale à un tour
 *
 * \param matrice_initialise : matrice initialisee a partir du fichier csv regroupant pour chaque
 * ligne ,representant un votant, le classement de 1-10 pour chaque candidat (represente au niveau
 * des colonnes)
 * \return vainqueur : structure du vainqueur regroupant nom du vainqueur et son score
 */
vainqueur main_uninominale_1(Matrix *matrice_initialise);

/**
 * \brief ceci est la fonction principale d'appel si on veut une methode uninominale à deux tours
 *
 * \param matrice_initialise : matrice initialisee a partir du fichier csv regroupant pour chaque
 * ligne ,representant un votant, le classement de 1-10 pour chaque candidat (represente au niveau
 * des colonnes)
 * \return vainqueur : structure du vainqueur regroupant nom du vainqueur et son score
 */
vainqueur main_uninominale_2(Matrix *matrice_initialise);

#endif //UNINOMINAL_H
