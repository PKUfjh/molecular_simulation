#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <math.h>
#include "parameters.h"
#include "initialize.h"
#include "neighbor.h"
#include "pos_distance.h"

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
    cout << "number of neighbor atoms of #16 atom: " << atoms[16].nei_num << endl; //test for the number of neighbor atoms
    
    //write neighbor list for the #12 atom
    outfile.open("geo16.out",ios::out);
    outfile << "neighbor list for #12 atom" << endl;
    int index = 16;
    outfile << "neighbor_number " << atoms[index].nei_num << endl;
    outfile.close();
    outfile.open("geo16.out",ios::app);
    for (int i = 0; i < atoms[index].nei_num; i++)
    {   
    int neighbor_num = atoms[index].nei_list[i][0];

    outfile << atoms[index].nei_list[i][0] << "\t";
    for (int j = 0; j < 3; j++)
    {   
        outfile.precision(15);
        outfile << atoms[index].nei_list[i][j+1] << "\t";
    }
    outfile << "\n";
    }
    outfile.close();
    
    
    return 0;
}