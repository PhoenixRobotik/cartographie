#ifndef VECTOR_H
#define VECTOR_H

/*
    Cette "classe" nous permet de gérer une liste de pointeurs sur des points.
    Ceci nous permet de gérer la liste de tous les points et le chemin.
*/


// How many we allocate at once
#define VECTOR_MALLOC_SIZE 5

// Define a vector type
typedef struct {
    int size;       // slots used so far
    int capacity;   // total available slots
    Point **data;   // array of integers we're storing
} Vector;
typedef Vector PointList;

//      Init, free and "make bigger if full"
void vector_init(Vector *vector);
void vector_free(Vector *vector);
void vector_extend_if_full(Vector *vector);

//      Getters and setters
// Retourne l'index du nouvel élément
int vector_append(Vector *vector, Point* value);

Point* vector_get(Vector *vector, int index);

#endif // VECTOR_H
