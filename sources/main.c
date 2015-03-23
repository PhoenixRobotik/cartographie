#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "geometrie.h"
#include "obstacles.h"
#include "point.h"
#include "pointList.h"

// À initialiser


int main() {/*
    coord a,b;
    a.x=0;
    a.y=1;
    b.x=1;
    b.y=1;
*/

    PointList vectorA;
    list_init(&vectorA);

    Point a = newVoidPoint();
    printf("%d\n", list_append(&vectorA,a));
    printf("%d\n", list_append(&vectorA,a));
    a.visited=1732;
    printf("%d\n", list_append(&vectorA,a));
	int i = list_get(&vectorA, 2).visited;
	printf("%d\n", i);
	printf("%d\n", vectorA.size);
    printf("%lu\n", sizeof(Point));

    return 0;
}
