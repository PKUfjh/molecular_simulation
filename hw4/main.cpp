#include <iostream>
#include "parameters.h"
#include "initialize.h"
#include "neighbor.h"
#include "force_energy.h"

using namespace std;

/* 
global parameters from the input file
:
natoms: number of atoms in the system
neighbor_n: maximum neigh atoms of one atom
r_cut: cutoff radius for L-J potential
extra_cut: extra cutoff radius for neighbor atom list
geo_path: path for the input file 
epsilon: input parameters for L-J potential
sigma: input parameters for L-J potential

global class of atoms
:
class Atom: saving ID, index, number of neigh atoms, neighbor list, position and velocity of the atoms
Atom *atoms = new Atom[900]: class array saving all the atoms information 
*/

int main() {
    initialize();// initialization of the global parameters
    setatoms();  // setting the ID, index, position and velocity for each atom in *atoms
    set_neighlist();  // setting the neigh list for each atom in *atoms
    cout << energy_force(atoms[13])[0] << endl;//output the energy of total force of #12 atom
    cout << energy_force(atoms[13])[1] << endl; //output the first component of total force of #12 atom
    cout << energy_force(atoms[13])[2] << endl;//output the second component of total force of #12 atom
    cout << energy_force(atoms[13])[3] << endl; //output the third component of total force of #12 atom
       
    return 0;
}