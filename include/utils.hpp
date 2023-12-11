#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "types.hpp"

using namespace std;

int read_data(string filename, PointSet& pset);

int write_data(string filename, PointSet& pset);

int append_data(string filename, vector<double> v);

double mean(vector<double> v);

double sigma(vector<double> v);

#endif // UTILS_HPP