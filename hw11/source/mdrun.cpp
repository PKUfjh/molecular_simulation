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
#include "verlet.h"
#include "rdf.h"
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
            pot_energy = verlet(STEP);
            kinetic_energy = kin_energy();
            total_energy = pot_energy + kinetic_energy;
            temperature = kinetic_energy*2/(3*Bolzmann_k*natoms*J_to_ev);
        }
        else if (MD_alg == 2)
        {
            pot_energy = velo_verlet(STEP);
            kinetic_energy = kin_energy();
            total_energy = pot_energy + kinetic_energy;
            temperature = kinetic_energy*2/(3*Bolzmann_k*natoms*J_to_ev);
        }
    }
    //calculate MSD information
    if (cal_msd == 1)
    {
        double MSD = msd();
        //output MSD information
        if (STEP % msd_interval == 0)
        {
            if (STEP == 0)
            {
                outfile.open("../diffusion.txt",ios::out);
            }
            else{
                outfile.open("../diffusion.txt",ios::app);
            }
            outfile << MSD << endl;
            outfile.close();
        }
    }

    //calculate the radial distribution function
    if (cal_rdf == 1)
    {
        if (STEP >= rdf_geo1 && STEP <= rdf_geo2)
        {
            if ((STEP-rdf_geo1)%rdf_interval == 0)
            {
                for (int i = 0; i < 85; i++)
                {
                    double rad = i*0.1+0.005;
                    rdflist[i] += rdf(rad);
                }
                if (STEP == rdf_geo2)
                {
                    for (int i = 0; i < 85; i++)
                    {
                        rdflist[i] = 1.0*rdflist[i]/(rdf_geo2-rdf_geo1);
                    }
                }
            }
        }
        //output the radial distribution function
        if (STEP == rdf_geo2){
            outfile.open("../rdf.txt",ios::out);
            for (int i = 0; i < 85; i++)
            {
                outfile << i*0.1+0.005  << "\t" << rdflist[i] << endl;
            }
            outfile.close();
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
        outfile << natoms << endl;
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
    for (int i = 0; i < natoms; i++) {
        memcpy(pre2_pos[i],pre1_pos[i],3*sizeof(double));
        memcpy(pre1_pos[i],atoms[i].pos,3*sizeof(double));
    }
    
}