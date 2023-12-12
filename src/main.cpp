#include <iostream>
#include <chrono>

#include "utils.hpp"
#include "algorithms.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    string dirname = "../data/";
    string dataname = "data";
    string resultname = argv[2];
    vector<double>results;

    // Read points data
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
    results.push_back(dist_sum);
    // write_data(dirname + dataname + "_ref_points.txt", pset);
    // write_data(dirname + dataname + "_ref_centers.txt", centers);

    vector<double> dist_sum_plus;
    vector<double> dist_sum_distrib;
    vector<double> time_plus;
    vector<double> time_distrib;
    for (int i = 0; i < 10; i++)
    {
        // k-means ++
        std::cout << "\n===================\n";
        std::cout << "k-means ++: \n";
        centers = PointSet();
        dist_sum = 0.0;
        auto start = chrono::high_resolution_clock::now();
        k_means_plus_plus(pset, center_num, centers, dist_sum);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration<double, milli>(stop - start);
        std::cout << "\tTotal excution tims: " << duration.count() << " ms" << endl;
        std::cout << "\tdist_sum: " << dist_sum << endl;
        dist_sum_plus.push_back(dist_sum);
        time_plus.push_back(duration.count());

        // write_data(dirname + dataname + "_plus_points.txt", pset);
        // write_data(dirname + dataname + "_plus_centers.txt", centers);

        // k-means ||
        std::cout << "\n===================\n";
        std::cout << "k-means ||:\n";
        int l = center_num;
        int thrd_num = atof(argv[1]);
        cout << "\tthread num: " << thrd_num << endl;
        centers = PointSet();
        dist_sum = 0.0;
        start = chrono::high_resolution_clock::now();
        k_means_distributed(pset, center_num, l, centers, dist_sum, thrd_num);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration<double, milli>(stop - start);
        std::cout << "\tTotal excution tims: " << duration.count() << " ms" << endl;
        dist_sum = 0.0;
        int j;
        for (auto &p : pset)
        {
            dist_sum += dist(p, centers, j);
        }
        std::cout << "\tdist_sum: " << dist_sum << endl;
        dist_sum_distrib.push_back(dist_sum);
        time_distrib.push_back(duration.count());
        // write_data(dirname + dataname + "_distrib_points.txt", pset);
        // write_data(dirname + dataname + "_distrib_centers.txt", centers);
    }
    
    results.push_back(mean(dist_sum_plus));
    results.push_back(sigma(dist_sum_plus));
    results.push_back(mean(dist_sum_distrib));
    results.push_back(sigma(dist_sum_distrib));
    results.push_back(mean(time_plus));
    results.push_back(sigma(time_plus));
    results.push_back(mean(time_distrib));
    results.push_back(sigma(time_distrib));
    append_data(resultname,results);
}
