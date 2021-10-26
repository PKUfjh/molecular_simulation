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

double **read_in(string filename,const char *startline){
    ifstream infile;
    infile.open(filename,ios::in);
    double **list = new double *[natoms];
    for (int i = 0; i < natoms; i++)
    {
        list[i] = new double [3];
    }

    int ind = 0;
    char buf[1024];
    do
    {
        infile.getline(buf,sizeof(buf));
    } while (strstr(buf,startline) == NULL); //read input file until the startline

    while (infile.getline(buf,sizeof(buf)))
    {
        if (ind >= natoms) //do the first loop until all atoms are read
        {
            break;
        }
        
        string id_name;
        const char *d = " \t";
        char *p= strtok(buf,d);
        if (p == NULL)
        {   
            continue;
        }
        
        id_name = p;

        int pos = 0;
        do
        {   
        double A_num;
        p = strtok(NULL,d);

        if (p == NULL)
        {
            break;
        }
        A_num = atof(p);
        list[ind][pos] = A_num;
        pos ++;
        }while(p);
        ind++;
    };
    infile.close();
    return list;
}

void mdrun(int STEP,double delta_t){
    ofstream outfile;
    ifstream infile;
    fstream inoutfile;

    if (STEP == -1)
    {
        outfile.open("position.txt",ios::out);
        outfile << "STEP -1" << endl;
        for (int i = 0; i < natoms; i++)
        {
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << atoms[i].pos[0] - atoms[i].vel[0]*delta_t << "\t";
            outfile << atoms[i].pos[1] - atoms[i].vel[1]*delta_t  << "\t";
            outfile << atoms[i].pos[2]  - atoms[i].vel[2]*delta_t  << endl;
        }
        outfile.close();
    }
    
    else if (STEP == 0)
    {
        double total_energy = 0;
        double kinetic_energy = 0;
        double pot_energy = 0;
        double temperature = 0;
        outfile.open("position.txt",ios::app);
        outfile << "STEP 0" << endl;
        for (int i = 0; i < natoms; i++)
        {
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << atoms[i].pos[0] << "\t" << atoms[i].pos[1] << "\t" << atoms[i].pos[2] << endl;
        }
        outfile.close();
        outfile.open("velocity.txt",ios::out);
        outfile << "STEP 0" << endl;
        for (int i = 0; i < natoms; i++)
        {
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << atoms[i].vel[0] << "\t" << atoms[i].vel[1] << "\t" << atoms[i].vel[2] << endl;
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
            outfile << force[1] << "\t" << force[2] << "\t" << force[3] << endl; //output the forces of each atom
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
        double **pos1;
        pos1 = new double *[natoms];
        for (int i = 0; i < natoms; i++)
        {
            pos1[i] = new double [3];
        }
        double **pos2;
        pos2 = new double *[natoms];
        for (int i = 0; i < natoms; i++)
        {
            pos1[i] = new double [3];
        }
        double **force;
        force = new double *[natoms];
        for (int i = 0; i < natoms; i++)
        {
            force[i] = new double [3];
        }
        
        
        string mark = "STEP "+to_string(STEP-1);
        const char *startline = mark.c_str();
        memcpy(force,read_in("force.txt",startline),natoms*3*sizeof(double));
        
        string mark1 = "STEP "+to_string(STEP-2);
        string mark2 = "STEP "+to_string(STEP-1);
        const char *pos1line = mark1.c_str();
        const char *pos2line = mark2.c_str();
        
        cout << read_in("force.txt",startline)[0][0] << endl;
        memcpy(pos1,read_in("position.txt",pos1line),natoms*3*sizeof(double));
        memcpy(pos2,read_in("position.txt",pos2line),natoms*3*sizeof(double));

        outfile.open("position.txt",ios::app);
        outfile << "STEP " << STEP << endl;
        for (int i = 0; i < natoms; i++)
        {   
            double poslist[3];
            for (int k = 0; k < 3; k++)
            {
                poslist[k] = 2*pos2[i][k] - pos1[i][k] + force[i][k]/mass * pow(delta_t,2);
            }
            restrict_in_box(poslist);
            atoms[i].setpos(poslist);
            outfile << atoms[i].ID << "\t";
            outfile.precision(12);
            outfile << atoms[i].pos[0] << "\t" << atoms[i].pos[1] << "\t" << atoms[i].pos[2] << endl;
        }
        
        //release the memory allocated to nei_list
        for (int j = 0; j < natoms; j++)
        {
            delete[] pos1[j];
        }
        delete[] pos1;
        for (int j = 0; j < natoms; j++)
        {
            delete[] pos2[j];
        }
        delete[] pos2;
        for (int j = 0; j < natoms; j++)
        {
            delete[] force[j];
        }
        delete[] force;

        outfile.close();
    }


}