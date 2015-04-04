#ifndef PATHFINDING_H
#define PATHFINDING_H

// To be called once. Or not at all. As u wish.
void pathfinding_init();

int pathfinding(int start_x, int start_y, int cible_x, int cible_y);

int return_length_of_path_found();
void return_path_found(int tableau[][2]);

#endif // PATHFINDING_H
