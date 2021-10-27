#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include "parameters.h"
#include "initialize.h"

//compute the total kinetic energy
double kin_energy()
{
    double kin_energy = 0;
    for (int j = 0; j < natoms; j++)
    {
        kin_energy += 0.5*mass*(pow(atoms[j].vel[0],2)+pow(atoms[j].vel[1],2)+pow(atoms[j].vel[2],2));
    }

    kin_energy = kin_energy/NA*J_to_ev*10;

    return kin_energy;
}
