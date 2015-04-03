#include "point.h"

Point newVoidPoint(){
    Point point;
    point.type = NOEUD;

    point.gScore = 0;
    point.fScore = 0;

    point.visited = 0;

    point.parentPointRank = -1;
    return point;
}

Point newPoint(coord position, PointType type){
    Point point = newVoidPoint();
    point.coord = position;
    point.type  = type;
    return point;
}

int equal(Point a, Point b) {
    return (   a.coord.x == b.coord.x
            && a.coord.y == b.coord.y );

}

int is_better(Point a, Point b) {
    return (a.fScore < b.fScore);
}

int est_sur_la_grille(Point point) {
    return (point.coord.x % GRID_X == GRID_DX % GRID_X &&
            point.coord.y % GRID_Y == GRID_DY % GRID_Y);
}

Point getVoisin(Point point, int i) {
    int coordonnees_voisins[4][2] =
            {{-1, 0},
             { 0,-1},
             {+1, 0},
             { 0,+1}};

    int coordonnees_voisins_trim[4][2] = 
            {{ 0, 0},
             { 0,+1},
             {+1, 0},
             {+1,+1}};

    Point voisin = newVoidPoint();

    if (est_sur_la_grille(point)) {
       // coordonnees_utilisees = coordonnees_voisins;

        voisin.coord = point.coord;
    } else {
       // coordonnees_utilisees = coordonnees_voisins_trim;

        voisin.coord.x = point.coord.x - ((point.coord.x - GRID_DX) % GRID_X) + GRID_DX;
        voisin.coord.y = point.coord.y - ((point.coord.y - GRID_DY) % GRID_Y) + GRID_DY;
    }

    if (i<0 || i>3)
        voisin.type = ERREUR;
    else {
        voisin.coord.x += GRID_X*coordonnees_voisins[i][0];
        voisin.coord.y += GRID_Y*coordonnees_voisins[i][1];
    }

    return voisin;
}
