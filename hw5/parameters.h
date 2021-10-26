#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iostream>

using namespace std;

/* 
global parameters from the input files

natoms: number of atoms in the system
neighbor_n: maximum neigh atoms of one atom
r_cut: cutoff radius for L-J potential
extra_cut: extra cutoff radius for neighbor atom list
geo_path: path for the input file 
vector_a: vector representing the lattice constant
epsilon: input parameters for L-J potential
sigma: input parameters for L-J potential
mass: atomic mass
read_vel: how the velocity is initialized
NA: Avogadro constant
Bolzmann_k: Bolzmann constant
J_to_eV: unit transformation from Joule to eV
*/

extern int natoms;extern int neighbor_n;
extern double r_cut;extern double extra_cut;extern string geo_path;
extern double vector_a[3][3];
extern double epsilon;extern double sigma;
extern double delta_t;
extern double mass; extern int read_vel;
extern double NA; extern double Bolzmann_k; extern double J_to_ev;

/* global class of atoms, 
saving ID, index, number of neigh atoms, neighbor list, position and velocity of the atoms */

class Atom
{
private:
public:
    string ID ;
    int index;
    int nei_num;
    double *nei_list;
    double pos[3];
    double vel[3];
    // declare function
    void allocate();
    void setpos(double position[3]);
    void setvel(double velocity[3]);
};

extern Atom *atoms;

#endif