#include <iostream>
#include <string.h>
#include "parameters.h"

using namespace std;

int natoms = 0; int neighbor_n = 0; double r_cut = 0; double extra_cut = 0; string geo_path = "";


Atom *atoms = new Atom[1024];

//set position and velocity array for the Atom class
void Atom::setpos(double position[3]){
    memcpy(pos,position,sizeof(pos));
}

void Atom::setvel(double velocity[3]){
    memcpy(vel,velocity,sizeof(vel));
}