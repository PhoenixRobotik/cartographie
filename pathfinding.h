#ifndef PATHFINDING_H
#define PATHFINDING_H
void pathfinding_init();
void pathfinding_reinit();

int pathfinding_start(int start_x, int start_y, int cible_x, int cible_y);
int pathfinding(coord start, coord cible);

PointList reconstruct_path();

PointList visitedPoints();


#endif // PATHFINDING_H
