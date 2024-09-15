#include <stdlib.h>

#include "dijkstra.h"

//Valeur s'il n'y a pas de carrefour précédent
#define PAS_CARREFOUR_PREC -1
//Valeur max pour la durée
#define DUREE_MAX 2000000000
//Valeur attribuée si l'on doit considérer ou pas le carrefour
enum {NE_PAS_CONSIDERER, A_CONSIDERER};

/* Renvoie l'indice du prochain carrefour à prendre en compte. 
   Renvoie -1 s'il n'y a plus de carrefour à prendre en compte.
   Renvoie -2 si les inputs étaient incorrectes. */
int prochain_carrefour(unsigned int* durees_cumulees, int* carrefours_a_considerer, unsigned int nombre_carrefours);

/* Renvoie le chemin le plus court entre les deux carrefours
   Renvoie NULL si le tableau passé en entrée est NULL*/
unsigned int* chemin(unsigned int indice_depart, unsigned int indice_arrivee, int* carrefours_precedents);

int prochain_carrefour(unsigned int* durees_cumulees, int* carrefours_a_considerer, unsigned int nombre_carrefours){
    if(durees_cumulees == NULL || carrefours_a_considerer == NULL || nombre_carrefours == 0)
        return -2;
        
    int prochain_carrefour = -1;
    unsigned int duree_min = DUREE_MAX;
    for(unsigned int i=0; i < nombre_carrefours; ++i){
        if(carrefours_a_considerer[i] == A_CONSIDERER && durees_cumulees[i] < duree_min)
            prochain_carrefour = i;
    }
    
    return prochain_carrefour;
}

unsigned int* chemin(unsigned int indice_depart, unsigned int indice_arrivee, int* carrefours_precedents){
    if(carrefours_precedents == NULL)
        return NULL;
    
    unsigned int carrefour = indice_arrivee;
    unsigned int longueur_chemin = 0;
    //Calcule la longueur du chemin
    while(carrefour != indice_depart){
        longueur_chemin++;
        carrefour = carrefours_precedents[carrefour];
    }
    longueur_chemin++;
    
    //Vérification de l'input
    unsigned int* chemin = malloc(longueur_chemin * sizeof(int));
    if(chemin == NULL)
        return NULL;
    
    //Calcul du chemin
    carrefour = indice_arrivee;
    unsigned int i = longueur_chemin-1;
    while(carrefour != indice_depart){
        chemin[i] = carrefour;
        carrefour = carrefours_precedents[carrefour];
        --i;
        
    }
    chemin[i] = carrefour;
    
    return chemin;
}

struct chemin_duree Dijkstra(unsigned int indice_depart, unsigned int indice_arrivee, unsigned int** temps, unsigned int nombre_carrefours){

    struct chemin_duree retour = {-1, NULL};

    //Vérification des inputs.
    if(temps == NULL || nombre_carrefours == 0)
        return retour;
    for(unsigned int i=0; i < nombre_carrefours; ++i){
        if(temps[i] == NULL)
            return retour;
    }    
    
    //Initialisation des 3 tableaux
    int* carrefours_precedents = malloc(nombre_carrefours * sizeof(int));
    //Vérification de l'allocation
    if(carrefours_precedents == NULL)
        return retour;
    for(unsigned int i=0; i < nombre_carrefours; ++i){
        carrefours_precedents[i] = PAS_CARREFOUR_PREC;
    }
    
    unsigned int* durees_cumulees = malloc(nombre_carrefours * sizeof(unsigned int)); 
    //Vérification de l'allocation
    if(durees_cumulees == NULL){
        free(carrefours_precedents);
        return retour;
    }
    for(unsigned int i=0; i < nombre_carrefours; ++i){
        durees_cumulees[i] = DUREE_MAX;
    }
    durees_cumulees[indice_depart] = 0;
    
    int* carrefours_a_considerer = malloc(nombre_carrefours * sizeof(int));
    //Vérification de l'allocation
    if(carrefours_precedents == NULL){
        free(durees_cumulees);
        free(carrefours_precedents);
        return retour;
    }
    for(unsigned int i=0; i < nombre_carrefours; ++i){
        carrefours_a_considerer[i] = A_CONSIDERER;
    }
    
    int carrefour;
    //Tant qu'il y a des carrefours à prendre en compte, on boucle
    while((carrefour = prochain_carrefour(durees_cumulees, carrefours_a_considerer, nombre_carrefours)) != -1){
        
        //Mise à jour des durées cumulées et du carrefour précédent
        for(unsigned int i = 0; i < nombre_carrefours; ++i){
            if(durees_cumulees[carrefour] + temps[carrefour][i] < durees_cumulees[i]){
                carrefours_precedents[i] = carrefour;
                durees_cumulees[i] = durees_cumulees[carrefour] + temps[carrefour][i];
            }
        }
        
        //Le carrefour n'est plus à considérer
        carrefours_a_considerer[carrefour] = NE_PAS_CONSIDERER;
    }
    
    retour.duree = durees_cumulees[indice_arrivee];
    retour.chemin = chemin(indice_depart, indice_arrivee, carrefours_precedents);
    
    //Désallocation de la mémoire
    free(carrefours_precedents);
    free(durees_cumulees);
    free(carrefours_a_considerer);
    
    return retour;
}
