/*-----------------------------------------------------------------*/
/** Advanced Project
 *  \author MARTIN Benoit
 *  \date 20/10/2023
 *  \file Implémentation de l'accès et la vérification des votes
 **/
/*-----------------------------------------------------------------*/


#include "sha256.h"
#include "sha256_utils.h"
#include "../src/utils_sd/utils_sd.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "verify_my_vote.h"
#define STRLONG 100
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
int main(int argc, const char * argv[]) {
	printf("----------------------------------------------------------------------------------------\n");
  if (argc < 2) {
    printf("Usage: ./%s <fichier de vote>\n", argv[0]);
    return 1;
  }

  const char *filename = argv[1];
  char resultatHash[SHA256_BLOCK_SIZE * 2 + 1];
  char concatene[STRLONG * 3 + 1];
  char clef[STRLONG];
  char nom[STRLONG];
  char prenom[STRLONG];

  // Get user input
  getInput(clef, "  > Veuillez saisir votre clef : ");
  getInput(nom, "  > Veuillez saisir votre nom : ");
  capitalizeSTR(nom);
  //printf("%s\n",nom);
  getInput(prenom, "  > Veuillez saisir votre prénom : ");
  capitalizeFirstLetter(prenom);
  //printf("%s\n",prenom);
  // Concatenate user input
  concatener(clef, nom, prenom, concatene);
  // Calculate hash
  calculateHash(concatene, resultatHash);
  printf("  Le hash obtenu est : %s\n",resultatHash);
  // Search for vote
  searchVote(resultatHash, filename);
	return 0;
}

void capitalizeFirstLetter(char *str) {
    if (str != NULL && *str != '\0') {
        *str = toupper((unsigned char)*str);
		str++;
    }
	while(*str){
		if(*str == ' '){
			str++;
			*str = toupper((unsigned char)*str);
			str++;
		}
		*str = tolower((unsigned char)*str);
		str++;
	}
}

void capitalizeSTR(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

void getInput(char *input, const char *message) {
  printf("%s", message);
  if (fgets(input, STRLONG, stdin) == NULL)
	  fprintf(stderr,"Erreur lors de fgets dans getInputs\n");
  input[strcspn(input, "\n")] = 0;
}

/*void getInputNom(char *input, const char *message) {
  printf("%s", message);
  if (fgets(input, STRLONG, stdin) == NULL)
	  fprintf(stderr,"Erreur lors de fgets dans getInputs\n");
  input[strcspn(input, "\n")] = 0;
  for(int i = 0; i < strlen(input); i++){
	  if (atoi(&input[i]) <=172 && atoi(&input[i]) >= 141)
		  input[0] = atoi(&input[0]) - 76;
  }
  printf("miaou : %s\n",input);
}

void getInputPrenom(char *input, const char *message) {
  printf("%s", message);
  if (fgets(input, STRLONG, stdin) == NULL)
	  fprintf(stderr,"Erreur lors de fgets dans getInputs\n");
  input[strcspn(input, "\n")] = 0;
	 if (!(atoi(&input[0]) <=172 && atoi(&input[0]) >= 141))
		 input[0] = atoi(&input[0]) - 76;
	printf("woof : %s\n",input);
}*/

void concatener(char *clef, char *nom, char *prenom, char *concatene) {
  strcpy(concatene, nom);
  strcat(concatene, " ");
  strcat(concatene, prenom);
  strcat(concatene, clef);
}

void calculateHash(const char *concatene, char *resultatHash) {
  sha256ofString((BYTE *)concatene, resultatHash);
  //printf("Hash : %s\n", resultatHash);
}

void searchVote(const char *resultatHash, const char *filename) {
  char buffer[256];
  bool trouve = false;

  FILE *fichier = fopen(filename, "r");
  if (fichier == NULL) {
    printf("Erreur d'ouverture du fichier %s\n", filename);
    return;
  }
  // search for the line containing the vote
  while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
    if (strstr(buffer, resultatHash) != NULL) {
      fclose(fichier);
      trouve = true;
      break; // Exit the loop once the vote is found
    }
  }

  // if vote was found extract it from the csv line
  if (trouve) {
    char *res = strchr(buffer, ',');
    for (int i = 0; i < 3; i++) {
      res = strchr(res + 1, ',');
      if (res == NULL) {
        printf("erreur extraction vote\n");
        return;
      }
    }

    res++;
	res[strlen(res)-1] = '\0';
   printf(" "ANSI_COLOR_GREEN " le vote a été trouvé : %s \n", res);
  } else {
    printf(" "ANSI_COLOR_RED " le vote n'a pas été trouvé \n");
  }
  printf(ANSI_COLOR_RESET "----------------------------------------------------------------------------------------\n");
}