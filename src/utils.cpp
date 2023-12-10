#include "utils.hpp"

int read_data(string filename, PointSet &pset)
{
    ifstream file;
    file.open(filename);
    if (!file)
    {
        cerr << "ERROR: Unable to open data file: " << filename << "\n";
        exit(EXIT_FAILURE);
    }
    string current_line;
    while (getline(file, current_line))
    {
        istringstream s(current_line);
        string field;
        Point p;

        int i = 0;
        while (getline(s, field, ' '))
        {
            if (field.empty())
                continue;

            p.coord[i] = atof(field.c_str());
            i++;
        }
        pset.push_back(p);
    }
    file.close();
    return 0;
}

int write_data(string filename, PointSet &pset)
{
    ofstream file;
    file.open(filename);
    if (!file)
    {
        cerr << "ERROR: Unable to open data file: " << filename << "\n";
        exit(EXIT_FAILURE);
    }
    for (auto p : pset)
    {
        file << setprecision(8) << p.coord[0] << " " << p.coord[1] << " " << p.weight << " " << p.center_id << endl;
    }
    file.close();
    return 0;
}