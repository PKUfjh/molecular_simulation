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
    for (int i = 0; i < natoms; i++)
    {
        atoms[i].allocate(); //allocate the memory to the 2D array nei_list
    }
    
    for (int i = 0; i < natoms; i++)
    {   
        for (int j = i+1; j < natoms; j++)
        {   
            double mirror_info[4];
            memcpy(mirror_info,pos_distance(atoms[i].pos,atoms[j].pos),sizeof(mirror_info));
            double dist = mirror_info[0];
            
            // save all the atoms within the radius r_cut+extra_cut into neighbor list
            if (dist <= (r_cut + extra_cut)) 
            {
                atoms[i].nei_list[atoms[i].nei_num][0] = j;
                atoms[j].nei_list[atoms[j].nei_num][0] = i;
                for (int l = 0; l < 3; l++)
                {
                    atoms[i].nei_list[atoms[i].nei_num][l+1] = atoms[i].pos[l] + mirror_info[l+1];
                    atoms[j].nei_list[atoms[j].nei_num][l+1] = atoms[j].pos[l] - mirror_info[l+1];
                }
                
                atoms[i].nei_num++;
                atoms[j].nei_num++;
            }
            else{
                continue;
            }
        }
    }

}
