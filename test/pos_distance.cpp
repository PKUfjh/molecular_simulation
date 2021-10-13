#include <math.h>
#include <fstream>
#include "pos_distance.h"
#include "parameters.h"

using namespace std;

ifstream infile_v;

double vector_a[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

double single_distance(double alist[3],double blist[3]){
    double dis = 0;
    for (int i = 0; i < 3; i++)
    {
        dis += pow(alist[i]-blist[i],2);
    }
    dis = sqrt(dis);
    return dis;
}

//compute the distance between two coordinates
double pos_distance(double alist[3], double blist[3]){
    char buf[1024];
    infile_v.open("geo.in",ios::in);
    const char *startline = "\%CELL_PARAMETER";

    do
    {
        infile_v.getline(buf,sizeof(buf));
    } while (strstr(buf,startline) == NULL); //read input file until the startline

    for (int j = 0; j < 3; j++)
    {
        infile_v.getline(buf,sizeof(buf));
        const char *d = "\t";
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

    double dis = 999999999;
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
                dis = min(dis,single_distance(alist,tem));
            }
            
        }
    }
    return dis;
}