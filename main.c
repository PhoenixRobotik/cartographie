
#if DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "geometrie.h"
#include "obstacles.h"
#include "point.h"
#include "bestInFirstOut.h"
#include "pointList.h"
#include "pathfinding.h"
#if USE_SDL
#include "simulation/affichage.h"
#endif

// À initialiser

int main() {

    pathfinding_init();

    coord a;
    coord b;
    a.x = 310;
    a.y = 2000-350;
    b.x = 3000-300;
    b.y = 1800;

   pathfinding(a,b);
    PointList cheminFinal = reconstruct_path();

#if DEBUG
    printf("visited, %d\n", visitedPoints().size);
    printf("final, %d\n", cheminFinal.size);

    //PointList visitedPointsV = visitedPoints();
    list_printf(&cheminFinal);
#endif
#if USE_SDL
    while(!sdl_manage_events());
#endif
    list_free(&cheminFinal);

    return 0;
}


void new_xy_absolu(int x, int y) {

}
