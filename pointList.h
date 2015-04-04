#ifndef POINTLIST_H
#define POINTLIST_H


//  Cette "classe" nous permet de gérer une liste de points.
//  Cette liste doit grandir mais on ne retire JAMAIS d'éléments.
//  Ceci nous permet d'enregistrer tous les points visités, et le chemin final,
//  sans initialiser un tableau d'une taille délirante.


// How many we allocate at once
#define LIST_MALLOC_SIZE 5
#define MAX_LIST_SIZE 320

// Define a list type
typedef struct {
    int size;       // slots used so far
    int capacity;   // total available slots
    Point* data;    // array of integers we're storing
} PointList;

//  Init, free
int list_init(PointList *list);
int list_free(PointList *list);

// Getters and setters
// Retourne l'index du nouvel élément ou -1 si erreur fatale.
int list_append(PointList *list, Point value);

Point list_get (PointList *list, int index);
int list_find  (PointList *list, Point point);

#if DEBUG
// Pour le debug
int list_printf(PointList *list);
#endif

#endif // POINTLIST_H
