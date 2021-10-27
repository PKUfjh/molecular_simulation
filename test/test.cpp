#include <iostream>
#include <time.h>
#include<random>
#include <fstream>
#include <math.h>
#include "pos_distance.h"
#include "parameters.h"
#include<stdlib.h>

using namespace std;


int main(){
    float num;
    srand(time(NULL));
    num = (rand()%100)*0.01 - 0.50;
    /*这里可以控制精度,应该能看懂吧,这里是两位精度,如果你想精确到0.001,可以写成num = (rand()%1000)*0.001;*/
    cout<<"The number is: "<<num<<endl;
    
    return 0;
}
