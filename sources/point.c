#include "geometrie.h"
#include "point.h"

Point newVoidPoint(){
    Point point;
    point.type = NOEUD;

    point.gScore = ENORMOUS_COST;
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



double distance_heuristique(Point a, Point b) {
	// TODO ajouter un coeff si nécessaire
    return 1.2*distance(a.coord, b.coord);
}

int equal(Point a, Point b) {
    return (   a.coord.x == b.coord.x
            && a.coord.y == b.coord.y );

}

int is_better(Point a, Point b) {
    return (a.fScore < b.fScore);
}
