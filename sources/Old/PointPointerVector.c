#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "PointPointerVector.h"

void vector_init(Vector *vector) {
    // initialize size and capacity
    vector->size = 0;
    vector->capacity = VECTOR_MALLOC_SIZE;

    // allocate memory for vector->data
    vector->data = malloc(sizeof(Point) * vector->capacity);
}

int vector_append(Vector *vector, Point* value) {
    // make sure there's room to expand into
    vector_extend_if_full(vector);

    // append the value and increment vector->size
    vector->data[vector->size++] = value;
    return vector->size-1;
}

Point* vector_get(Vector *vector, int index) {
    if (index >= vector->size || index < 0) {
        printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
        exit(1);
    }
    return vector->data[index];
}

void vector_extend_if_full(Vector *vector) {
    if (vector->size >= vector->capacity) {
        // Extend vector->capacity and resize the allocated memory accordingly
        vector->capacity += VECTOR_MALLOC_SIZE;
        vector->data = realloc(vector->data, sizeof(Point) * vector->capacity);
    }
}

void vector_free(Vector *vector) {
    free(vector->data);
}
