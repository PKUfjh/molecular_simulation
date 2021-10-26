#ifndef FORCE_ENERGY_H
#define FORCE_ENERGY_H
#include "parameters.h"

//L-J potential of two input coordinates
double LJ_potential(double r_ab);

//L-J force of teo input coordinates
double *LJ_force(double r_ab,double dir[3]);

//output the total energy of one atom and its neigh list, and total force of one atom
double *energy_force(Atom atom1);

#endif