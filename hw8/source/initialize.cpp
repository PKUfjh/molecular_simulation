#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <random>
#include <string.h>
#include <stdlib.h>
#include "initialize.h"
#include "parameters.h"
#include "kin_energy.h"

using namespace std;

ifstream infile1;

// initialization of the global parameters, position and velocity of atoms
void initialize(){
    infile1.open("../input",ios::in);
    char buf[1024];

    while (infile1.getline(buf,sizeof(buf)))
    {
        const char *d = " \t";
        char *p= strtok(buf,d);
        if (p == NULL)
        {
            continue;
        }
        string title;
        title = p;
        
        if (title == "natoms")
        {
            p = strtok(NULL,d);natoms = atof(p);
        } 
        else if (title == "mass")
        {
            p = strtok(NULL,d);mass = atof(p);
        }
        else if (title == "geo_path")
        {
            p = strtok(NULL,d);geo_path = p;
        }
        else if (title == "read_vel")
        {
            p = strtok(NULL,d);read_vel = atof(p);
        }
        else if (title == "T_0")
        {
            p = strtok(NULL,d);T_0 = atof(p);
        }
        else if (title == "r_cut")
        {
            p = strtok(NULL,d);r_cut = atof(p);
        }else if (title == "extra_cut")
        {
            p = strtok(NULL,d);extra_cut = atof(p);
        }
        else if (title == "neighbor_n")
        {
            p = strtok(NULL,d);neighbor_n = atof(p);
        }
        else if (title == "delta_t")
        {
            p = strtok(NULL,d);delta_t = atof(p);
        }
        else if (title == "neighbor_step")
        {
            p = strtok(NULL,d);neighbor_step = atof(p);
        }
        else if (title == "output_step")
        {
            p = strtok(NULL,d);output_step = atof(p);
        }
        else if (title == "epsilon")
        {
            p = strtok(NULL,d);epsilon = atof(p);
        }
        else if (title == "sigma")
        {
            p = strtok(NULL,d);sigma = atof(p);
        }
        else
        {
            continue;
        }
    }
    infile1.close();

    atoms = new Atom [natoms];
    infile1.open(geo_path,ios::in);
    const char *startline = "\%CELL_PARAMETER";
    const char *positionline = "\%ATOMIC_POSTION";
    const char *velocityline = "\%ATOMIC_VELOCITY";

    do
    {
        infile1.getline(buf,sizeof(buf));
    } while (strstr(buf,startline) == NULL); //read input file until the startline

    //initialization of lattice vectors from input file
    for (int j = 0; j < 3; j++)
    {
        infile1.getline(buf,sizeof(buf));
        const char *d = " \t";
        char *p= strtok(buf,d);
        if (p == NULL)
        {   
            continue;
        }
        double A_num = atof(p);
        vector_a[j][0] = A_num;
        
        int pos = 1;
        do
        {   
        p = strtok(NULL,d);
        if (p == NULL)
        {
            break;
        }
        A_num = atof(p);
        vector_a[j][pos] = A_num;
        pos ++;
        }while(p);
    }

    /* set ID, index, number of neigh atoms, neighbor list, position and velocity
        for each atom in the model in class Atom */
    do
    {
        infile1.getline(buf,sizeof(buf));
    } while (strstr(buf,positionline) == NULL); //read input file until the startline

    int ind = 0;
    while (infile1.getline(buf,sizeof(buf)))
    {
        double poslist[3];
        if (strstr(buf,velocityline) != NULL) //do the first loop until the middleline
        {
            break;
        }
        
        string id_name;
        const char *d = " \t";
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

    //initialization of velocity for each atom
    //read_vel 1: read from input
    if (read_vel == 1)
    {   
        ind = 0;
        while (infile1.getline(buf,sizeof(buf)))
        {   
            double vellist[3];
            const char *d = " \t";
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
        infile1.close();
    }
    //read_vel 0: random initialization
    else if (read_vel == 0)
    {
        infile1.close();
        double kinetic_energy = 0;
        double tot_mass = 0;
        double center_vel[3] = {0};
        double temperature;
        double factor;
        for (int i = 0; i < natoms; i++)
        {   
            srand(time(NULL)+i);
            for(int j = 0; j < 3; ++j)
                atoms[i].vel[j] = (rand()%100)*0.01 - 0.50;
            tot_mass += mass;
            center_vel[0] += mass*atoms[i].vel[0];
            center_vel[1] += mass*atoms[i].vel[1];
            center_vel[2] += mass*atoms[i].vel[2];
        }
        center_vel[0] = center_vel[0]/tot_mass;
        center_vel[1] = center_vel[1]/tot_mass;
        center_vel[2] = center_vel[2]/tot_mass;
        for (int j = 0; j < natoms; j++)
        {
            atoms[j].vel[0] = atoms[j].vel[0] - center_vel[0];
            atoms[j].vel[1] = atoms[j].vel[1] - center_vel[1];
            atoms[j].vel[2] = atoms[j].vel[2] - center_vel[2];
            kinetic_energy += 0.5*mass*(pow(atoms[j].vel[0],2)+pow(atoms[j].vel[1],2)+pow(atoms[j].vel[2],2));
        }
        kinetic_energy = kinetic_energy/NA*J_to_ev*10;
        temperature = kinetic_energy*2/(3*Bolzmann_k*natoms*J_to_ev);
        factor = T_0/temperature;
        for (int j = 0; j < natoms; j++)
        {
            atoms[j].vel[0] = sqrt(factor)*atoms[j].vel[0];
            atoms[j].vel[1] = sqrt(factor)*atoms[j].vel[1];
            atoms[j].vel[2] = sqrt(factor)*atoms[j].vel[2];
        }
    }

    for (int i = 0; i < natoms; i++)
    {
        atoms[i].allocate(); //allocate the memory to the nei_list
    }
    
    pre1_pos = new double *[natoms];
    for (int i = 0; i < natoms; i++)
    {
        pre1_pos[i] = new double [3];
    }

    pre2_pos = new double *[natoms];
    for (int i = 0; i < natoms; i++)
    {
        pre2_pos[i] = new double [3];
    }

    pre1_force = new double *[natoms];
    for (int i = 0; i < natoms; i++)
    {
        pre1_force[i] = new double [3];
    }
}