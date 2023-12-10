#include <iostream>
#include "utils.hpp"

using namespace std;

int main()
{
    PointSet pset;
    read_data("data/data_points.txt", pset);
    cout << "data size: " << pset.size() << endl;
}
