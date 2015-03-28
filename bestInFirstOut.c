// BIFO : Best In First Out

//  On va créer une re de liste dans laquelle on peut rajouter
//  des points, et "pop" va donner le point qui a le meilleur score.

#include <stdlib.h>
#include "point.h"
#include "bestInFirstOut.h"

int openCount = 0;
node* headOfOpenPoints = NULL;

Point pop_best_open_point(){
    Point bestOpenPoint;

    //TODO Il y a là une erreur, à gérer
    if (openCount == 0) {
        bestOpenPoint.type = ERREUR;
        return bestOpenPoint;
        //printf("Error : cannot pop_best_open_point, BIFO is empty !\n");
        //exit(1);
    }

    bestOpenPoint = headOfOpenPoints->point;

    node* nextBestOpenPoint= headOfOpenPoints->next;
    free(headOfOpenPoints);
    headOfOpenPoints = nextBestOpenPoint;

    openCount--;

    return bestOpenPoint;
}

void add_to_open(Point newPoint){
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
    openCount++;
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
