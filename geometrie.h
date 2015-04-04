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
} coord;

int est_sur_la_grille(coord coord);

float distance(coord pointA, coord pointB);
float distance_heuristique(coord A, coord B);

int collisionSegmentSegment(coord A, coord B, coord I, coord P);

int collisionSegmentCercle(coord A, coord B, coord C, float rayon);

#endif // GEOMETRIE_H
