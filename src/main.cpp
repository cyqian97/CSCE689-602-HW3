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

    // Read Gaussian distribution centers as good initial centers, generte reference result
    PointSet centers;
    read_data(dirname + dataname + "_centers.txt", centers);
    int center_num = centers.size();
    cout << "Read " << centers.size() << " data centers.\n";

    double dist_sum = 0.0;
    lloyd(pset,centers,dist_sum);
    cout << "dist_sum: " << dist_sum << endl;
    write_data(dirname+dataname+"_ref_points.txt",pset);
    write_data(dirname+dataname+"_ref_centers.txt",centers);

    // k-means ++
    centers = PointSet(); 
    dist_sum = 0.0;
    k_means_plus_plus(pset,center_num,centers,dist_sum);
    cout << "dist_sum: " << dist_sum << endl;
    write_data(dirname+dataname+"_plus_points.txt",pset);
    write_data(dirname+dataname+"_plus_centers.txt",centers);


}
