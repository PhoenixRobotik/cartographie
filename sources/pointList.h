#ifndef POINTLIST_H
#define POINTLIST_H

/*
    Cette "classe" nous permet de gérer une liste de points.
    Cette liste doit grandir mais on ne retire JAMAIS d'éléments.
    Ceci nous permet d'enregistrer tous les points visités, et le chemin final,
    sans initialiser un tableau d'une taille délirante.
*/


// How many we allocate at once
#define LIST_MALLOC_SIZE 5

// Define a list type
typedef struct {
    int size;       // slots used so far
    int capacity;   // total available slots
    int* dataIds;   // identifiants basés sur les coordonnées, utilisé pour trouver un point
    Point* data;    // array of integers we're storing
} PointList;

//      Init, free and "make bigger if full"
void list_init(PointList *list);
void list_free(PointList *list);
void list_extend_if_full(PointList *list);

//      Getters and setters
// Retourne l'index du nouvel élément
int list_append(PointList *list, Point value);

Point list_get(PointList *list, int index);

int list_find(PointList *list, Point point);

void list_printf(PointList *list);

#endif // POINTLIST_H
