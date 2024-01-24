/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author MARTIN Benoit
 *  \date 5/10/2023
 *  \file lecture_csv.h
 *  \brief Interface de la lecture des fichiers csv
 */
/*-----------------------------------------------------------------*/
#ifndef lecture_csv
#define lecture_csv

#include "../datatypes/matrix.h"

/**
 *
 *	\brief renvoie la matrice de vote du fichier csv passé en paramètre
 *	\param[in] nomFichier Le nom du fichier à importer
 *  \param[in] choix la catégorie de fichier : 1 == vote  et 2 == matrice de duelle
 *	\return ptrMatrix  
 */

ptrMatrix main_lecture_csv(char *nomFichier, int choix);

#endif /* lecture_csv */