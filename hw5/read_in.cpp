#include "parameters.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

double **read_in(string filename,int STEP){
    double **list = new double *[natoms];
    for (int i = 0; i < natoms; i++)
    {
        list[i] = new double [3];
    }

    if (STEP == -1)
    {
        for (int i = 0; i < natoms; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                list[i][j] = atoms[i].pos[j] - atoms[i].vel[j]*delta_t;
            }
        }
        return list;
    }
    ifstream infile;
    infile.open(filename,ios::in);

    string mark = "STEP "+to_string(STEP);
    const char *startline = mark.c_str();
    int ind = 0;
    char buf[1024];
    do
    {
        infile.getline(buf,sizeof(buf));
    } while (strstr(buf,startline) == NULL); //read input file until the startline

    while (infile.getline(buf,sizeof(buf)))
    {
        if (ind >= natoms) //do the first loop until all atoms are read
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
        list[ind][pos] = A_num;
        pos ++;
        }while(p);
        ind++;
    };
    infile.close();
    return list;
}