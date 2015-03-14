// BIFO : Best In First Out

/*
    On va créer une structure de liste dans laquelle on peut rajouter
    des points, et "pop" va donner le point qui a le meilleur score.

*/
#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "BIFO.h"

int openCount = 0;
struct node* headOfOpenPoints;

void set_is_open(Point* point){
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->pointedPoint = point;

    if (openCount == 0) {
        newNode->next = newNode;
        headOfOpenPoints = newNode;
    } else {
        struct node* current = headOfOpenPoints;
        while (current->next != 0
            && is_better(*(current->next->pointedPoint), *point))
            current = current ->next;

        newNode->next = current->next;
        current->next = newNode;
    }
    point->is_open = true;
    openCount++;
}

Point* pop_best_open_point(){
    if (openCount == 0) {
        printf("Error : cannot pop_best_open_point, BIFO is empty !\n");
        exit(1);
    }

    Point* bestOpenPoint = headOfOpenPoints->pointedPoint;
    struct node* nextBestOpenPoint = headOfOpenPoints->next;
    free(headOfOpenPoints);

    headOfOpenPoints = nextBestOpenPoint;

    openCount--;
    bestOpenPoint->is_open = false;

    return bestOpenPoint;
}


int is_open_empty() {
    return (openCount==0);
}
