#ifndef POINT_H
#define POINT_H

#define ENORMOUS_COST 99999
// Juste une facilité pour identifier le noeud de début et de cible.
typedef enum {
    DEBUT,
    NOEUD,
    CIBLE
} PointType;

// Définit complètement un noeud (au détail près de open)
struct _Point {
    coord pos;          // Les coordonnées du point (en mm)
    PointType type;

    float gScore;       // Le coût pour y aller
    float fScore;       // Le coût estimé pour aller jusqu'à la cible en passant par là

    int visited;        // Booléen : si on l'a déjà visité

    int parentPointRank;// Le rang du point parent dans la liste des points visités ou -1
    //struct _Point* parent;  // Le parent dans le chemin. Est défini quand on le visite.
};
typedef struct _Point Point;

Point newVoidPoint();
Point newPoint(coord position, PointType type);


double distance_heuristique(Point a, Point b);

int is_better(Point a, Point b);


#endif // POINT_H
