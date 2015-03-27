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
#include "debug/affichage.h"

// À initialiser

int main() {

    pathfinding_init();

    coord a;
    coord b;
    a.x = 400;
    a.y = 1700;
    b.x = 2600;
    b.y = 1700;

    pathfinding(a,b);
    PointList cheminFinal = reconstruct_path();

    printf("visited, %d\n", visitedPoints().size);
    printf("final, %d\n", cheminFinal.size);

    //PointList visitedPointsV = visitedPoints(); 
    list_printf(&cheminFinal);

    while(!sdl_manage_events());

    return 0;
}
