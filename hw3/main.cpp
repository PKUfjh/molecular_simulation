#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <iomanip>
#include <math.h>
#include "parameters.h"
#include "initialize.h"
#include "neighbor.h"

using namespace std;

// ifstream infile;
ofstream outfile;

/* 
global parameters from the input file

natoms: number of atoms in the system
neighbor_n: maximum neigh atoms of one atom
r_cut: cutoff radius for L-J potential
extra_cut: extra cutoff radius for neighbor atom list
geo_path: path for the input file */

/* global class of atoms

class Atom: saving ID, index, number of neigh atoms, neighbor list, position and velocity of the atoms
Atom *atoms: class array saving all the atoms information 
*/

int main() {
    initialize(); // initialization of the global parameters
    setatoms(); // setting the ID, index, position and velocity for each atom in *atoms
    set_neighlist(); // setting the neigh list for each atom in *atoms
    cout << "number of neighbor atoms of #12 atom: "<< atoms[11].nei_num << endl; //test for the number of neighbor atoms

    //write neighbor list for the #12 atom
    outfile.open("geo12.out",ios::out);
    outfile << "neighbor list for #12 atom" << endl;
    int index = 11;
    outfile << "neighbor_number " << atoms[index].nei_num << endl;
    outfile.close();
    outfile.open("geo12.out",ios::app);
    for (int i = 0; i < atoms[index].nei_num; i++)
    {   
    int neighbor_num = atoms[index].nei_list[i];

    outfile << atoms[index].nei_list[i] << "\t";
    for (int i = 0; i < 3; i++)
    {
        outfile << atoms[neighbor_num].pos[i] << "\t";
    }
    outfile << "\n";
    }
    outfile.close();
    
    
    return 0;
}