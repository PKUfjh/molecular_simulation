#include <math.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include "pos_distance.h"
#include "parameters.h"
#include "force_energy.h"
#include "kin_energy.h"
#include "rdf.h"
#include "neighbor.h"
#include "mdrun.h"

double rdf(double radius){
    int num = 0;
    for (int i = 0; i < natoms; i++)
    {
        for (int j = 0; j < atoms[i].nei_num; j++){
            int neighbor_num = atoms[i].nei_list[j];
            double distance = shortest(atoms[i].pos,atoms[neighbor_num].pos)[0];
            if (distance >= radius && distance <= radius + rdf_dr)
            {
                num += 1;
            }
        }
    }
    return 1.0*volume*num/(natoms*natoms*4*M_PI*radius*radius*rdf_dr);

    
}