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
T_0: initial temperature for random initialization of velocity
epsilon: input parameters for L-J potential
sigma: input parameters for L-J potential
mass: atomic mass
read_vel: how the velocity is initialized
NA: Avogadro constant
Bolzmann_k: Bolzmann constant
J_to_eV: unit transformation from Joule to eV
MD_step:total MD steps
*/

extern int natoms;extern int neighbor_n;
extern double r_cut;extern double extra_cut;extern string geo_path;
extern double vector_a[3][3];
extern double T_0;
extern double **pre1_pos;
extern double **pre2_pos;
extern double **pre1_force;
extern double **delta_D;

extern double epsilon;extern double sigma;
extern double delta_t;
extern int neighbor_step;extern int output_step;
extern double mass; extern int read_vel;extern int MD_alg;
extern double NA; extern double Bolzmann_k; extern double J_to_ev;
extern int MD_step;extern string ensemble; extern double T_res; extern int nraise;
extern int cal_msd; extern int msd_interval;
extern int cal_rdf; extern double rdf_rcut;extern double rdf_dr; extern int rdf_geo1; extern int rdf_geo2; extern int rdf_interval;
extern double rdflist[85]; extern double volume;

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