#if DEBUG
#include <stdio.h>
#endif

#include "pathfinding.h"
#if USE_SDL
#include "simulation/affichage.h"
#endif

int x_actuel = 300;
int y_actuel = 1000;


void new_xy_absolu(int x, int y) {
    int on_a_un_chemin = pathfinding(x_actuel, y_actuel, x, y);
    printf("chemin trouvé ? %d\n", on_a_un_chemin);

    if (on_a_un_chemin) {
        int taille = return_length_of_path_found();
        int chemin_trouve[taille][2];
        return_path_found(chemin_trouve);
        int i;
        for (i = 0; i < taille; ++i)
            printf("%d -- %d\n", chemin_trouve[i][0], chemin_trouve[i][1]);

        // Si il y a un chemin de trouvé, on y va !
        x_actuel = x;
        y_actuel = y;        
    }
}


int main() {
    new_xy_absolu(2700,1600);

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

