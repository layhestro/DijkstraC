#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

struct chemin_duree{
    unsigned int duree;
    unsigned int* chemin;
};

/* Renvoie la duree du chemin le plus court entre 2 carrefours ainsi que le 
   chemin sous forme de tableau
   Renvoie NULL si le tableau des temps n'est pas valide 
   ou si le nombre de carrefours est égal à 0. */
struct chemin_duree Dijkstra(unsigned int indice_depart, unsigned int indice_arrivee, unsigned int** temps, unsigned int nombre_carrefours);

#endif
