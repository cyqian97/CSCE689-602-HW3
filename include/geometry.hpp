#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <cmath>
#include <limits>

#include "types.hpp"

using namespace std;

double dist(Point &p1, Point &p2);
double dist(Point &p1, PointSet pset);
double dist(Point &p1, PointSet pset, int &id);
#endif // GEOMETRY_HPP