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
    clock_t start = clock();
    initialize(); // initialization of the global parameters
    set_neighlist(); // setting the neigh list for each atom in *atoms
    cout << "number of neighbor atoms of #12 atom: " << atoms[11].nei_num << endl; //test for the number of neighbor atoms
    
    //write neighbor list for the #12 atom
    outfile.open("../geo2.out",ios::out);
    outfile << "neighbor list for #12 atom" << endl;
    int index = 11;
    outfile << "neighbor_number " << atoms[index].nei_num << endl;
    for (int i = 0; i < atoms[index].nei_num; i++)
    {   
    int neighbor_num = atoms[index].nei_list[i];
    
    outfile << neighbor_num << "\t";
    for (int j = 0; j < 3; j++)
    {   
        outfile.precision(15);
        outfile << atoms[neighbor_num].pos[j] << "\t";
    }
    outfile << "\n";
    }
    outfile.close();

     //release the memory allocated to nei_list
    for (int j = 0; j < natoms; j++)
    {
        delete[] atoms[j].nei_list;
    }

    delete[] atoms;
    clock_t end = clock();
    outfile.open("../running time for "+geo_path,ios::out);
    outfile <<"Running Time : "<<(double)(end - start)/ CLOCKS_PER_SEC << "s" << endl;
    outfile << "CPU: Intel(R)_Core(TM)_i7-10700_CPU_@_2.90GHz" << endl;
    outfile << "CPU core number: 1";
    outfile.close(); 
    
    
    return 0;
}