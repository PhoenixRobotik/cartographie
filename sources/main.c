#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "point.h"
#include "PointPointerVector.h"
#include "data.h"
#include "astar.h"

// À initialiser

Point* Vstart;
Point* Vgoal;

void print_pointlist(PointList pointlist) {
    int i;
    for (i = 0; i < pointlist.size; ++i){
        Point a = *vector_get(&pointlist, i);
        printf("x : %f, y : %f\n", a.x, a.y);
    }
}




int main(int argc, char const *argv[]) {
    add_all_my_points();
    printf("%f\n", AllThePoints[1].y);

    PointList result = astar(startPointer, ciblePointer);

    printf("fini\n");
    print_pointlist(result);

    return 0;
}
