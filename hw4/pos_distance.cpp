#include <math.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "pos_distance.h"
#include "parameters.h"

using namespace std;

ifstream infile_v;


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
double *pos_distance(double alist[3], double blist[3]){
    static double pos_distance[4];

    double dis = 999999999;
    //compute the minimum distane between one atom with the other atom and its mirror
    for (int i_1 = 0; i_1 < 3; i_1++){
        for (int i_2 = 0; i_2 < 3; i_2++)
        {
            for (int i_3 = 0; i_3 < 3; i_3++)
            {   
                double tem[3];
                memcpy(tem,blist,sizeof(tem));
                for (int k = 0; k < 3; k++)
                {
                    tem[k] = tem[k] + (i_1 - 1)*vector_a[0][k] + (i_2 - 1)*vector_a[1][k] + (i_3 - 1)*vector_a[2][k];
                }
                double temdis = single_distance(alist,tem);
                if ( temdis < dis)
                {
                    dis = temdis;
                    pos_distance[0] = dis;
                    for (int l = 0; l < 3;l++)
                    {
                        // pos_distance[l+1] = alist[l] - tem[l];
                        pos_distance[l+1] = tem[l];
                    }
                    
                }
            }
            
        }
    }
    return pos_distance;
}