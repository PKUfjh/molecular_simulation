#include <math.h>
#include "distance.h"

using namespace std;

double distance(double alist[3], double blist[3]){
    double dis = 0.0;
    for (int i = 0; i < 3; i++)
    {
        dis += pow(alist[i]-blist[i],2);
    }

    dis = sqrt(dis);

    return dis;
}