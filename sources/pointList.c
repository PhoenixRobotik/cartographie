#include "geometrie.h"
#include "point.h"
#include "pointList.h"

void list_init(PointList *vector) {
    // initialize size and capacity
    vector->size = 0;
    vector->capacity = LIST_MALLOC_SIZE;

    // allocate memory for vector->data
    vector->dataIds = malloc(sizeof(int) * vector->capacity);
    vector->data = malloc(sizeof(Point) * vector->capacity);
}

int list_append(PointList *vector, Point value) {
    // make sure there's room to expand into
    list_extend_if_full(vector);

    // append the value and increment vector->size
    vector->data[vector->size++] = value;
    return vector->size-1;
}

Point list_get(PointList *vector, int index) {
    if (index >= vector->size || index < 0) {
        //printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
        exit(1);
    }
    return vector->data[index];
}

void list_extend_if_full(PointList *vector) {
    if (vector->size >= vector->capacity) {
        // Extend vector->capacity and resize the allocated memory accordingly
        vector->capacity += LIST_MALLOC_SIZE;
        vector->data = realloc(vector->data, sizeof(Point) * vector->capacity);
    }
}

void list_free(PointList *vector) {
    free(vector->data);
}
