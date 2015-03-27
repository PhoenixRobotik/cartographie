// BIFO : Best In First Out
#ifndef BESTINFIRSTOUT_H
#define BESTINFIRSTOUT_H value

// We define a linked list to keep it sorted while inserting.
// The first point of the list is the best.
struct node{
    Point point;
    struct node* next;
};
typedef struct node node;

// Donne le meilleur point (la tête de la liste) et le supprime de la liste.
Point pop_best_open_point();

// Ajoute un point dans la liste
void add_to_open(Point);

// Cherche dans la liste si le point est ouvert (regarde les coordonnées)
int is_open(Point);
Point* find_in_open(Point point);

// Indique la taille de la liste (si 0, la liste est vide)
int open_size();

#endif // BESTINFIRSTOUT_H
