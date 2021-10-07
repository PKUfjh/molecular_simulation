#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <iomanip>
#include <math.h>
#include <vector>
#include "distance.h"
#include "parameters.h"
#include "initialize.h"
#include "neighbor.h"

using namespace std;

ifstream infile;
ofstream outfile;


int main() {
    initialize();
    setatoms();
    set_neighlist();
    cout << atoms[11].nei_num << endl;

    outfile.open("geo12.out",ios::out);
    outfile << "neighbor list for #12 atom" << endl;
    int index = 11;
    outfile << "number of neighbors: " << atoms[index].nei_num << endl;
    for (int i = 0; i < atoms[index].nei_num; i++)
    {   
    int neighbor_num = atoms[index].nei_list[i];

    outfile << atoms[index].nei_list[i] << "\t";
    for (int i = 0; i < 3; i++)
    {
        outfile << atoms[neighbor_num].pos[i] << "\t";
    }
    outfile << "\n";
    
    }
    
    
    
    return 0;
}