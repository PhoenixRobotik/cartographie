#if DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "geometrie.h"
#include "point.h"
#include "pointList.h"

int list_init(PointList *list) {
    // initialize size and capacity
    list->size = 0;
    list->capacity = LIST_MALLOC_SIZE;

    // allocate memory for list->data
    list->data = malloc(sizeof(Point) * list->capacity);
    return (list->data != NULL)-1;
}

int list_free(PointList *list) {
    list->size = 0;
    list->capacity = 0;
    free(list->data);
    return (list->data == NULL)-1;
}

int list_append(PointList *list, Point value) {
    // make sure there's room to expand into
    if (list->size == list->capacity) {
        list->capacity += LIST_MALLOC_SIZE;

        // Here, there is a fatal error to manage.
        if (list->capacity >= MAX_LIST_SIZE)
            return -1;
        list->data = realloc(list->data, sizeof(Point) * list->capacity);
    }

    // append the value and increment list->size
    list->data[list->size] = value;
    return list->size++;
}

Point list_get(PointList *list, int index) {
    if (index >= list->size || index < 0)
        return errorPoint();
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



#if DEBUG
int list_printf(PointList *list) {
    int i;
    Point current;
    for (i = 0; i < list->size; ++i) {
        current = list_get(list, i);

        printf("%2d : x%4d - y%4d ; gS %9.5f - fS %9.5f\n",
            i, current.coord.x, current.coord.y, current.gScore, current.fScore);
    }
    return 0;
}
#endif
