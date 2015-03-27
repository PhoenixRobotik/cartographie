#include <stdio.h>

#include "geometrie.h"
#include "point.h"
#include "pointList.h"
#include "obstacles.h"
#include "bestInFirstOut.h"
#include "pathfinding.h"

PointList VisitedPoints;
Point realCiblePoint;

void pathfinding_init() {
    list_init(&VisitedPoints);
}

void breakp() {

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

    realCiblePoint = newPoint(cible, NOEUD);
    Point ciblePoint = newPoint(pointLePlusProche(cible), CIBLE);


    printf("commence la boucle, %d\n", open_size());

    while(open_size()!=0) {
        //printf("whileBoucle\n");
        Point visiting = pop_best_open_point();
        visiting.visited = 1;
        int visitingRank = list_append(&VisitedPoints, visiting);

        if (equal(visiting, ciblePoint)) {
            // On a fini, on reconstruit le chemin grâce au parent de chaque point.
            realCiblePoint.parentPointRank = visitingRank;
            return;
        }

        int voisinId;
        for (voisinId = 0; voisinId < 4; ++voisinId) {
            Point voisin = getVoisin(visiting, voisinId);

            // Si on l'a déjà VISITÉ on passe (peut-être on pourrait quand même changer le parent ?)
            if (list_find(&VisitedPoints, voisin)!=-1)
                continue;

            float tentative_gScore = visiting.gScore + distance(visiting.coord, voisin.coord);
            printf("tentative_gScore %f\n", tentative_gScore);
            breakp();

            Point* voisinOpenPointer = find_in_open(voisin);
            int voisin_is_open = 1;

            if (voisinOpenPointer == NULL) {
                voisin_is_open = 0;
                voisinOpenPointer = &voisin;
            }

            if(!voisin_is_open || tentative_gScore < voisinOpenPointer->gScore) {
                printf("c\n");
                voisinOpenPointer->parentPointRank = visitingRank;
                voisinOpenPointer->gScore = tentative_gScore;
                voisinOpenPointer->fScore = tentative_gScore + distance_heuristique(*voisinOpenPointer, realCiblePoint);

                if (!voisin_is_open)
                    add_to_open(voisin);
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

    Point current = realCiblePoint;

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
