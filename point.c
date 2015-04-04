#include "point.h"

Point newVoidPoint(){
    Point point;
    point.type = NOEUD;

    point.gScore = 0;
    point.fScore = 0;

    point.parentPointRank = -1;
    return point;
}

Point newPoint(coord position, PointType type){
    Point point = newVoidPoint();
    point.coord = position;
    point.type  = type;
    return point;
}

Point errorPoint() {
    Point point;
    point.type = ERREUR;
    return point;
}

int equal(Point a, Point b) {
    return (   a.coord.x == b.coord.x
            && a.coord.y == b.coord.y );

}

int is_better(Point a, Point b) {
    return (a.fScore < b.fScore);
}

Point getVoisin(Point point, int i) {
    Point voisin = newVoidPoint();
    if (i<0 || i>3) {
        voisin.type = ERREUR;
        return voisin;
    }

    voisin.coord = point.coord;

    int coordonnees_voisins_si_point_sur_la_grille[4][2] =
            {{-1, 0},
             { 0,-1},
             {+1, 0},
             { 0,+1}};

    int coordonnees_voisins_si_point_decale[4][2] = 
            {{ 0, 0},
             { 0,+1},
             {+1, 0},
             {+1,+1}};

    if (est_sur_la_grille(point.coord)) {
        voisin.coord.x += GRID_X*coordonnees_voisins_si_point_sur_la_grille[i][0];
        voisin.coord.y += GRID_Y*coordonnees_voisins_si_point_sur_la_grille[i][1];

    } else {
        voisin.coord.x -= ((point.coord.x - GRID_DX) % GRID_X) + GRID_DX;
        voisin.coord.y -= ((point.coord.y - GRID_DY) % GRID_Y) + GRID_DY;
        voisin.coord.x += GRID_X*coordonnees_voisins_si_point_decale[i][0];
        voisin.coord.y += GRID_Y*coordonnees_voisins_si_point_decale[i][1];
    }

    return voisin;
}
