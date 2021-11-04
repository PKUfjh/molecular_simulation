#include <math.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "pos_distance.h"
#include "parameters.h"

using namespace std;

//compute the distance between two coordinates
double single_distance(double alist[3],double blist[3]){
    double dis = 0;
    for (int i = 0; i < 3; i++)
    {
        dis += pow(alist[i]-blist[i],2);
    }
    dis = sqrt(dis);
    return dis;
}

//compute the distance between two coordinates under PBC
double *shortest(double alist[3],double blist[3]){
    static double shortest[4];
    double zero[3] = {0};
    double clist[3];
    for (int i = 0; i < 3; i++)
    {
        clist[i] = alist[i] - blist[i];
        double length = single_distance(vector_a[i],zero);
        while (clist[i] >= length/2)
        {
            clist[i] -= length;
        }
        while (clist[i] < -length/2)
        {
            clist[i] += length;
        }
    }
    
    shortest[0] = single_distance(clist,zero);
    memcpy(shortest+1,clist,sizeof(clist));
    return shortest;
}

void restrict_in_box(double alist[3]){
    for (int i = 0; i < 3; i++)
    {
        double zero[3] = {0};
        double length = single_distance(vector_a[i],zero);
        while (alist[i] < 0)
        {
            alist[i] += length;
        }
        while (alist[i] >= length)
        {
            alist[i] -= length;
        }  
    }
    
}
