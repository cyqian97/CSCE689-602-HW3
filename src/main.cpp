#include <iostream>
#include <chrono>

#include "utils.hpp"
#include "algorithms.hpp"

using namespace std;

int main()
{
    string dirname = "../data/";
    string dataname = "data";
    PointSet pset;
    read_data(dirname + dataname + "_points.txt", pset);
    std::cout << "Read " << pset.size() << " data points.\n";

    // Read Gaussian distribution centers as good initial centers, generte reference result
    std::cout << "===================\n";
    std::cout << "Reference:\n";
    PointSet centers;
    read_data(dirname + dataname + "_centers.txt", centers);
    int center_num = centers.size();
    std::cout << "\tRead " << centers.size() << " data centers.\n";

    double dist_sum = 0.0;
    lloyd(pset, centers, dist_sum);
    std::cout << "\tdist_sum: " << dist_sum << endl;
    write_data(dirname + dataname + "_ref_points.txt", pset);
    write_data(dirname + dataname + "_ref_centers.txt", centers);

    // k-means ++
    std::cout << "\n===================\n";
    std::cout << "k-means ++: \n";
    centers = PointSet();
    dist_sum = 0.0;
    auto start = chrono::high_resolution_clock::now();
    k_means_plus_plus(pset, center_num, centers, dist_sum);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    std::cout << "\tTotal excution tims: " << duration.count() << " ms" << endl;
    std::cout << "\tdist_sum: " << dist_sum << endl;
    write_data(dirname + dataname + "_plus_points.txt", pset);
    write_data(dirname + dataname + "_plus_centers.txt", centers);
    // this_thread::sleep_for(std::chrono::seconds(5));

    
    // k-means ||
    std::cout << "\n===================\n";
    std::cout << "k-means ||:\n";
    int l = center_num;
    // for (int i = 0; i < 10; i++)
    // {
    //     std::cout << "Round " << i << endl;
    centers = PointSet();
    dist_sum = 0.0;
    start = chrono::high_resolution_clock::now();
    k_means_distributed(pset, center_num, l, centers, dist_sum, 12);
    // }
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    std::cout << "\tTotal excution tims: " << duration.count() << " ms" << endl;
    dist_sum = 0.0;
    int i;
    for (auto &p : pset)
    {
        dist_sum += dist(p, centers, i);
    }
    std::cout << "\tdist_sum: " << dist_sum << endl;
    write_data(dirname + dataname + "_distrib_points.txt", pset);
    write_data(dirname + dataname + "_distrib_centers.txt", centers);
}
