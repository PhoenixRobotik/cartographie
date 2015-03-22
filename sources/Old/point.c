#include <math.h>

#include "point.h"


Point newPoint(double x, double y, PointType type){
    Point point;
    point.x = x;
    point.y = y;
    point.type = type;

    point.gScore = ENORMOUS_COST;
    point.fScore = 0;

    point.is_open = false;
    point.visited = false;

    point.parent = 0;

    point.neighborCount = 0;
    return point;
}

void addLink(Point* a, Point* b) {
    a->voisins[a->neighborCount] = b;
    a->neighborCount++;
}



double distance_directe(Point a, Point b) {
    double deltaX = a.x - b.x;
    double deltaY = a.y - b.y;
    return sqrt(deltaX*deltaX + deltaY * deltaY);
}

double distance_heuristique(Point a, Point b) {
    return distance_directe(a, b);
}

bool are_in_view(Point a, Point b) {
    return true;
}

bool is_better(Point a, Point b) {
    if (a.fScore < b.fScore)
        return true;
    return false;
}
