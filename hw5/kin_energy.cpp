#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include "parameters.h"
#include "initialize.h"


double kin_energy()
{
    double kin_energy = 0;
    if (read_vel == 1)
    {   
        double center_vel[3] = {0};
        double tot_mass = 0;
        for (int j = 0; j < natoms; j++)
        {
            tot_mass += mass;
            center_vel[0] += mass*atoms[j].vel[0];
            center_vel[1] += mass*atoms[j].vel[1];
            center_vel[2] += mass*atoms[j].vel[2];
        }
        center_vel[0] = center_vel[0]/tot_mass;
        center_vel[1] = center_vel[1]/tot_mass;
        center_vel[2] = center_vel[2]/tot_mass;
        for (int j = 0; j < natoms; j++)
        {
            atoms[j].vel[0] = atoms[j].vel[0] - center_vel[0];
            atoms[j].vel[1] = atoms[j].vel[1] - center_vel[1];
            atoms[j].vel[2] = atoms[j].vel[2] - center_vel[2];
            kin_energy += 0.5*mass*(pow(atoms[j].vel[0],2)+pow(atoms[j].vel[1],2)+pow(atoms[j].vel[2],2));
        }

        kin_energy = kin_energy/NA*J_to_ev*10;
        
    }
    else{
        return 0;
    }
    return kin_energy;
}
