#include "geometry.hpp"

double dist(Point &p1, Point &p2)
{
    return p1.weight * (pow(p1.coord[0] - p2.coord[0], 2) + pow(p1.coord[1] - p2.coord[1], 2));
}

double dist(Point &p1, PointSet& pset)
{
    double d =  numeric_limits<double>::max();

    for (auto& p2 : pset)
    {
        double d_i = dist(p1, p2);
        if (d_i < d)
        {
            d = d_i;
        }
    }
    return d;
}

double dist(Point &p1, PointSet& pset, int &id)
{
    id = -1;
    double d =  numeric_limits<double>::max();

    int i = 0;
    for (auto p2 : pset)
    {
        double d_i = dist(p1, p2);
        if (d_i < d)
        {
            d = d_i;
            id = i;
        }
        i++;
    }
    p1.center_id = id;
    return d;
}