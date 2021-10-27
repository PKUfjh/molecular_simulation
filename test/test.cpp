#include <iostream>
#include <time.h>
#include<random>
#include <fstream>
#include <math.h>
#include "pos_distance.h"
#include "parameters.h"

using namespace std;


int main(){
    for (int i = 0; i < 2; i++)
    {
        default_random_engine e(time(0));
        uniform_real_distribution<double> u(-1.2,3.5);
        for(int i = 0; i < 2; ++i)
		cout << u(e) << endl;
    }
    
    
;
    return 0;
}
