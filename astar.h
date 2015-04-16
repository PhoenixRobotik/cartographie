#ifndef ASTAR_H
#define ASTAR_H

#include <stdlib.h>
#include "pointList.h"
#include "obstacles.h"
#include "bestInFirstOut.h"

#include "debug.h"

void pre_astar();
int astar(coord start, coord cible);
void post_astar();

int reconstruct_path(PointList *cheminComplet);

PointList visitedPoints();


#endif // ASTAR_H
