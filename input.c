#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

//Valeur max pour la durée
#define DUREE_MAX 2000000000

char** lecture_carrefours(char* chemin_fichier, unsigned int* nombre_carrefours){
    if(chemin_fichier == NULL)
        return NULL;
    
    //Ouverture du fichier et vérification si tout s'est bien passé
    FILE* fichier = fopen(chemin_fichier, "r"); 
    if(fichier == NULL){
        printf("ERREUR: Ouverture du fichier carrefour impossible\n");
        return NULL;
    }

    *nombre_carrefours = 0;
    char ligne[256]; 
    //Comptage du nombre de lignes
    while(fscanf(fichier, "%s", ligne) == 1){
        (*nombre_carrefours)++;
    }

    // Allocation du tableau
    char** carrefours = malloc(*nombre_carrefours * sizeof(char *));   
    //Si l'allocation echoue, fermeture du fichier
    if( carrefours == NULL ){
        printf("ERREUR: Impossible d'allouer de la mémoire pour les carrefours\n");
        if(fclose(fichier) != 0){
            printf("Erreur lors de la fermeture du fichier: %s", chemin_fichier);
        }
        return NULL;
    }   

    //Retour au début du fichier
    rewind(fichier);

    const char delimiteur[] = ";\r\n";
    unsigned int i = 0;
    //Lecture ligne par ligne du fichier. 256 caractères max par ligne.
    while (fgets(ligne, sizeof(ligne), fichier)){
        //Split la ligne en fonction de la ','
        strtok(ligne, delimiteur);
        char* carrefour = strtok(NULL, delimiteur);
        
        //+1 because we need to consider the \0
        carrefours[i] = malloc(strlen(carrefour) + 1 * sizeof(char));
        strcpy(carrefours[i], carrefour);
        
        //Vérification de l'allocation, en cas d'echec fermeture du fichier et désallocation de la mémoire  
        if(carrefours[i] == NULL){
                if(fclose(fichier) != 0){
                    printf("Erreur lors de la fermeture du fichier: %s", chemin_fichier);
                }
            //Désallocation des strings allouées
            for(unsigned int j=0; j < i; ++j)
                free(carrefours[j]);
            free(carrefours);
        }

        ++i;
    }    

    if(fclose(fichier) != 0){
        printf("Erreur lors de la fermeture du fichier: %s", chemin_fichier);
    }
    return carrefours;
}

unsigned int** lecture_temps(char* chemin_fichier, unsigned int nombre_carrefours){
    if(chemin_fichier == NULL)
        return NULL;
    
    //Ouverture du fichier et vérification si tout s'est bien passé
    FILE* fichier = fopen(chemin_fichier, "r"); 
    if(fichier == NULL){
        printf("ERREUR: Ouverture du fichier carrefour impossible\n");
        return NULL;
    }

    // Allocation du tableau
    unsigned int** temps = malloc(nombre_carrefours * sizeof(int*));   
    //Si l'allocation echoue, fermeture du fichier
    if(temps == NULL){
        printf("ERREUR: Impossible d'allouer de la mémoire pour les temps\n");
            if(fclose(fichier) != 0){
                printf("Erreur lors de la fermeture du fichier: %s", chemin_fichier);
            }
        return NULL;
    }
    
    //Allocation des sous tableaux
    for(unsigned int i=0; i < nombre_carrefours; ++i){
        temps[i] = malloc(nombre_carrefours * sizeof(int));
        //Check si l'allocation a réussi, si pas désallocation de la mémoire et fermeture du fichier
        if(temps[i] == NULL){
            for(unsigned int j=0; j < i; ++j)
                free(temps[j]);
            free(temps);  
                if(fclose(fichier) != 0){
                    printf("Erreur lors de la fermeture du fichier: %s", chemin_fichier);
                }
            return NULL;
        }
    }
    
    //Initialise les valeurs diagonales à 0 et les autres à la DUREE_MAX
    for(unsigned int i=0; i < nombre_carrefours; ++i){
        for(unsigned int j=0; j < nombre_carrefours; ++j){
            if(i == j)
                temps[i][j] = 0;
            else
                temps[i][j] = DUREE_MAX;
        }
    }
        

    const char delimiteur[] = ";\r\n";
    char ligne[256];
    //Lecture ligne par ligne du fichier. 256 caractères max par ligne.
    while (fgets(ligne, sizeof(ligne), fichier)){
        //Split la ligne en fonction de la ','
        unsigned int origine = atoi(strtok(ligne, delimiteur));
        unsigned int duree = atoi(strtok(NULL, delimiteur));
        unsigned int destination = atoi(strtok(NULL, delimiteur));
        
        //Symmetrie
        temps[origine][destination] = duree; 
        temps[destination][origine] = duree;
    }    

    if(fclose(fichier) != 0){
        printf("Erreur lors de la fermeture du fichier: %s", chemin_fichier);
    }
    return temps;
}

void desalloue_carrefours(char** carrefours, unsigned int nombre_carrefours){
    for(unsigned int i = 0; i < nombre_carrefours; ++i){
        free(carrefours[i]);
    }
    free(carrefours);
}

void desalloue_temps(unsigned int** temps, unsigned int nombre_carrefours){
    for(unsigned int i = 0; i < nombre_carrefours; ++i){
        free(temps[i]);
    }
    free(temps);
}
