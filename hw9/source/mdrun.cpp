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
#include <random>
#include <chrono>

void mdrun(int STEP){
    ofstream outfile;
    ifstream infile;
    fstream inoutfile;
    
    double total_energy = 0;
    double kinetic_energy = 0;
    double pot_energy = 0;
    double temperature = 0;
    // 从epoch（1970年1月1日00:00:00 UTC）开始经过的纳秒数，unsigned类型会截断这个值
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    // 第一个参数为高斯分布的平均值，第二个参数为标准差
    double gauss_sigma = sqrt(Bolzmann_k*T_res*NA*1000/mass)*0.01;
    std::normal_distribution<double> normal(0.0, gauss_sigma);
    //均匀分布产生碰撞概率
    std::uniform_real_distribution<double> uniform(0.0,1.0); 
    if (STEP == 0)
    {
        for (int i = 0; i < natoms; i++)
        {
            memcpy(pre1_pos[i],atoms[i].pos,3*sizeof(double));
        }
        for (int i = 0; i < natoms; i++)
        {
            double force[4];
            memcpy(force,energy_force(atoms[i]),sizeof(force));
            memcpy(pre1_force[i],force+1,3*sizeof(double));
            pot_energy += force[0];
        }
        kinetic_energy = kin_energy();
        total_energy = pot_energy + kinetic_energy;
        temperature = kinetic_energy*2/(3*Bolzmann_k*natoms*J_to_ev);
    }
    else{
        if (MD_alg == 1)
        {
            if (STEP == 1)
            {
                for (int i = 0; i < natoms; i++)
                {   
                    double poslist[3];
                    for (int k = 0; k < 3; k++)
                    {
                        poslist[k] = atoms[i].pos[k] + atoms[i].vel[k] * delta_t + (pre1_force[i][k]*NA*0.1*0.5)/(mass*J_to_ev) * pow(delta_t,2);
                    }
                    restrict_in_box(poslist);
                    atoms[i].setpos(poslist);
                }
            }
            else{
                for (int i = 0; i < natoms; i++)
                {   
                    double poslist[3];
                    for (int k = 0; k < 3; k++)
                    {
                        poslist[k] = 2*pre1_pos[i][k] - pre2_pos[i][k] +  (pre1_force[i][k]*NA*0.1)/(mass*J_to_ev) * pow(delta_t,2);
                    }
                    restrict_in_box(poslist);
                    atoms[i].setpos(poslist);
                }
            }
            
            for (int i = 0; i < natoms; i++)
            {
                double force[4];
                memcpy(force,energy_force(atoms[i]),sizeof(force));
                memcpy(pre1_force[i],force+1,3*sizeof(double));
                pot_energy += force[0];
            }


            for (int i = 0; i < natoms; i++)
            {
                for (int k = 0; k < 3; k++)
                {
                    atoms[i].vel[k] = shortest(atoms[i].pos,pre1_pos[i])[k+1]/delta_t + (pre1_force[i][k]*NA*0.1*0.5)/(mass*J_to_ev) * delta_t;
                }
                memcpy(pre2_pos[i],pre1_pos[i],3*sizeof(double));
                memcpy(pre1_pos[i],atoms[i].pos,3*sizeof(double));
            }
            kinetic_energy = kin_energy();
            total_energy = pot_energy + kinetic_energy;
            temperature = kinetic_energy*2/(3*Bolzmann_k*natoms*J_to_ev);
        }
    else if (MD_alg == 2)
    {
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
            memcpy(pre2_pos[i],pre1_pos[i],3*sizeof(double));
            memcpy(pre1_pos[i],atoms[i].pos,3*sizeof(double));
        }
        kinetic_energy = kin_energy();
        total_energy = pot_energy + kinetic_energy;
        temperature = kinetic_energy*2/(3*Bolzmann_k*natoms*J_to_ev);
    }
    }
        
        
    //output MD run information for every 2 steps
    if (STEP % output_step == 0)
    {   
        string mode;
        if (STEP == 0)
        {
            outfile.open("../position.txt",ios::out);
        }
        else{
            outfile.open("../position.txt",ios::app);
        }
        outfile << "STEP " << STEP << endl;
        for (int i = 0; i < natoms; i++)
        {
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << atoms[i].pos[0] << "\t" << atoms[i].pos[1] << "\t" << atoms[i].pos[2] << endl;
        }
        outfile.close();

        if (STEP == 0)
        {
            outfile.open("../velocity.txt",ios::out);
        }
        else{
            outfile.open("../velocity.txt",ios::app);
        }
        outfile << "STEP " << STEP << endl;
        for (int i = 0; i < natoms; i++)
        {
        outfile << atoms[i].ID << "\t";
        outfile.precision(12);
        outfile << atoms[i].vel[0] << "\t" << atoms[i].vel[1] << "\t" << atoms[i].vel[2] << endl;
        }
        outfile.close();
        
        if (STEP == 0)
        {
            outfile.open("../force.txt",ios::out);
        }
        else{
            outfile.open("../force.txt",ios::app);
        }
        outfile << "STEP " << STEP << endl;
        for (int i = 0; i < natoms; i++)
        {
        outfile << atoms[i].ID << "\t";
        outfile.precision(12);
        outfile << pre1_force[i][0] << "\t" << pre1_force[i][1] << "\t" << pre1_force[i][2] << endl; //output the forces of each atom
        }
        outfile.close();
        
        if (STEP == 0)
        {
            outfile.open("../run.log",ios::out);
        }
        else{
            outfile.open("../run.log",ios::app);
        }
        outfile.precision(12);
        outfile << "STEP " << STEP << endl;
        outfile <<"total kinetic energy(eV): " << kinetic_energy << endl; //output the total potential energy
        outfile <<"total potential energy(eV): " << pot_energy << endl; //output the total potential energy
        outfile <<"total energy(eV): " << total_energy << endl;
        outfile <<"Temperature (K): " << temperature << endl;
        outfile.close();
        if (STEP == 0)
        {
            outfile.open("../temperature.log",ios::out);
        }
        else{
            outfile.open("../temperature.log",ios::app);
        }
        outfile << temperature << endl;
        outfile.close();
    } 
}