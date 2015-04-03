
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

int x_actuel = 300;
int y_actuel = 1000;

int main() {

    pathfinding_init();
/*
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
*/
    while(!sdl_manage_events());
    printf("auie\n");
    return 0;
}


void new_xy_absolu(int x, int y) {
    printf("%d, %d\n", x, y);
    //pathfinding_init();
    int on_a_un_chemin = pathfinding_start(x_actuel, y_actuel, x, y);

    if (on_a_un_chemin) {
        x_actuel = x;
        y_actuel = y;        
    }
    pathfinding_reinit();
}
