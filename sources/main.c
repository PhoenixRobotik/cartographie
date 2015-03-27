#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "geometrie.h"
#include "obstacles.h"
#include "point.h"
#include "bestInFirstOut.h"
#include "pointList.h"
#include "pathfinding.h"

// À initialiser

void auie() {

}

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
    pathfinding_init();


    coord a;
    coord b;
    a.x = 257;
    a.y = 230;
    b.x = 600;
    b.y = 601;

/*
    Point A = newPoint(pointLePlusProche(a), NOEUD);
    //add_to_open(A);

    if (is_open(A)) {
        printf("auieauie\n");
    }
    else
        printf("non\n");
    {
    }
    is_open(A);
*/
    

    pathfinding(a,b);
    auie();
    PointList cheminFinal = reconstruct_path();

    printf("visited, %d\n", visitedPoints().size);
    printf("final, %d\n", cheminFinal.size);

    //PointList visitedPointsV = visitedPoints(); 
    list_printf(&cheminFinal);

    return 0;
}
