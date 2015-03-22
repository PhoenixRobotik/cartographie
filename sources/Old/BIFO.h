// BIFO : Best In First Out

#ifndef BIFO_H
#define BIFO_H

// We define a linked list to keep it sorted while inserting.
// The first point of the list is the best.

struct node {
    Point* pointedPoint;
    struct node* next;
};


Point* pop_best_open_point();


void set_is_open(Point*);


int is_open_empty();

#endif // BIFO_H
