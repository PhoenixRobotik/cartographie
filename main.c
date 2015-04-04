#if DEBUG
#include <stdio.h>
#endif

#include "pathfinding.h"
#if USE_SDL
#include "simulation/affichage.h"
#endif

int x_actuel = 300;
int y_actuel = 1000;

int main() {

   // pathfinding(330, 1800,
   //            2600, 1003);

/*    PointList cheminFinal = reconstruct_path();

#if DEBUG
    printf("visited, %d\n", visitedPoints().size);
    printf("final, %d\n", cheminFinal.size);

    //PointList visitedPointsV = visitedPoints();
    list_printf(&cheminFinal);
#endif*/
#if USE_SDL
    while(!sdl_manage_events());
#endif

    return 0;
}


void new_xy_absolu(int x, int y) {
    int on_a_un_chemin = pathfinding(x_actuel, y_actuel, x, y);
    printf("chemin trouvé ? %d\n", on_a_un_chemin);

    if (on_a_un_chemin) {
        x_actuel = x;
        y_actuel = y;        
    }
}
