#include <iostream>
#include <fstream>
#include <math.h>
#include "pos_distance.h"
#include "parameters.h"

using namespace std;


int main(){
    double r1 = 32.6620979507 - -8.96402092864*0.1;
    double r2 = 32.6620979507;
    double f = 0.0146230270325;
    double m = 4.0026;
    double r3 = 2*r2 - r1 + f/m * 0.01;
    cout << r1 << endl;
    cout << r3 << endl;
    return 0;
}
