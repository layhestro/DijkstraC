#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "dijkstra.h"

//100 caractères utiles + '\0'
#define TAILLE_MAX 101

/* Cherche dans le tableau de carrefours le carrefour donné en input et renvoie 
   l'indice correspondant. Renvoie -1 si le carrefour n'existe pas. Renvoie -2 
   si l'un des tableaux est NULL.*/
int cherche_carrefour(char* carrefour, char** carrefours, unsigned int nombre_carrefours);

int cherche_carrefour(char* carrefour, char** carrefours, unsigned int nombre_carrefours){
    //Vérification des inputs
    if(carrefour == NULL || carrefours == NULL)
        return -2;   
    for(unsigned int i=0; i < nombre_carrefours; ++i){
        if(carrefours[i] == NULL)
            return -2;
    }
    
    //Parcours la liste des carrefours et renvoie l'indice du premier carrefour correspondant
    for(unsigned int i=0; i < nombre_carrefours; ++i){
        if(!strncmp(carrefour, carrefours[i], TAILLE_MAX))
            return i;
    }
    
    return -1;
}

int main(){
    char fichier_carrefour[] = "ExempleReel_4_6_Carrefours.csv";
    char fichier_temps[] = "ExempleReel_4_6_Temps.csv";
 
    //Lecture des carrefours
    unsigned int nombre_carrefours = 0;
    char** carrefours = lecture_carrefours(fichier_carrefour, &nombre_carrefours);
    if(carrefours == NULL){
        return -1;
    }
    
    //Lecture des temps
    unsigned int** temps = lecture_temps(fichier_temps, nombre_carrefours);
    if(temps == NULL){
        desalloue_carrefours(carrefours, nombre_carrefours);
        return -1;
    }

    //Affichage des carrefours
    for(unsigned int i = 0; i < nombre_carrefours; ++i){
        printf("%s\n", carrefours[i]);
    }
    
    char carrefour_depart[TAILLE_MAX], carrefour_arrivee[TAILLE_MAX];
    int indice_depart, indice_arrivee;
    //Entrée en input du carrefour d'entrée par l'utilisateur
    printf("Carrefour de depart? ");
    scanf("%s", carrefour_depart);
    while((indice_depart = cherche_carrefour(carrefour_depart, carrefours, nombre_carrefours)) == -1){
        printf("Le carrefour de départ n'existe pas. Entrez-le a nouveau: ");
        scanf("%s", carrefour_depart);
    }
    //Entrée en input du carrefour d'arrivee par l'utilisateur
    printf("Carrefour d'arrivee? ");
    scanf("%s", carrefour_arrivee);
    while((indice_arrivee = cherche_carrefour(carrefour_arrivee, carrefours, nombre_carrefours)) == -1){
        printf("Le carrefour d'arrivee n'existe pas. Entrez-le a nouveau: ");
        scanf("%s", carrefour_arrivee);
    }
    
    //Utilisation de l'algorithme de Dijkstra
    struct chemin_duree resultats = Dijkstra(indice_depart, indice_arrivee, temps, nombre_carrefours);
    if(resultats.chemin == NULL){
        printf("Erreur: l'algo est incapable de calculer la distance la plus courte.\n");
        return -1;
    }
    
    //Output des résultats
    unsigned int i=0;
    for(; resultats.chemin[i] != (unsigned int) indice_arrivee; ++i){
        printf("%s --> ", carrefours[resultats.chemin[i]]); 
    }
    printf("%s avec une durée total de %u minutes pour aller de %s à %s.", carrefours    [resultats.chemin[i]], resultats.duree, carrefours[indice_depart], carrefours[indice_arrivee]);
        
    //Désallocation de la mémoire
    free(resultats.chemin);
    desalloue_temps(temps, nombre_carrefours);
    desalloue_carrefours(carrefours, nombre_carrefours);
    
    return 0;
}
