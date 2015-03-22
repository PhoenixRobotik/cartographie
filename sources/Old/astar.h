#ifndef ASTAR_H
#define ASTAR_H

PointList astar(Point* start, Point* goal);

PointList reconstruct_path(Point* goal);

#endif // ASTAR_H
