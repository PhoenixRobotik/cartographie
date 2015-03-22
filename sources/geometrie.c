#include <math.h>
#include "geometrie.h"


float distance(coord pointA, coord pointB) {
    int   u=(pointA.x-pointB.x),
            v=(pointA.y-pointB.y);
    return (float)sqrtf(u*u+v*v);
}

float distancePointSegment(coord segment1, coord segment2, coord point){

    return 0;

}
int SegmentsIntersectent(coord segment1a, coord segment1b, coord segment2a, coord segment2b){

    return 0;
}
