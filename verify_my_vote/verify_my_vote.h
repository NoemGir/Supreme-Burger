/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author MARTIN Benoit
 *  \date 27/10/2023
 *  \file Interface de l'accès et la vérification des votes
 **/
/*-----------------------------------------------------------------*/

#ifndef verify_my_vote_h
#define verify_my_vote_h


#include "sha256.h"
#include "sha256_utils.h"
#include "../src/utils_sd/utils_sd.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constant definition
#define STRLONG 100
/// \def define a maximum length for user input. 

//verify my vote takes for argument the csv file containing the vote to verify 
//Usage: ./verify_my_vote <fichier de vote>

// Function declarations
/*
 *	\fn main 
 *	\brief takes for argument the csv file containing the vote to verify 
 *	\param[in] argc argv[]
 *	\return void
 */
int main(int argc, const char * argv[]);
/*
 *	\fn getInput 
 *	\brief get the user input (key ,first name and last name)
 *	\param[in] input message 
 *	\return void  
 */
 
 void capitalizeFirstLetter(char *str);
 
 void capitalizeSTR(char *str);
 
void getInput(char *input, const char *message);
/*
 *	\fn calculateHash 
 *	\brief calculate the SHA256 hash of a const char*
 *	\param[in] concatenate resultatHash
 *	\return void  
 */
void calculateHash(const char *concatene, char *resultatHash);
/*
 *	\fn searchVote 
 *	\brief search for param[in] resultatHash if it is in a file 
 *	\param[in] resultatHash filename 
 *	\return void  
 */
void searchVote(const char *resultatHash, const char *filename);
/*
 *	\fn concatener 
 *	\brief take user input and concatenate it in a char*
 *	\param[in] clef nom prenom concatenate
 *	\return void  
 */
void concatener(char *clef, char *nom, char *prenom, char *concatene);

#endif /* verify_my_vote_h */