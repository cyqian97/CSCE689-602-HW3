#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <iostream>
#include <condition_variable>
#include <thread>

#include "geometry.hpp"
#include "sample.hpp"

/// @brief Lloyd's algorithm
/// @param pset: input point set
/// @param centers: input & output centers
/// @param dist_sum: output summation of distances from all points to their representive
void lloyd(PointSet &pset, PointSet &centers, double &dist_sum);

/// @brief k-means++ algorithm
/// @param pset: input point set
/// @param k: input center number
/// @param centers: output centers
/// @param dist_sum: output summation of distances from all points to their representive
void k_means_plus_plus(PointSet &pset, int k, PointSet &centers, double &dist_sum);

/// @brief k-means++ algorithm
/// @param pset: input point set
/// @param k: input center number
/// @param l: input oversampling factor
/// @param centers: output centers
/// @param dist_sum: output summation of distances from all points to their representive
void k_means_distributed(PointSet &pset, int k, int l, PointSet &centers, double &dist_sum, int _thread_num = 10);
void thread_central(double &phi, int num_loops);
void thread_distributed(int thread_id, double &phi, PointSet pset, PointSet &centers, int l, int num_loops);

#endif // ALGORITHMS_HPP