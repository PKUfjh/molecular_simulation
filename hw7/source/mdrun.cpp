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

void mdrun(int STEP){
    ofstream outfile;
    ifstream infile;
    fstream inoutfile;
    
    if (STEP == 0)
    {
        double total_energy = 0;
        double kinetic_energy = 0;
        double pot_energy = 0;
        double temperature = 0;
        outfile.open("../position.txt",ios::out);
        outfile << "STEP 0" << endl;
        for (int i = 0; i < natoms; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                pre1_pos[i][k] = atoms[i].pos[k];
            }
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << atoms[i].pos[0] << "\t" << atoms[i].pos[1] << "\t" << atoms[i].pos[2] << endl;
        }
        outfile.close();
        outfile.open("../velocity.txt",ios::out);
        outfile << "STEP 0" << endl;
        for (int i = 0; i < natoms; i++)
        {
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << atoms[i].vel[0] << "\t" << atoms[i].vel[1] << "\t" << atoms[i].vel[2] << endl;
        }
        outfile.close();
        outfile.open("../force.txt",ios::out);
        outfile << "STEP 0" << endl;
        //output the total force of each atom
        for (int i = 0; i < natoms; i++)
        {
            double force[4];
            memcpy(force,energy_force(atoms[i]),sizeof(force));
            for (int k = 0; k < 3; k++)
            {
                pre1_force[i][k] = force[k+1];
            }
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << force[1] << "\t" << force[2] << "\t" << force[3] << endl; //output the forces of each atom
            pot_energy += force[0];
        }
        outfile.close();
        kinetic_energy = kin_energy();
        total_energy = pot_energy + kinetic_energy;
        temperature = kinetic_energy*2/(3*Bolzmann_k*natoms*J_to_ev);
        outfile.open("../run.log",ios::out);
        outfile.precision(12);\
        outfile << "STEP 0" << endl;
        outfile <<"total kinetic energy(eV): " << kinetic_energy << endl; //output the total potential energy
        outfile <<"total potential energy(eV): " << pot_energy << endl; //output the total potential energy
        outfile <<"total energy(eV): " << total_energy << endl;
        outfile <<"Temperature (K): " << temperature << endl;
        outfile.close();
    }
    else{
        double total_energy = 0;
        double kinetic_energy = 0;
        double pot_energy = 0;
        double temperature = 0;

        if (STEP == 1)
        {
            outfile.open("../position.txt",ios::app);
            outfile << "STEP " << STEP << endl;
            for (int i = 0; i < natoms; i++)
            {   
                double poslist[3];
                for (int k = 0; k < 3; k++)
                {
                    poslist[k] = atoms[i].pos[k] + atoms[i].vel[k] * delta_t + 1/2 * (pre1_force[i][k]*NA*0.1)/(mass*J_to_ev) * pow(delta_t,2);
                }
                restrict_in_box(poslist);
                atoms[i].setpos(poslist);
                outfile << atoms[i].ID << "\t";
                outfile.precision(12);
                outfile << atoms[i].pos[0] << "\t" << atoms[i].pos[1] << "\t" << atoms[i].pos[2] << endl;
            }
            outfile.close();
        }
        else{
            outfile.open("../position.txt",ios::app);
            outfile << "STEP " << STEP << endl;
            for (int i = 0; i < natoms; i++)
            {   
                double poslist[3];
                for (int k = 0; k < 3; k++)
                {
                    poslist[k] = 2*pre1_pos[i][k] - pre2_pos[i][k] +  (pre1_force[i][k]*NA*0.1)/(mass*J_to_ev) * pow(delta_t,2);
                }
                restrict_in_box(poslist);
                atoms[i].setpos(poslist);
                outfile << atoms[i].ID << "\t";
                outfile.precision(12);
                outfile << atoms[i].pos[0] << "\t" << atoms[i].pos[1] << "\t" << atoms[i].pos[2] << endl;
            }
            outfile.close();
        }
        
        outfile.open("../force.txt",ios::app);
        outfile << "STEP " << STEP << endl;
        //output the total force of each atom
        for (int i = 0; i < natoms; i++)
        {
            double force[4];
            memcpy(force,energy_force(atoms[i]),sizeof(force));
            for (int k = 0; k < 3; k++)
            {
                pre1_force[i][k] = force[k+1];
            }
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << force[1] << "\t" << force[2] << "\t" << force[3] << endl; //output the forces of each atom
            pot_energy += force[0];
        }
        outfile.close();

        outfile.open("../velocity.txt",ios::app);
        outfile << "STEP " << STEP << endl;
        for (int i = 0; i < natoms; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                atoms[i].vel[k] = shortest(atoms[i].pos,pre1_pos[i])[k+1]/delta_t + 1/2 *  (pre1_force[i][k]*NA*0.1)/(mass*J_to_ev) * delta_t;
            }
            for (int k = 0; k < 3; k++)
            {
                pre2_pos[i][k] = pre1_pos[i][k];
                pre1_pos[i][k] = atoms[i].pos[k];
            }
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << atoms[i].vel[0] << "\t" << atoms[i].vel[1] << "\t" << atoms[i].vel[2] << endl;
        }
        outfile.close();

        
        kinetic_energy = kin_energy();
        total_energy = pot_energy + kinetic_energy;
        temperature = kinetic_energy*2/(3*Bolzmann_k*natoms*J_to_ev);
        outfile.open("../run.log",ios::app);
        outfile.precision(12);\
        outfile << "STEP " << STEP << endl;
        outfile <<"total kinetic energy(eV): " << kinetic_energy << endl; //output the total potential energy
        outfile <<"total potential energy(eV): " << pot_energy << endl; //output the total potential energy
        outfile <<"total energy(eV): " << total_energy << endl;
        outfile <<"Temperature (K): " << temperature << endl;
        outfile.close();


    } 
}