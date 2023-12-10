#include <iostream>

#include "utils.hpp"
#include "algorithms.hpp"

using namespace std;

int main()
{
    string dirname = "../data/";
    string dataname = "data";
    PointSet pset;
    read_data(dirname + dataname + "_points.txt", pset);
    cout << "Read " << pset.size() << " data points.\n";
    PointSet centers;
    read_data(dirname + dataname + "_centers.txt", centers);
    cout << "Read " << centers.size() << " data centers.\n";

    double dist_sum = 0.0;
    lloyd(pset,centers,dist_sum);
    cout << "dist_sum: " << dist_sum << endl;
    write_data(dirname+dataname+"_res_points.txt",pset);
    write_data(dirname+dataname+"_res_centers.txt",centers);
}
