#include <iostream>
#include <string.h>

using namespace std;

extern int natoms;extern int neighbor_n;extern int r_cut;extern int extra_cut;extern string geo_path;

#ifndef PARAMETERS
#define PARAMETERS




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
    // void setpos(double position[3]);
    // void setvel(double velocity[3]);
    // void setneighbor_num(int neighbor_num);
    // void setneighbor_list(int *neighbot_list);
};

#endif