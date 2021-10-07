#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iostream>

using namespace std;

/* 
global parameters from the input file

natoms: number of atoms in the system
neighbor_n: maximum neigh atoms of one atom
r_cut: cutoff radius for L-J potential
extra_cut: extra cutoff radius for neighbor atom list
geo_path: path for the input file 
epsilon: input parameters for L-J potential
sigma: input parameters for L-J potential
*/

extern int natoms;extern int neighbor_n;extern double r_cut;extern double extra_cut;extern string geo_path;
extern double epsilon;extern double sigma;

/* global class of atoms, 
saving ID, index, number of neigh atoms, neighbor list, position and velocity of the atoms */

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