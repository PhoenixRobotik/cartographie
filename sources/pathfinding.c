#include <stdio.h>

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
/*
    if (passagePossible(start, cible) == 1) {
        // OUI !
        Point newStart = newPoint(start, DEBUT);
        ciblePoint = newPoint(cible, CIBLE);
        ciblePoint.parentPointRank = list_append(&VisitedPoints, newStart);
        return;
    }
*/

    // On "recalibre" les points en fonction de la grille.
    Point startPoint = newPoint(start, DEBUT);
    Point newStart = newPoint(pointLePlusProche(start), NOEUD);

    newStart.gScore = distance(start, newStart.coord);
    newStart.fScore = distance(newStart.coord, cible);
    newStart.parentPointRank = list_append(&VisitedPoints, startPoint);
    add_to_open(newStart);

    Point realCiblePoint = newPoint(cible, NOEUD);
    ciblePoint = newPoint(pointLePlusProche(cible), CIBLE);


    printf("commence la boucle, %d\n", open_size());

    while(open_size()!=0) {
        printf("whileBoucle\n");
        Point current = pop_best_open_point();
        int currentVisitedRank = list_append(&VisitedPoints, current);
        current.visited = 1;

        // On a fini, on reconstruit le chemin grâce au parent de chaque point.
        if (distance(current.coord, ciblePoint.coord)==0) {
            ciblePoint.parentPointRank = currentVisitedRank;
            return;
        }

        int i;
        for (i = 0; i < 4; ++i) {
                printf("a\n");
            Point currentVoisin = getVoisin(current, i);
            // Si on l'a déjà visité on passe (peut-être on pourrait quand même changer le parent ?)
            if (list_find(&VisitedPoints, currentVoisin)!=-1)
                continue;

            int tentative_gScore = current.gScore + distance(current.coord, currentVoisin.coord);

                printf("b\n");
            if(!is_open(currentVoisin) || tentative_gScore < currentVoisin.gScore) {
                printf("c\n");
                currentVoisin.parentPointRank = currentVisitedRank;
                currentVoisin.gScore = tentative_gScore;
                currentVoisin.fScore = tentative_gScore + distance_heuristique(currentVoisin, ciblePoint);

                if (!is_open(currentVoisin))
                    add_to_open(currentVoisin);
            }
        }
    }
    printf("pas de chemin trouvé !\n");
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
