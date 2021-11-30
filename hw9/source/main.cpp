#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <time.h>
#include "parameters.h"
#include "initialize.h"
#include "neighbor.h"
#include "mdrun.h"
#include "force_energy.h"

using namespace std;

ofstream outfile;

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

global class of atoms
:
class Atom: saving ID, index, number of neigh atoms, neighbor list, position and velocity of the atoms
Atom *atoms = new Atom[900]: class array saving all the atoms information 
*/

int main() {
    clock_t start = clock();
    initialize();// initialization of the global parameters, position and velocity of atoms
    
    //run molecular dynamics
    for (int i = 0; i <= MD_step; i++)
    {
        if (i%neighbor_step == 0)
        {
            set_neighlist(); //searching neighbor list for every atom every 5 steps
        }
        mdrun(i);
    }
    
    
    //release the memory allocated to nei_list
    for (int j = 0; j < natoms; j++)
    {
        delete[] atoms[j].nei_list;
    }
    clock_t end = clock();
    cout <<"Running Time : "<<(double)(end - start)/ CLOCKS_PER_SEC << endl;
    
    return 0;
}