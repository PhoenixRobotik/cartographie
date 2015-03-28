#if DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "geometrie.h"
#include "point.h"
#include "pointList.h"

void list_init(PointList *list) {
    // initialize size and capacity
    list->size = 0;
    list->capacity = LIST_MALLOC_SIZE;

    // allocate memory for list->data
    list->dataIds = malloc(sizeof(int) * list->capacity);
    list->data = malloc(sizeof(Point) * list->capacity);
}

int list_append(PointList *list, Point value) {
    // make sure there's room to expand into
    list_extend_if_full(list);

    // append the value and increment list->size
    list->data[list->size++] = value;
    return list->size-1;
}

Point list_get(PointList *list, int index) {
    if (index >= list->size || index < 0) {
        //printf("Index %d out of bounds for list of size %d\n", index, list->size);
        exit(1);
    }
    return list->data[index];
}
int list_find(PointList *list, Point point) {
    int i;
    for (i = 0; i < list->size; ++i) {
        if ( equal(point, list->data[i]) )
            return i;
    }
    return -1;
}

void list_extend_if_full(PointList *list) {
    if (list->size >= list->capacity) {
        // Extend list->capacity and resize the allocated memory accordingly
        list->capacity += LIST_MALLOC_SIZE;
        list->data = realloc(list->data, sizeof(Point) * list->capacity);
    }
}

void list_free(PointList *list) {
    free(list->data);
}

#if DEBUG
void list_printf(PointList *list) {
    int i;
    Point current;
    for (i = 0; i < list->size; ++i) {
        current = list_get(list, i);

        printf("%2d : x%4d - y%4d ; gS %9.5f - fS %9.5f\n", 
            i, current.coord.x, current.coord.y, current.gScore, current.fScore);
    }
}
#endif
