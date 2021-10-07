#include <iostream>
#include <string.h>
#include "global.h"

using namespace std;

int atoms = 0; int neighbor_n = 0; int r_cut = 0; int extra_cut = 0; string geo_path = "";

void Atom::setpos(double position[3]){
    memcpy(pos,position,sizeof(pos));
}

void Atom::setvel(double velocity[3]){
    memcpy(vel,velocity,sizeof(vel));
}