#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "types.hpp"

using namespace std;

void read_data(string filename, PointSet& pset)
{
    ifstream file;
    file.open(filename);
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
};

#endif // UTILS_H{{}}