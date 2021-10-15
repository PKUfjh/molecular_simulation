#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "pos_distance.h"
#include "parameters.h"

using namespace std;

ifstream infile_n;

/* set ID, index, number of neigh atoms, neighbor list, position and velocity
for each atom in the model in class Atom */
void setatoms(){
    infile_n.open("geo.in",ios::in);
    const char *startline = "\%ATOMIC_POSTION";
    const char *middleline = "\%ATOMIC_VELOCITY";
    char buf[1024];

    do
    {
        infile_n.getline(buf,sizeof(buf));
    } while (strstr(buf,startline) == NULL); //read input file until the startline

    int ind = 0;
    while (infile_n.getline(buf,sizeof(buf)))
    {
        double poslist[3];
        if (strstr(buf,middleline) != NULL) //do the first loop until the middleline
        {
            break;
        }
        
        string id_name;
        const char *d = "\t";
        char *p= strtok(buf,d);
        if (p == NULL)
        {   
            continue;
        }
        
        id_name = p;

        int pos = 0;
        do
        {   
        double A_num;
        p = strtok(NULL,d);

        if (p == NULL)
        {
            break;
        }
        A_num = atof(p);
        poslist[pos] = A_num;
        pos ++;
        }while(p);
        atoms[ind].index = ind;
        atoms[ind].ID = id_name;
        atoms[ind].setpos(poslist); //set ID, index, position for each atom in the first loop
        ind++;
    };

    ind = 0;
    while (infile_n.getline(buf,sizeof(buf)))
    {   
        double vellist[3];
        const char *d = "\t";
        char *p= strtok(buf,d);

        int pos = 0;
        do
        {   
        double A_num;
        p = strtok(NULL,d);

        if (p == NULL)
        {
            break;
        }
        A_num = atof(p);
        vellist[pos] = A_num;
        pos ++;
        }while(p);
        atoms[ind].setvel(vellist); //set velocity for each atom in the second loop
        ind++;
    };
}

// set neighbor list for each atom in the model in class Atom
void set_neighlist(){
    int nlist[natoms]; 
    for (int i = 0; i < natoms; i++)
    {   
        atoms[i].allocate();
        
        nlist[i] = 0;
        for (int j = 0; j < natoms; j++)
        {
            if (j == i)
            {
                continue;
            }
            double mirror_info[4];
            memcpy(mirror_info,pos_distance(atoms[i].pos,atoms[j].pos),sizeof(mirror_info));
            double dist = mirror_info[0];
            
            // save all the atoms within the radius r_cut+extra_cut into neighbor list
            if (dist <= (r_cut + extra_cut)) 
            {
                atoms[i].nei_list[nlist[i]][0] = j;
                for (int l = 0; l < 3; l++)
                {
                    atoms[i].nei_list[nlist[i]][l+1] = mirror_info[l+1];
                }
                
                nlist[i]++;
            }
            else{
                continue;
            }
        }
        atoms[i].nei_num = nlist[i];
    }

}
