#include "algorithms.hpp"

void lloyd(PointSet &pset, PointSet &centers, double &dist_sum)
{
    // Initialization
    int count_loop = 0;
    vector<Point *> centers_vec;
    vector<Point> centers_next;
    for (auto &p : centers)
    {
        centers_vec.push_back(&p);
        centers_next.push_back(Point{0, 0});
    }

    while (true)
    {
        count_loop ++;
        vector<int> center_count(centers.size(), 0);
        dist_sum = 0.0;
        for (auto &p : pset)
        {
            int i;
            dist_sum += dist(p, centers, i);
            centers_next[i].coord[0] += p.coord[0] * p.weight;
            centers_next[i].coord[1] += p.coord[1] * p.weight;
            center_count[i] += p.weight;
        }
        for (int i = 0; i < centers.size(); i++)
        {
            centers_next[i].coord[0] /= center_count[i];
            centers_next[i].coord[1] /= center_count[i];
        }
        // cout << "centers: " << endl;
        // for (auto c : centers_next)
        // {
        //     cout << c.coord[0] << ", " << c.coord[1] << endl;
        // }
        // Check convergence
        for (int i = 0; i < centers.size(); i++)
        {
            bool is_converge = true;
            if (centers_next[i].coord[0] != centers_vec[i]->coord[0] || centers_next[i].coord[1] != centers_vec[i]->coord[1])
            {
                is_converge = false;
                *centers_vec[i] = centers_next[i];
                centers_next[i] = Point{0, 0};
            }
            if (is_converge)
            {
                cout << "Lloyd's Algorithm finished in " << count_loop << " loops." << endl;
                return;
            }
        }
    }
}
