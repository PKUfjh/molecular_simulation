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
    return 0;
}
