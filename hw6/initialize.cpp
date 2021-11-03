#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "initialize.h"
#include "parameters.h"

using namespace std;

ifstream infile1;

// initialization of the global parameters
void initialize(){
    infile1.open("input",ios::in);
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
            p = strtok(NULL,d);
            natoms = atof(p);
        } 
        else if (title == "mass")
        {
            p = strtok(NULL,d);
            mass = atof(p);
        }
        
        else if (title == "geo_path")
        {
            p = strtok(NULL,d);
            geo_path = p;
        }
        else if (title == "read_vel")
        {
            p = strtok(NULL,d);
            read_vel = atof(p);
        }
        
        else if (title == "r_cut")
        {
            p = strtok(NULL,d);
            r_cut = atof(p);
        }else if (title == "extra_cut")
        {
            p = strtok(NULL,d);
            extra_cut = atof(p);
        }
        else if (title == "neighbor_n")
        {
            p = strtok(NULL,d);
            neighbor_n = atof(p);
        }
        else if (title == "epsilon")
        {
            p = strtok(NULL,d);
            epsilon = atof(p);
        }
        else if (title == "sigma")
        {
            p = strtok(NULL,d);
            sigma = atof(p);
        }
        else
        {
            continue;
        }
    }
    infile1.close();
    infile1.open("geo.in",ios::in);
    const char *startline = "\%CELL_PARAMETER";
    const char *positionline = "\%ATOMIC_POSTION";
    const char *velocityline = "\%ATOMIC_VELOCITY";

    do
    {
        infile1.getline(buf,sizeof(buf));
    } while (strstr(buf,startline) == NULL); //read input file until the startline

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
    //initialization of neighbor number for each atom
    for (int i = 0; i < natoms; i++)
    {
        atoms[i].nei_num = 0;
    }
    
}