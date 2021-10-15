#include <iostream>
#include <fstream>
#include <string.h>
#include "parameters.h"
#include "initialize.h"
#include "neighbor.h"
#include "force_energy.h"

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

    outfile.open("energy.txt",ios::out);
    double energy = 0;
    for (int i = 0; i < natoms; i++)
    {
        // outfile << atoms[i].ID << "\t";
        // outfile.precision(12);
        // outfile << energy_force(atoms[i])[0] << endl;//output the energy of each atom
        energy += energy_force(atoms[i])[0];
    }
    outfile.precision(12);
    outfile <<"total energy: " << energy << endl; //output the total menergy
    outfile.close();
    outfile.open("force.txt",ios::out);
    //output the total force of each atom
    for (int i = 0; i < natoms; i++)
    {
        double force[4];
        memcpy(force,energy_force(atoms[i]),sizeof(force));
        outfile << atoms[i].ID << "\t";
        outfile.precision(12);
        outfile << force[1] << "\t";
        outfile << force[2] << "\t";
        outfile << force[3] << endl;
    }
    outfile.close();

    for (int j = 0; j < natoms; j++)
    {
        delete[] atoms[j].nei_list;
    }
    return 0;
}