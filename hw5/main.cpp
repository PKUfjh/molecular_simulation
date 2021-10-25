#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include "parameters.h"
#include "initialize.h"
#include "neighbor.h"
#include "mdrun.h"

using namespace std;

ofstream outfile;

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
    
    mdrun(0);
    //release the memory allocated to nei_list
    for (int j = 0; j < natoms; j++)
    {
        for (int k = 0; k < neighbor_n; k++)
        {
            delete[] atoms[j].nei_list[k];
        }
        delete[] atoms[j].nei_list;
    }
    
    return 0;
}