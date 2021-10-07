#include <iostream>
#include "parameters.h"
#include "initialize.h"
#include "neighbor.h"
#include "force_energy.h"

using namespace std;

int main() {
    initialize();// initialization of the global parameters
    setatoms();  // setting the ID, index, position and velocity for each atom in *atoms
    set_neighlist();  // setting the neigh list for each atom in *atoms
    cout << energy_force(atoms[13])[0] << endl; //output the first component of total force of #12 atom
    cout << energy_force(atoms[13])[1] << endl;//output the second component of total force of #12 atom
    cout << energy_force(atoms[13])[2] << endl; //output the third component of total force of #12 atom
       
    return 0;
}