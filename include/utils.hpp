#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "types.hpp"

using namespace std;

int read_data(string filename, PointSet& pset);

int write_data(string filename, PointSet& pset);

#endif // UTILS_HPP