#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iostream>

using namespace std;

extern int natoms;extern int neighbor_n;extern double r_cut;extern double extra_cut;extern string geo_path;


class Atom
{
private:
public:
    string ID ;
    int index;
    int nei_num;
    int *nei_list;
    double pos[3];
    double vel[3];
    // declare function
    void setpos(double position[3]);
    void setvel(double velocity[3]);
};

extern Atom *atoms;

#endif