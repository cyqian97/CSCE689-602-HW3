#include "algorithms.hpp"

void lloyd(PointSet &pset, PointSet &centers, double &dist_sum)
{
    // Initialization
    int count_loop = 0;
    vector<Point> centers_next(centers.size(), Point{0, 0});

    while (true)
    {
        count_loop++;
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

        // Check convergence
        for (int i = 0; i < centers.size(); i++)
        {
            bool is_converge = true;
            if (centers_next[i].coord[0] != centers[i].coord[0] || centers_next[i].coord[1] != centers[i].coord[1])
            {
                is_converge = false;
                centers[i] = centers_next[i];
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

void k_means_plus_plus(PointSet &pset, int k, PointSet &centers, double &dist_sum)
{
    centers = PointSet();
    vector<double> probs(pset.size(), 1.0 / pset.size());
    for (int i = 0; i < k; i++)
    {
        centers.push_back(sample_point_from_set(pset, probs));
        for (int i = 0; i < pset.size(); i++)
        {
            probs[i] = dist(pset[i], centers);
        }
        double prob_sum = 0.0;
        for (auto &prob : probs)
        {
            prob_sum += prob;
        }
        for (auto &prob : probs)
        {
            prob /= prob_sum;
        }
    }
    lloyd(pset, centers, dist_sum);
}

// Vars for distributed alg
mutex mtx;
mutex mtx2;
mutex mtx3;
mutex mtx4;
condition_variable cv;
condition_variable cv2;
int thread_num;
int thread_count = 0;

void k_means_distributed(PointSet &pset, int k, int l, PointSet &centers, double &dist_sum, int _thread_num)
{
    thread_num = _thread_num;

    // Sample the first point
    centers = PointSet();
    vector<double> probs(pset.size(), 1.0 / pset.size());
    centers.push_back(sample_point_from_set(pset, probs));

    list<thread> thrds;
    int num_loops = 5; //log(10 * pset.size());

    // central thread
    double phi = 0.0;
    thread thrd_c(thread_central, ref(phi), num_loops);
    thrds.push_back(move(thrd_c));

    // distributed threads
    int num_p_thrd = pset.size() / thread_num;
    int start_id = 0;
    for (int i = 0; i < thread_num - 1; i++)
    {
        PointSet _pset;
        for (int i = start_id; i < start_id + num_p_thrd; i++)
        {
            _pset.push_back(pset[i]);
        }

        thread t(thread_distributed, i, ref(phi), _pset, ref(centers), l, num_loops);
        thrds.push_back(move(t));
        start_id += num_p_thrd;
    }
    {
        PointSet _pset;
        for (int i = start_id; i < pset.size(); i++)
        {
            _pset.push_back(pset[i]);
        }
        thread t(thread_distributed, thread_num - 1, ref(phi), _pset, ref(centers), l, num_loops);
        thrds.push_back(move(t));
    }

    for (auto &t : thrds)
    {
        t.join();
    }
}

void thread_central(double &phi, int num_loops)
{
    cout << "Central thread started\n";
    for (int i = 0; i < num_loops; i++)
    {
        {
            std::unique_lock<std::mutex> lk1(mtx);
            cv.wait(lk1, []
                    { return thread_count == thread_num; });
            cout << "Central thread: sync " << thread_count << " threads.\n";
            thread_count = 0;
        }
        cv2.notify_all();

        {
            std::unique_lock<std::mutex> lk1(mtx);
            cv.wait(lk1, []
                    { return thread_count == thread_num; });
            cout << "Central thread: sync " << thread_count << " threads.\n";
            thread_count = 0;
            phi = 0.0;
        }
        cv2.notify_all();
    }
}

void thread_distributed(int thread_id, double &phi, PointSet pset, PointSet &centers, int l, int num_loops)
{

    for (int i = 0; i < num_loops; i++)
    {
        // Calcuatle local part of phi
        double phi_local = 0.0;
        vector<double> probs(pset.size(), 0.0);
        for (int i = 0; i < pset.size(); i++)
        {
            double d = dist(pset[i], centers);
            probs[i] = d;
            phi_local += d;
        }

        // Update phi
        {
            std::lock_guard<std::mutex> lk1(mtx);
            cout << "Thread " << thread_id << " stage 1\n";
            phi += phi_local;
            thread_count++;
        }

        // Sync thread, wait for phi to be fully updated
        cv.notify_one();
        {
            std::unique_lock<std::mutex> lk2(mtx2);
            cv2.wait(lk2);
        }

        // Sample local points
        for (int i = 0; i < pset.size(); i++)
        {
            probs[i] = l * probs[i] / phi;
        }
        PointSet centers_local;
        for (int i = 0; i < pset.size(); i++)
        {
            if (sample_point(probs[i]))
            {
                centers_local.push_back(pset[i]);
            }
        }

        // Update centers
        {
            std::unique_lock<std::mutex> lk3(mtx3);
            centers.insert(centers.end(), centers_local.begin(), centers_local.end());
            thread_count++;
        }

        // Sync threads, wait for centers to be fully updated
        cv.notify_one();
        {
            std::unique_lock<std::mutex> lk4(mtx4);
            cv2.wait(lk4);
            cout << "Thread " << thread_id << ": finished distribution.\n";
        }
    }
}
