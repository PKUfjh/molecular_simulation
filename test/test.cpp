#include <iostream>
#include <fstream>
#include "pos_distance.h"
#include "parameters.h"

using namespace std;


int main(){
    double alist[3] = {32.6620979507,24.2384190653,20.601090991};
    double blist[3] = {0.958537767622,11.2148260576,5.41037676614};
    cout << "single " << single_distance(alist,blist) << endl;
    cout << "pos " << pos_distance(alist,blist) << endl;
    int neighbor_n = 20;
    double **nei_list = new double *[neighbor_n];
    for (int i = 0; i < neighbor_n; i++)
    {
        nei_list[i] = new double [4];
    }
    for (int i = 0; i < neighbor_n; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            nei_list[i][j] = i + j;
        }
    }
    for (int i = 0; i < neighbor_n; i++)
    {
        delete[] nei_list[i];
    }
    
    delete[] nei_list;

    cout << "ds" << endl;
    return 0;
}
