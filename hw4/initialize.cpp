#include <iostream>
#include <fstream>
#include <string.h>
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
        else if (title == "geo_path")
        {
            p = strtok(NULL,d);
            geo_path = p;
        }else if (title == "r_cut")
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
}