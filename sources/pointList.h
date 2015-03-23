#ifndef POINTLIST_H
#define POINTLIST_H

/*
    Cette "classe" nous permet de gérer une liste de points.
    Ceci nous permet d'enregistrer la liste de tous les points ouverts ou enregistrés,
    sans initialiser un tableau d'une taille délirante.
*/


// How many we allocate at once
#define LIST_MALLOC_SIZE 5

// Define a vector type
typedef struct {
    int size;       // slots used so far
    int capacity;   // total available slots
    int* dataIds;   // identifiants basés sur les coordonnées, utilisé pour trouver un point
    Point* data;    // array of integers we're storing
} PointList;

//      Init, free and "make bigger if full"
void list_init(PointList *vector);
void list_free(PointList *vector);
void list_extend_if_full(PointList *vector);

//      Getters and setters
// Retourne l'index du nouvel élément
int list_append(PointList *vector, Point value);

Point list_get(PointList *vector, int index);

#endif // POINTLIST_H
