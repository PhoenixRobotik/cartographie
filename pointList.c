#include <stdlib.h>
#include "pointList.h"

void list_init(PointList *list) {
    // initialize size and capacity
    list->size = 0;
    list->capacity = LIST_MALLOC_SIZE;

    // allocate memory for list->data
    list->data = malloc(sizeof(Point) * list->capacity);
}

void list_free(PointList *list) {
    list->size = 0;
    list->capacity = 0;
    free(list->data);
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
