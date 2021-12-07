#include <math.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "pos_distance.h"
#include "parameters.h"
#include "force_energy.h"
#include "kin_energy.h"
#include "mdrun.h"
#include "msd.h"
#include "velo_verlet.h"
#include <random>
#include <chrono>

double velo_verlet(int STEP){
    double pot_energy;
    // 从epoch（1970年1月1日00:00:00 UTC）开始经过的纳秒数，unsigned类型会截断这个值
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    // 第一个参数为高斯分布的平均值，第二个参数为标准差
    double gauss_sigma = sqrt(Bolzmann_k*T_res*NA*1000/mass)*0.01;
    std::normal_distribution<double> normal(0.0, gauss_sigma);
    //均匀分布产生碰撞概率
    std::uniform_real_distribution<double> uniform(0.0,1.0); 

    for (int i = 0; i < natoms; i++)
    {   
        double poslist[3];
        double vellist[3];
        for (int k = 0; k < 3; k++)
        {
            poslist[k] = atoms[i].pos[k] + atoms[i].vel[k] * delta_t + (pre1_force[i][k]*NA*0.1*0.5)/(mass*J_to_ev) * pow(delta_t,2);
            vellist[k] = atoms[i].vel[k]  + (pre1_force[i][k]*NA*0.1*0.5)/(mass*J_to_ev) * delta_t;
        }
        restrict_in_box(poslist);
        atoms[i].setpos(poslist);
        atoms[i].setvel(vellist);
    }

    for (int i = 0; i < natoms; i++)
    {
        double force[4];
        memcpy(force,energy_force(atoms[i]),sizeof(force));
        memcpy(pre1_force[i],force+1,3*sizeof(double));
        pot_energy += force[0];
    }

    if (ensemble == "NVT")
    {
        for (int i = 0; i < natoms; i++)
        {
            if (uniform(generator) < 1.0/nraise){
                for (int k = 0; k < 3; k++){
                    atoms[i].vel[k] = normal(generator);
                }
            }
            else{
                for (int k = 0; k < 3; k++){
                    atoms[i].vel[k] = atoms[i].vel[k] + (pre1_force[i][k]*NA*0.1*0.5)/(mass*J_to_ev) * delta_t;
                }
            }
        }
    }
    else if (ensemble == "NVE")
    {
        for (int i = 0; i < natoms; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                atoms[i].vel[k] = atoms[i].vel[k] + (pre1_force[i][k]*NA*0.1*0.5)/(mass*J_to_ev) * delta_t;
            }
        }
    }
    else{
        cout << "please enter valid ensemble name" << endl;
        exit(0);
    }

    return pot_energy;
}