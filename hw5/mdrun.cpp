#include <math.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "pos_distance.h"
#include "parameters.h"
#include "force_energy.h"
#include "kin_energy.h"

double *mdrun(double STEP){
    ofstream outfile;
    double total_energy = 0;
    double kinetic_energy = 0;
    double pot_energy = 0;
    double temperature = 0;
    static double list[4] = {total_energy,kinetic_energy,pot_energy,temperature};
    if (STEP == 0)
    {
        outfile.open("position.txt",ios::out);
        outfile << "STEP 0" << endl;
        for (int i = 0; i < natoms; i++)
        {
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << atoms[i].pos[0] << "\t";
            outfile << atoms[i].pos[1] << "\t";
            outfile << atoms[i].pos[2] << endl;
        }
        outfile.close();
        outfile.open("velocity.txt",ios::out);
        outfile << "STEP 0" << endl;
        for (int i = 0; i < natoms; i++)
        {
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << atoms[i].vel[0] << "\t";
            outfile << atoms[i].vel[1] << "\t";
            outfile << atoms[i].vel[2] << endl;
        }
        outfile.close();
        outfile.open("force.txt",ios::out);
        outfile << "STEP 0" << endl;
        //output the total force of each atom
        for (int i = 0; i < natoms; i++)
        {
            double force[4];
            memcpy(force,energy_force(atoms[i]),sizeof(force));
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << force[1] << "\t";
            outfile << force[2] << "\t";
            outfile << force[3] << endl; //output the forces of each atom
            pot_energy += force[0];
        }
        outfile.close();
        kinetic_energy = kin_energy();
        total_energy = pot_energy + kinetic_energy;
        temperature = kinetic_energy*2/(3*Bolzmann_k*natoms*J_to_ev);
        outfile.open("run.log",ios::out);
        outfile.precision(12);\
        outfile << "STEP 0" << endl;
        outfile <<"total kinetic energy(eV): " << kinetic_energy << endl; //output the total potential energy
        outfile <<"total potential energy(eV): " << pot_energy << endl; //output the total potential energy
        outfile <<"total energy(eV): " << total_energy << endl;
        outfile <<"Temperature (K): " << temperature << endl;
        outfile.close();
    }
    else{
        return list;
    }
    
    return list;

}