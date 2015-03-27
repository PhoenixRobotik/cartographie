#include <math.h>
#include "geometrie.h"


float distance(coord pointA, coord pointB) {
    int u=(pointA.x-pointB.x),
        v=(pointA.y-pointB.y);
    return (float)sqrtf((float)u*u+v*v);
}

float distance_heuristique(coord a, coord b) {
    // TODO ajouter un coeff si nécessaire
    return 1.414*distance(a, b);
}

int collisionSegmentSegment(coord A, coord B, coord I, coord P){
    coord D,E;
    D.x = B.x - A.x;
    D.y = B.y - A.y;
    E.x = P.x - I.x;
    E.y = P.y - I.y;
    double denom = D.x*E.y - D.y*E.x;
    if (denom==0)
        return 0;   // Segment et droite parallèles
    float t = - (A.x*E.y-I.x*E.y-E.x*A.y+E.x*I.y) / denom;
    if (t<0 || t>1)
        return 0;
    float u = - (-D.x*A.y+D.x*I.y+D.y*A.x-D.y*I.x) / denom;
    if (u<0 || u>1)
        return 0;
    return 1;
}

int distanceCercleSegment() {
    return 10000;
}



float distancePointSegment(coord segment1, coord segment2, coord point){

    return 0;

}
