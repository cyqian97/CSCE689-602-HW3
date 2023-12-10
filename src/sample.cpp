#include "sample.hpp"

bool sample_point(double prob)
{
    return (double(rand()) / RAND_MAX < prob);
}

PointSet::iterator sample_point_from_set(PointSet pset, list<double> probs)
{
    assert(pset.size() == probs.size());

    double r = double(rand()) / RAND_MAX;
    double accum_prob = 0.0;
    PointSet::iterator iter_pset = pset.begin();
    for (auto prob : probs)
    {
        accum_prob += prob;
        if (accum_prob > r)
        {
            return iter_pset;
        }
        iter_pset++;
    }
}