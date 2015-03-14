#ifndef DATA_H
#define DATA_H

#define ROBOT_R 190

#define TABLE_H 2000
#define TABLE_W 3000

#define GRID_W 100
#define GRID_H 100
#define GRID_DW 0
#define GRID_DH 0

typedef struct {
    int x;
    int y;
} _coord;
typedef _coord coord;

// Structure définissant un obstacle
typedef struct {
    int type;       // 0 pour un trait, 1 pour un cercle
    coord point1;
    coord point2;
    int rayon;   // Utilisé pour les pieds, non pour le plateau
} _Obstacle;
typedef _Obstacle Obstacle;

void addAllObstaclesStatiques();
void addObstacleRond(coord centre, int rayon);


#define NOMBRE_OBSTACLES_STATIQUES 34
#define NOMBRE_OBSTACLES_NON_STATIQUES_MAX 4

Obstacle ObstaclesStatiques[NOMBRE_OBSTACLES_STATIQUES];
int nombreObstaclesNonStatiques=0;
Obstacle ObstaclesNonStatiques[NOMBRE_OBSTACLES_NON_STATIQUES_MAX]; // Verres + pieds

//Type, 1x/centrex,         1y/centrey,         2x,                 2y
const int obstacles[NOMBRE_OBSTACLES_STATIQUES][5]={
    // Bords de la table
    {0, 0+ROBOT_R,          0+ROBOT_R,      TABLE_H-ROBOT_R,    0+ROBOT_R},
    {0, TABLE_H-ROBOT_R,    0+ROBOT_R,      TABLE_H-ROBOT_R,    TABLE_W-ROBOT_R},
    {0, TABLE_H-ROBOT_R,    TABLE_W-ROBOT_R,0+ROBOT_R,          TABLE_W-ROBOT_R},
    {0, 0+ROBOT_R,          TABLE_W-ROBOT_R,0+ROBOT_R,          0+ROBOT_R},

    // Estrade
    {1, 100,                1200, 0, 0},
    {0, 100+ROBOT_R,        1200,           100+ROBOT_R,        1800+ROBOT_R},
    {1, 100,                1800, 0, 0},

    // Marches (Gros robot)
    {0, TABLE_H,            967-ROBOT_R,    TABLE_H-580,        967-ROBOT_R},
    {1, 580,                967, 0, 0},
    {0, TABLE_H-580-ROBOT_R,967,            TABLE_H-580-ROBOT_R,2033},
    {1, 580,                2033, 0, 0},
    {0, TABLE_H-580,        2033+ROBOT_R,   TABLE_H-580,        2033+ROBOT_R},

    // Zone de départ
    {0, 778-ROBOT_R,        0,              778-ROBOT_R,        400},
    {1, 788,                400, 0, 0},
    {0, 778,                400+ROBOT_R,    800,                400+ROBOT_R},
    {1, 800,                400, 0, 0},
    {0, 800+ROBOT_R,        0,              800+ROBOT_R,        400},

    {0, 800,                70+ROBOT_R,     800,                70+ROBOT_R},

    {0, 1200-ROBOT_R,       0,              1222-ROBOT_R,       400},
    {1, 1200,               400, 0, 0},
    {0, 1200,               400+ROBOT_R,    1222,               400+ROBOT_R},
    {1, 1222,               400, 0, 0},
    {0, 1222+ROBOT_R,       0,              1222+ROBOT_R,       400},

    // Zone de départ ennemie
    {0, 778-ROBOT_R,        TABLE_W,        778-ROBOT_R,        TABLE_W-400},
    {1, 788,                TABLE_W-400, 0, 0},
    {0, 778,                TABLE_W-400-ROBOT_R,800,            TABLE_W-400-ROBOT_R},
    {1, 800,                TABLE_W-400,    0, 0},
    {0, 800+ROBOT_R,        TABLE_W,        800+ROBOT_R,        TABLE_W-400},

    {0, 800,                70+ROBOT_R,     800,                70+ROBOT_R},

    {0, 1200-ROBOT_R,       0,              1222-ROBOT_R,       400},
    {1, 1200,               400, 0, 0},
    {0, 1200,               400+ROBOT_R,    1222,               400+ROBOT_R},
    {1, 1222,               400, 0, 0},
    {0, 1222+ROBOT_R,       0,              1222+ROBOT_R,       400}
};

#endif // DATA_H
