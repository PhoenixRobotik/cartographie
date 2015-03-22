#ifndef GEOMETRIE_H
#define GEOMETRIE_H

#define ROBOT_R 190

#define TABLE_H 2000
#define TABLE_W 3000

#define GRID_X 100
#define GRID_Y 100
#define GRID_DX 0
#define GRID_DY 0

// Valeurs booléennes : vrai=1, faux=0

typedef struct {
    int x;
    int y;
} _coord;
typedef _coord coord;

float distance(coord pointA, coord pointB);

float distancePointSegment(coord segment1, coord segment2, coord point);
int SegmentsIntersectent(coord segment1a, coord segment1b, coord segment2a, coord segment2b);


#endif // GEOMETRIE_H
