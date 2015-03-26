#ifndef POINT_H
#define POINT_H

#define ENORMOUS_COST 99999
// Juste une facilité pour identifier le noeud de début et de cible.
typedef enum {
    NOEUD,
    DEBUT,
    CIBLE,
    ERREUR
} PointType;

// Définit complètement un noeud (au détail près de open)
typedef struct  {
    coord coord;          // Les coordonnées du point (en mm)
    PointType type;

    float gScore;       // Le coût pour y aller
    float fScore;       // Le coût estimé pour aller jusqu'à la cible en passant par là

    int visited;        // Booléen : si on l'a déjà visité

    int parentPointRank;// Le rang du point parent dans la liste des points visités ou -1
    //struct _Point* parent;  // Le parent dans le chemin. Est défini quand on le visite.
} Point;

Point newVoidPoint();
Point newPoint(coord position, PointType type);


double distance_heuristique(Point a, Point b);

int equal(Point a, Point b);
int is_better(Point a, Point b);

// i doit être entre 0 et 3, donne un voisin direct du point
Point getVoisin(Point point, int i);


#endif // POINT_H
