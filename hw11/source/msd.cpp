#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include "pos_distance.h"
#include "parameters.h"
#include "msd.h"

using namespace std;

double msd(){
    double msd = 0;
    double origin[3] = {0};
    for (int i = 0; i < natoms; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            delta_D[i][k] += shortest(atoms[i].pos,pre1_pos[i])[k+1];
        }
    }
    for (int i = 0; i < natoms; i++)
    {
        msd += pow(single_distance(delta_D[i],origin),2); 
    }
    msd = 1.0*msd/natoms;
    return msd;
}
