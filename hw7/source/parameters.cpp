#include <iostream>
#include <string.h>
#include "parameters.h"

using namespace std;

int natoms = 0; int neighbor_n = 0; double r_cut = 0; double extra_cut = 0; string geo_path = "";
double epsilon = 0.0;double sigma = 0.0;
double delta_t = 0.0;
double T_0 = 0;
double vector_a[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
double mass = 0; int read_vel = 0;
double NA = 6.02214086e23; double Bolzmann_k = 1.38064852e-23;double J_to_ev = 6.24150974e18;


Atom *atoms = new Atom [1024];

//set position and velocity array for the Atom class
void Atom::setpos(double position[3]){
    memcpy(pos,position,sizeof(pos));
}

void Atom::setvel(double velocity[3]){
    memcpy(vel,velocity,sizeof(vel));
}

void Atom::allocate(){
    nei_list = new double [neighbor_n];
}