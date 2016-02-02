#include "debug.h"

#include "cartographie.h"

int x_actuel = 300;
int y_actuel = 1000;
void new_xy_absolu(int x, int y);

float float_get_x_actuel(){
    return x_actuel;
}
float float_get_y_actuel(){
    return y_actuel;

}
int get_theta_actuel(){
    return 0;
}

void set_trajectoire_xy_absolu(int x, int y) {
    new_xy_absolu(x, y);
}
void new_xy_absolu(int x, int y) {

    // On appelle le pathfinding et on regarde si il y a un chemin
    int longueur_chemin_trouve = pathfinding(x_actuel, y_actuel, x, y);

    if (longueur_chemin_trouve > 0) {
        debug(1, "Chemin trouvé de %d points\n", longueur_chemin_trouve);
        // On récupère le chemin lui-même
        int chemin_trouve[longueur_chemin_trouve][2];
        return_path_found(chemin_trouve);

        // On l'affiche
        int i;
        for (i = 0; i < longueur_chemin_trouve; ++i)
            debug(1, "%d -- %d\n", chemin_trouve[i][0], chemin_trouve[i][1]);

        // Et on l'exécute !
        x_actuel = x;
        y_actuel = y;
    } else {
        debug(1, "Pas de chemin trouvé\n");
    }
}


int main() {
    pathfinding_init();

    nouvel_obstacle_rond(1500, 1200, 200);
    new_xy_absolu(2700,1600);
    new_xy_absolu(300,1600);
    new_xy_absolu(2700,1600);
    //pause();

    return 0;
}

