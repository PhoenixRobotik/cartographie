#include <stdlib.h>
#include "point.h"
#if USE_SDL
#include "simulation/affichage.h"
#endif
#include "bestInFirstOut.h"

// BIFO : Best In First Out

//  On va créer une re de liste dans laquelle on peut rajouter
//  des points, et "pop" va donner le point qui a le meilleur score.

int openCount = 0;
node* headOfOpenPoints = NULL;

int reset_open() {
    node* current = headOfOpenPoints;
    node* next;
    while(current != NULL) {
        next = current->next;
        free(current);
        openCount--;
        current = next;
    }
    headOfOpenPoints = current;
    if (openCount != 0) {
        // There is a fatal bug in this code then, creating mem leak.
        openCount = 0;
        headOfOpenPoints = NULL;
        return -1;
    }
    return 0;
}

Point pop_best_open_point() {
    Point bestOpenPoint;

    //TODO Il y a là une erreur à gérer
    if (openCount == 0)
        return errorPoint();

    bestOpenPoint = headOfOpenPoints->point;

    node* nextBestOpenPoint= headOfOpenPoints->next;
    free(headOfOpenPoints);
    headOfOpenPoints = nextBestOpenPoint;

    openCount--;

    return bestOpenPoint;
}

int add_to_open(Point newPoint) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->point = newPoint;

    // La liste était vide ou le nouveau point doit être mis au début
    if (openCount == 0 || is_better(newPoint, headOfOpenPoints->point)) {
        newNode->next = headOfOpenPoints;
        headOfOpenPoints = newNode;
    } else {
        node* current = headOfOpenPoints;

        while(current->next != NULL &&  // Le dernier point pointe sur zéro
              !is_better(newPoint, current->next->point) )
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
    }

    #if USE_SDL
    dessine_point_passage_carto(newPoint.coord.x,newPoint.coord.y,0);
    #endif
    return openCount++;
}

Point* find_in_open(Point point) {
    node* current = headOfOpenPoints;
    while(current != NULL) {
        if(equal(point, current->point))
            return &(current->point);
        current = current->next;
    }
    return NULL;
}

int open_size() {
    return openCount;
}
