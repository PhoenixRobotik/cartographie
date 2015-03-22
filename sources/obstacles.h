#ifndef OBSTACLES_H
#define OBSTACLES_H

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

#define NOMBRE_OBSTACLES_STATIQUES 34

// Gestion des obstacles non statiques (plots, etc, gérés par la stratégie)
void addObstacleNonStatiqueRond(coord centre, int rayon);

#define NOMBRE_OBSTACLES_NON_STATIQUES_MAX 4



int passagePossible(coord a, coord b);
int conflitPassageObstacle(coord a, coord b, Obstacle obstacle);


#endif // OBSTACLES_H
