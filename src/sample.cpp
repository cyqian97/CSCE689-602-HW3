#include "sample.hpp"

bool sample_point(double prob)
{
    return (double(rand()) / RAND_MAX < prob);
}

Point sample_point_from_set(PointSet &pset, vector<double> &probs)
{
    assert(pset.size() == probs.size());

    double r = double(rand()) / RAND_MAX;
    double accum_prob = 0.0;
    for (int i = 0 ; i<pset.size();i++)
    {
        accum_prob += probs[i];
        if (accum_prob >= r)
        {
            return pset[i];
        }
    }
    return pset[pset.size()-1];
}

// Point sample_and_erase(PointSet &pset, list<double> &probs)
// {
//     PointSet::iterator pit = sample_point_from_set(pset, probs);
//     Point p = *pit;
//     pset.erase(pit);
//     return p;
// }