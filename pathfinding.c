#if DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "geometrie.h"
#include "point.h"
#include "pointList.h"
#include "obstacles.h"
#include "bestInFirstOut.h"
#include "astar.h"

#if USE_SDL
#include "simulation/affichage.h"
#endif
#include "pathfinding.h"

int pathfinding_initialized = 0;
PointList cheminComplet;

void pathfinding_init() {
    addAllObstaclesStatiques();
    #if USE_SDL
    init_sdl_screen();
    dessine_fond();
    int i;
    for (i = 0; i < NOMBRE_OBSTACLES_STATIQUES; ++i) {
        Obstacle obstacle = getObstacleStatique(i);
        if (obstacle.type == 0)
            dessine_obstacle_ligne(obstacle.point1.x, obstacle.point1.y, obstacle.point2.x, obstacle.point2.y);
        else
            dessine_obstacle_rond (obstacle.point1.x, obstacle.point1.y, obstacle.rayon + ROBOT_R);
    }
    #endif
    pathfinding_initialized=1;
}


int pathfinding(int start_x, int start_y, int cible_x, int cible_y) {
    // On nettoie les tableaux, au cas où
    if (!pathfinding_initialized)
        pathfinding_init();


    coord start, cible;
    start.x = start_x;
    start.y = start_y;
    cible.x = cible_x;
    cible.y = cible_y;

    pre_astar();
    if (astar(start, cible)) {
        reconstruct_path(&cheminComplet);
        post_astar();
        return 1;
    }
    post_astar();
    return 0;
}
int return_length_of_path_found() {
    return cheminComplet.size;
}
void return_path_found(int tableau[][2]) {
    int i;
    for (i = 0; i < cheminComplet.size; ++i) {
        Point valeur = cheminComplet.data[i];
        tableau[i][0] = valeur.coord.x;
        tableau[i][1] = valeur.coord.y;
    }
}
