#ifndef PATHFINDING_H
#define PATHFINDING_H

PointList astar(Point* start, Point* goal);

PointList reconstruct_path(Point* goal);

#endif // PATHFINDING_H
