#ifndef TYPES_HPP
#define TYPES_HPP

#include <list>
#include <array>
#include <vector>

using namespace std;

struct Point
{
    array<double, 2> coord;
    int weight = 1;
    int center_id = -1;
};

typedef vector<Point> PointSet;


#endif // TYPES_HPP