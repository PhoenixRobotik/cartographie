
#if DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "geometrie.h"
#include "point.h"
#include "pointList.h"
#include "obstacles.h"
#include "bestInFirstOut.h"
#include "pathfinding.h"

#if USE_SDL
#include "debug/affichage.h"
#endif

PointList VisitedPoints;
Point realCiblePoint;

void pathfinding_init() {
    list_init(&VisitedPoints);
    addAllObstaclesStatiques();
#if USE_SDL
    init_sdl_screen();
    dessine_fond();
    int i;
    for (i = 0; i < NOMBRE_OBSTACLES_STATIQUES; ++i) {
        Obstacle obstacle = getObstacleStatique(i);
        if (obstacle.type == 0)
            add_trait(obstacle.point1.x, obstacle.point1.y, obstacle.point2.x, obstacle.point2.y);
        else {
            add_circle(obstacle.point1.x, obstacle.point1.y, obstacle.rayon + ROBOT_R, 20);
        }
    }
#endif
}



void pathfinding(coord start, coord cible) {

    // On "recalibre" les points en fonction de la grille.
    Point realStartPoint= newPoint(start, DEBUT);
    Point startPoint    = newPoint(pointLePlusProche(start), NOEUD);
    Point ciblePoint    = newPoint(pointLePlusProche(cible), NOEUD);
          realCiblePoint= newPoint(cible, CIBLE);

    realStartPoint.gScore = 0;
    realStartPoint.fScore = distance_heuristique(realStartPoint.coord, realCiblePoint.coord);

    startPoint.parentPointRank = list_append(&VisitedPoints, realStartPoint);

    startPoint.gScore = distance(start, startPoint.coord);
    startPoint.fScore = startPoint.gScore + distance_heuristique(startPoint.coord, realCiblePoint.coord);

#if USE_SDL
    add_passage_point(start.x,start.y,1);
    add_passage_point(cible.x,cible.y,1);
#endif

#if DEBUG
    printf("on peut aller directement ?\n");
#endif
    // Tout d'abord on regarde si on peut aller tranquillement de start à cible :
    if (passagePossible(start, cible)) {
#if DEBUG
        printf("on peut aller directement\n");
#endif
        // OUI !
        realCiblePoint.parentPointRank = startPoint.parentPointRank;
        return;
    }
#if DEBUG
    printf("on ne peut pas aller directement\n");
#endif

    add_to_open(startPoint);


    while(open_size()!=0) {
        //printf("whileBoucle\n");
        Point visiting = pop_best_open_point();
        visiting.visited = 1;
        int visitingRank = list_append(&VisitedPoints, visiting);
#if USE_SDL
        add_passage_point(visiting.coord.x,visiting.coord.y,0);
#endif

        if (equal(visiting, ciblePoint)) {
            // On a fini, on reconstruit le chemin grâce au parent de chaque point.
            realCiblePoint.parentPointRank = visitingRank;
            realCiblePoint.gScore = visiting.gScore + distance(visiting.coord, realCiblePoint.coord);
            realCiblePoint.fScore = realCiblePoint.gScore;
            return;
        }

        int voisinId;
        for (voisinId = 0; voisinId < 4; ++voisinId) {
           // int i=0;
           // while(++i<10000000);
            //printf("go\n");
            Point voisin = getVoisin(visiting, voisinId);
            if (!passagePossible(visiting.coord, voisin.coord))
                continue;

            // Si on l'a déjà VISITÉ on passe (peut-être on pourrait quand même changer le parent ?)
            if (list_find(&VisitedPoints, voisin)!=-1)
                continue;

            float tentative_gScore = visiting.gScore + distance(visiting.coord, voisin.coord);
            //printf("tentative_gScore %f\n", tentative_gScore);

            Point* voisinOpenPointer = find_in_open(voisin);
            int voisin_is_open = 1;

            if (voisinOpenPointer == NULL) {
                voisin_is_open = 0;
                voisinOpenPointer = &voisin;
            }

            if(!voisin_is_open || tentative_gScore < voisinOpenPointer->gScore) {
                //printf("c\n");
                voisinOpenPointer->parentPointRank = visitingRank;
                voisinOpenPointer->gScore = tentative_gScore;
                voisinOpenPointer->fScore = tentative_gScore
                        + distance_heuristique((*voisinOpenPointer).coord, realCiblePoint.coord);

                if (!voisin_is_open)
                    add_to_open(voisin);
            }
        }
    }
#if DEBUG
    printf("pas de chemin trouvé !\n");
#endif
}

PointList visitedPoints() {
    return VisitedPoints;
}

Point get_precedent_theta_start(Point current) {
    Point precedent, subprecedent;
    precedent = list_get(&VisitedPoints, current.parentPointRank);
    if (precedent.type == DEBUT)
        return precedent;
    subprecedent = list_get(&VisitedPoints, precedent.parentPointRank);
    if (passagePossible(current.coord, subprecedent.coord)) {
        current.parentPointRank = precedent.parentPointRank;
        return get_precedent_theta_start(current);
    }

    return precedent;
}

PointList reconstruct_path() {
    PointList cheminInverse, cheminComplet;

    list_init(&cheminInverse);
    list_init(&cheminComplet);

    Point current = realCiblePoint;
#if USE_SDL
    coord old = current.coord;
#endif

    while (current.type != DEBUT) {
        list_append(&cheminInverse, current);
#if USE_SDL
        add_trait(old.x, old.y, current.coord.x, current.coord.y);
        add_passage_point(current.coord.x, current.coord.y, 2);
        old = current.coord;
#endif
        current = get_precedent_theta_start(current);
    }
#if USE_SDL
    add_trait(old.x, old.y, current.coord.x, current.coord.y);
    add_passage_point(current.coord.x, current.coord.y, 2);
#endif
    list_append(&cheminInverse, current);

    // Maintenant, on retourne la liste :)
    int i;
    for (i = cheminInverse.size-1; i >= 0; --i)
        list_append(&cheminComplet, list_get(&cheminInverse,i));

    return cheminComplet;
}
