#ifndef PATHFINDING_H
#define PATHFINDING_H

// To be called once. Or not at all. As u wish.
void pathfinding_init();

// To start the actual pathfinding. Returns if a path was found or not.
int pathfinding(int start_x, int start_y, int cible_x, int cible_y);

// Returns the number of passing points.
int return_length_of_path_found();
// Returns the list of passing points.
void return_path_found(int tableau[][2]);

// Gestion des obstacles temporaires
// Retourne le nombre d'obstacles non statiques alors en place, ou -1 si erreur.
int nouvel_obstacle_rond(int x, int y, int rayon);
void reinitialise_obstacles_temporaires();

#endif // PATHFINDING_H
