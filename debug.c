#include "debug.h"

#if DEBUG
// Pour le debug
int list_printf(PointList *list) {
    int i;
    Point current;
    for (i = 0; i < list->size; ++i) {
        current = list_get(list, i);

        debug("%2d : x%4d - y%4d ; gS %9.5f - fS %9.5f\n",
            i, current.coord.x, current.coord.y, current.gScore, current.fScore);
    }
    return 0;
}
#endif