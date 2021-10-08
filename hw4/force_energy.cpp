#include <iostream>
#include <stdio.h>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <iomanip>
#include <math.h>
#include "pos_distance.h"
#include "parameters.h"
#include "neighbor.h"

using namespace std;

ifstream infile;

//L-J potential of two input coordinates
double LJ_potential(double alist[3],double blist[3]){
    double u;
    double r_ab;
    double tem;
    double tem_cut;
    r_ab = pos_distance(alist,blist);
    tem = pow(sigma/r_ab,6);
    tem_cut = pow(sigma/r_cut,6);
    if (r_ab > r_cut)
    {
        u = 0;
    }else{
        u = 4*epsilon*(pow(tem,2)-tem) - 4*epsilon*(pow(tem_cut,2)-tem_cut);
    }
    return u;
}

//L-J force of teo input coordinates
double *LJ_force(double alist[3],double blist[3]){
    static double force[3];
    double r_ab;
    double tem;
    double dir[3] = {0};
    for (int i = 0; i < 3; i++)
    {
        dir[i] = alist[i] - blist[i];
    }
    
    r_ab = pos_distance(alist,blist);
    tem = pow(sigma/r_ab,6);
    if (r_ab < r_cut)
    {   
        for (int i = 0; i < 3; i++)
        {
            force[i] = 4*epsilon*(12*pow(tem,2)-6*tem)*dir[i]/pow(r_ab,2);
        }
    }
    return force;
}

//output the total energy of one atom and its neigh list, and total force of one atom
double *energy_force(Atom atom1){
    static double energy_force[4];
    double energy = 0.0;
    double force[3] = {0};
    for (int i = 0; i < atom1.nei_num; i++)
    {
        energy = energy + LJ_potential(atom1.pos,atoms[atom1.nei_list[i]].pos);
        for (int j = 0; j < 3; j++)
        {
            force[j] =  force[j] + LJ_force(atom1.pos,atoms[atom1.nei_list[i]].pos)[j];
        }
        
    }
    energy_force[0] = energy;
    for (int k =1; k < 4; k++)
    {
        energy_force[k] = force[k-1];
    }
    
    return energy_force;
}
