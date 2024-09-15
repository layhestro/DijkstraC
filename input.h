#ifndef INPUT_H_
#define INPUT_H_

/* Lit le fichier dont le nom est passé en paramètre et retourne un tableau 
   contenant les noms de carrefours. Le dernier pointeur est initialisé à NULL
   pour marquer la fin du tableau. Le pointeur sur un int contiendra le nombre 
   de lignes */
char** lecture_carrefours(char* chemin_fichier, unsigned int* nombre_carrefours);

/* Lit le fichier dont le nom est passé en paramètre et retourne un tableau 
   contenant les temps entre les carrefours. Le dernier pointeur est initialisé 
   à NULL pour marquer la fin du tableau. */
unsigned int** lecture_temps(char* chemin_fichier, unsigned int nombre_carrefours);

/* Libère la mémoire utilisée pour les carrefours */
void desalloue_carrefours(char** carrefours, unsigned int nombre_carrefours);

/* Libère la mémoire utilisée pour les temps */
void desalloue_temps(unsigned int** temps, unsigned int nombre_carrefours);

#endif
