#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include "pos_distance.h"
#include "parameters.h"

using namespace std;

// set neighbor list for each atom in the model in class Atom
void set_neighlist(){
    //initilize neighbor list for each atom
    for (int j = 0; j < natoms; j++)
    {
        atoms[j].nei_num = 0;
        atoms[j].nei_list[natoms] = {0};
    }
    
    for (int i = 0; i < natoms; i++)
    {   
        for (int j = i+1; j < natoms; j++)
        {   
            double dist = shortest(atoms[i].pos,atoms[j].pos)[0];
            
            // save all the atoms within the radius r_cut+extra_cut into neighbor list
            if (dist <= (r_cut + extra_cut)) 
            {
                atoms[i].nei_list[atoms[i].nei_num] = j;
                atoms[j].nei_list[atoms[j].nei_num] = i;
                
                atoms[i].nei_num++;
                atoms[j].nei_num++;
            }
            else{
                continue;
            }
        }
    }

}
