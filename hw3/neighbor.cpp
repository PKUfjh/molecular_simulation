#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <iomanip>
#include <math.h>
#include <vector>
#include "distance.h"
#include "parameters.h"

using namespace std;

ifstream infile_n;


// Atom *atoms = new Atom[900];

void setatoms(){
    infile_n.open("geo.in",ios::in);
    const char *startline = "\%ATOMIC_POSTION";
    const char *middleline = "\%ATOMIC_VELOCITY";
    char buf[1024];

    do
    {
        infile_n.getline(buf,sizeof(buf));
    } while (strstr(buf,startline) == NULL);

    int ind = 0;
    while (infile_n.getline(buf,sizeof(buf)))
    {
        double poslist[3];
        if (strstr(buf,middleline) != NULL)
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
        atoms[ind].setpos(poslist);
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
        atoms[ind].setvel(vellist);
        ind++;
    };
}


void set_neighlist(){
    int nlist[natoms]; 
    int list[natoms][neighbor_n];
    for (int i = 0; i < natoms; i++)
    {   
        nlist[i] = 0;
        for (int j = 0; j < natoms; j++)
        {
            if (j == i)
            {
                continue;
            }
            
            double dist = distance(atoms[i].pos,atoms[j].pos);
            if (dist <= (r_cut + extra_cut))
            {
                list[i][nlist[i]] = j;
                nlist[i]++;
            }
        }
        atoms[i].nei_num = nlist[i];
        atoms[i].nei_list = list[i];
    }

}
