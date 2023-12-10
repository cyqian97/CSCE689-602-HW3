#ifndef SAMPLE_HPP
#define SAMPLE_HPP
#include <assert.h>

#include <stdlib.h> /* srand, rand */

#include "types.hpp"

using namespace std;

bool sample_point(double prob);

PointSet::iterator sample_point_from_set(PointSet pset, list<double> probs);

#endif // SAMPLE_HPP