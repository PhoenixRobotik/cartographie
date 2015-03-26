#include "geometrie.h"
#include "point.h"
#include "pointList.h"
#include "obstacles.h"
#include "bestInFirstOut.h"
#include "pathfinding.h"

PointList VisitedPoints;
Point ciblePoint;

void pathfinding_init() {
    list_init(&VisitedPoints);
}


void pathfinding(coord start, coord cible) {
    // C'est là qu'on va gérer l'ajout d'ennemis.


    // Tout d'abord on regarde si on peut aller tranquillement de start à cible :

    if (passagePossible(start, cible) == 1) {
        // OUI !
        Point newStart = newPoint(start, DEBUT);
        ciblePoint = newPoint(cible, CIBLE);
        ciblePoint.parentPointRank = list_append(&VisitedPoints, newStart);
        return;
    }



    // On "recalibre" les points en fonction de la grille.
    Point newStart = newPoint(pointLePlusProche(start), DEBUT);
    Point newCible = newPoint(pointLePlusProche(cible), CIBLE);


    newStart.gScore = distance(start, newStart.coord);
    newStart.fScore = distance(start, cible);

    add_to_open(newStart);
/*
    //printf("commence la boucle\n");

    while(open_size()!=0) {
        Point* current = pop_best_open_point();
        printf("%d\n", current->neighborCount);

        // On a fini, on reconstruit le chemin grâce au parent de chaque point.
        if (current->type == CIBLE)
            return reconstruct_path(goal);

        current->visited = true;

        int i;
        for (i = 0; i < current->neighborCount; ++i) {
            Point* currentNeighbor = current->voisins[i];
            if (currentNeighbor->visited)
                continue;

            int tentative_gScore = current->gScore + distance_directe(*current, *currentNeighbor);

            if(!currentNeighbor->is_open || tentative_gScore < currentNeighbor->gScore) {
                currentNeighbor->parent = current;
                currentNeighbor->gScore = tentative_gScore;
                currentNeighbor->fScore = tentative_gScore + distance_heuristique(*currentNeighbor, *goal);

                if (!currentNeighbor->is_open)
                    set_is_open(currentNeighbor);
            }
        }
    }

    printf("pas de chemin trouvé !\n");
    PointList pointList;
    return pointList;
    */
}

PointList visitedPoints() {
    return VisitedPoints;
}

PointList reconstruct_path() {
    PointList cheminInverse, cheminComplet;

    list_init(&cheminInverse);
    list_init(&cheminComplet);

    Point current = ciblePoint;

    while (current.type != DEBUT) {
        list_append(&cheminInverse, current);
        current = list_get(&VisitedPoints, current.parentPointRank);
    }
    list_append(&cheminInverse, current);

    // Maintenant, on retourne la liste :)
    int i;
    for (i = cheminInverse.size-1; i >= 0; --i)
        list_append(&cheminComplet, list_get(&cheminInverse,i));

    return cheminComplet;
}
