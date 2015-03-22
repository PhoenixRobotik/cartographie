#ifndef POINT_H
#define POINT_H

#define MAX_VOISINS 10

#define ENORMOUS_COST 9999999

typedef enum { false, true } bool;

// Juste une facilité pour identifier le noeud de début et de cible.
typedef enum {
    DEBUT,
    NOEUD,
    CIBLE
} PointType;


// Définit complètement un noeud (au détail près de open)
struct _Point {
    double x;
    double y;
    PointType type;

    int gScore;     // Le coût pour y aller
    int fScore;     // Le coût estimé pour aller jusqu'à la cible en passant par là

    bool is_open;    // Booléen : si il est à visiter
    bool visited;    // Booléen : si on l'a déjà visité

    struct _Point* parent;  // Le parent dans le chemin. Est défini quand on le visite.

    int neighborCount;
    struct _Point* voisins[MAX_VOISINS]; // Les voisins du point. Définis au début, non modifiés par la suite.
};

typedef struct _Point Point;

Point newPoint(double x, double y, PointType type);

void addLink(Point* a, Point* b);

double distance_directe(Point a, Point b);
double distance_heuristique(Point a, Point b);


bool are_in_view(Point a, Point b);

bool is_better(Point a, Point b);

#endif // POINT_H
