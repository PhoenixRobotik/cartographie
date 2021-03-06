#include "astar.h"
#if USE_SDL
#include "hardware.h"
#endif
PointList VisitedPoints;
Point realCiblePoint;

Point trim_point(Point point) {
    if (est_sur_la_grille(point.coord))
        return point;

    Point pointTrim = point;

    int i;
    for (i = 0; i < 4; ++i) {
        pointTrim = getVoisin(point, i);
        if (passagePossible(point.coord, pointTrim.coord))
            return pointTrim;
    }
    pointTrim.type = ERREUR;
    return pointTrim;
}

void pre_astar() {
    list_init(&VisitedPoints);
}
void post_astar() {
    list_free(&VisitedPoints);
    reset_open();
}
int astar(coord start, coord cible) {
    // On définit le point de départ
    Point startPoint= newPoint(start, DEBUT);
    startPoint.gScore = 0;
    startPoint.fScore = distance_heuristique(startPoint.coord, realCiblePoint.coord);
    // Et on l'ajoute à la liste des visités ET des ouverts
    int startPointRank = list_append(&VisitedPoints, startPoint);
    if (startPointRank == -1) {
        debug(1, "Erreur dans le code ? à startPoint:%d:%d\n",
            startPoint.coord.x, startPoint.coord.y);
        return -1;
    }
    if(add_to_open(startPoint) == -1) {
        debug(1, "Erreur dans le code ? à startpoint:%d:%d\n",
            startPoint.coord.x, startPoint.coord.y);
        return -1;
    }

    // On définit le point d'arrivée : on récupère son voisin sur la grille
    // le plus susceptible d'être visité en premier.
      realCiblePoint = newPoint(cible, CIBLE);
    Point ciblePoint = trim_point(realCiblePoint);
    if (ciblePoint.type == ERREUR) {
        return 0;
    }

    #if USE_SDL
    dessine_point_passage_carto(start.x,start.y,4);
    dessine_point_passage_carto(cible.x,cible.y,4);
    #endif

    // Tout d'abord on regarde si on peut aller tranquillement de start à cible :
    debug(1, "on peut aller directement ?\n");
    if (passagePossible(start, cible)) {
        debug(1, "on peut aller directement !\n");
        // OUI !
        realCiblePoint.parentPointRank = startPointRank;
        return 1;
    }
    debug(1, "on ne peut pas aller directement :(\n");

    // Tant qu'il y a des points à visiter…
    while(open_size()!=0) {
        Point visiting = pop_best_open_point();
        int visitingRank = list_append(&VisitedPoints, visiting);
        if (visitingRank == -1) {
            // Si il y a eu un overflow…
            debug(1, "Overflow à %d:%d\n", visiting.coord.x, visiting.coord.y);
            return 0;
        }

        #if USE_SDL
        dessine_point_passage_carto(visiting.coord.x,visiting.coord.y,1);
        #endif

        if (equal(visiting, ciblePoint)) {
            // On a fini, on reconstruit le chemin grâce au parent de chaque point.
            realCiblePoint.parentPointRank = visitingRank;
            realCiblePoint.gScore = visiting.gScore + distance(visiting.coord, realCiblePoint.coord);
            realCiblePoint.fScore = realCiblePoint.gScore;
            return 1;
        }


        int  voisinId;
        for (voisinId = 0; voisinId < 4; ++voisinId) {
            Point voisin = getVoisin(visiting, voisinId);
            if (voisin.type == ERREUR) {
                debug(1, "Voisin impossible : %d\n", voisinId);
                return -1;
            }
            if (!passagePossible(visiting.coord, voisin.coord))
                continue;

            // Si on l'a déjà VISITÉ on passe
            if (list_find(&VisitedPoints, voisin)!=-1)
                continue;

            float tentative_gScore = visiting.gScore + distance(visiting.coord, voisin.coord);

            Point* voisinOpenPointer = find_in_open(voisin);
            int voisin_is_open = 1;

            if (voisinOpenPointer == NULL) {
                voisin_is_open = 0;
                voisinOpenPointer = &voisin;
            }

            if(!voisin_is_open || tentative_gScore < voisinOpenPointer->gScore) {
                voisinOpenPointer->parentPointRank = visitingRank;
                voisinOpenPointer->gScore = tentative_gScore;
                voisinOpenPointer->fScore = tentative_gScore
                        + distance_heuristique((*voisinOpenPointer).coord, realCiblePoint.coord);

                if (!voisin_is_open)
                    if (add_to_open(voisin) == -1) {
                        debug(1, "Overflow à %d:%d\n", voisin.coord.x, voisin.coord.y);
                        return -1;
                    }
            }
        }
    }
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
//                                             THETA STAR
////////////////////////////////////////////////////////////////////////////////


Point get_precedent_theta_start(Point current) {
    Point precedent, subprecedent;
    precedent = list_get(&VisitedPoints, current.parentPointRank);
    if (precedent.type == DEBUT)
        return precedent;
    #if USE_SDL
    dessine_point_passage_carto(precedent.coord.x, precedent.coord.y, 2);
    #endif
    subprecedent = list_get(&VisitedPoints, precedent.parentPointRank);
    if (passagePossible(current.coord, subprecedent.coord)) {
        current.parentPointRank = precedent.parentPointRank;
        return get_precedent_theta_start(current);
    }

    return precedent;
}

int reconstruct_path(PointList *cheminComplet) {
    PointList cheminInverse;

    list_init(&cheminInverse);
    list_free( cheminComplet);
    list_init( cheminComplet);

    Point current = realCiblePoint;
    #if USE_SDL
    coord old = current.coord;
    #endif

    while (current.type != DEBUT) {
        list_append(&cheminInverse, current);
        #if USE_SDL
        dessine_obstacle_ligne(old.x, old.y, current.coord.x, current.coord.y);
        dessine_point_passage_carto(current.coord.x, current.coord.y, 3);
        old = current.coord;
        #endif
        current = get_precedent_theta_start(current);
    }

    #if USE_SDL
    dessine_obstacle_ligne(old.x, old.y, current.coord.x, current.coord.y);
    dessine_point_passage_carto(current.coord.x, current.coord.y, 3);
    #endif
    list_append(&cheminInverse, current);

    // Maintenant, on retourne la liste :)
    int i;
    for (i = cheminInverse.size-1; i >= 0; --i)
        list_append(cheminComplet, list_get(&cheminInverse,i));

    list_free(&cheminInverse);
    return 0;
}
