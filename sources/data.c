#include <stdio.h>
#include <stdlib.h>
#include "data.h"


static void addObstacleStatique(const int valeurs[], int i){
    Obstacle obstacle;
    coord point;
    obstacle.type   = valeurs[0];
            point.x = valeurs[1];
            point.y = valeurs[2];
    obstacle.point1 = point;
            point.x = valeurs[3];
            point.y = valeurs[4];
    obstacle.point2 = point;

    obstacle.rayon  = 0;

    ObstaclesStatiques[i]=obstacle;
}
void addAllObstaclesStatiques(){
    int i;
    for (i = 0; i < NOMBRE_OBSTACLES_STATIQUES; ++i)
        addObstacleStatique(obstacles[i], i);
}

void addObstacleRond(coord centre, int rayon) {
    Obstacle obstacle;
    obstacle.type   = 1;
    obstacle.point1 = centre;
    obstacle.rayon  = rayon;
    ObstaclesNonStatiques[nombreObstaclesNonStatiques++]=obstacle;
}


static int distancePointSegment(coord segment1, coord segment2, coord point){

}
static int SegmentsIntersectent(coord segment1a, coord segment1b, coord segment2a, coord segment2b){

}

static int conflitPassageObstacle(coord a, coord b, Obstacle obstacle) {
    switch (obstacle.type) {
        case 0:     // Segment
            return SegmentsIntersectent(a, b, obstacle.point1, obstacle.point2);
            break;
        case 1:     // Cercle
            return (distancePointSegment(a, b, obstacle.point1) <= ROBOT_R + obstacle.rayon);
            break;
        default:
            return 1;
            break;
    }
}

int passagePossible(coord a, coord b) {
    int i;
    for (i = 0; i < NOMBRE_OBSTACLES_STATIQUES; ++i)
        if (conflitPassageObstacle(a, b, ObstaclesStatiques[i]))
            return 1;

    return 0;
}
