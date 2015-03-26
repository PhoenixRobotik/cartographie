#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "geometrie.h"
#include "obstacles.h"
#include "point.h"
#include "pointList.h"
#include "pathfinding.h"

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
/*
    Point a = newVoidPoint();
    printf("element %d\n", list_append(&vectorA,a));
    printf("élément %d\n", list_append(&vectorA,a));
    a.visited=1732;
    printf("élément %d\n", list_append(&vectorA,a));
	int i = list_get(&vectorA, 2).visited;
	printf("élément 2, valeur : %d\n", i);
	printf("taille liste %d\n", vectorA.size);
    printf("taille structure Point %lu\n", sizeof(Point));
*/
    coord a;
    coord b;
    a.x = 200;
    a.y = 100;
    b.x = 200;
    b.y = 20000;

    pathfinding(a,b);
    PointList cheminFinal = reconstruct_path();

    printf("visited, %d\n", visitedPoints().size);
    printf("final, %d\n", cheminFinal.size);

    PointList visitedPointsV = visitedPoints(); 
    list_printf(&cheminFinal);

    return 0;
}
