#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "geometrie.h"

// Structure définissant un obstacle
typedef struct {
    int type;       // 0 pour un trait, 1 pour un cercle
    coord point1;
    coord point2;
    int rayon;   // Utilisé pour les pieds, non pour le plateau
} _Obstacle;
typedef _Obstacle Obstacle;

// Gestion des obstacles
void addAllObstaclesStatiques();
void addObstacleStatique(const int valeurs[], int i);
Obstacle getObstacleStatique(int i);

#define NOMBRE_OBSTACLES_STATIQUES 34

// Gestion des obstacles non statiques (plots, etc, gérés par la stratégie)
int addObstacleNonStatiqueRond(coord centre, int rayon);
void reinit_obstacles_non_statiques();

#define NOMBRE_OBSTACLES_NON_STATIQUES_MAX 4


int conflitPassageObstacle(coord a, coord b, Obstacle obstacle);
int passagePossible(coord a, coord b);
coord pointLePlusProche(coord origine);

#endif // OBSTACLES_H
