#ifndef MDRUN_H
#define MDRUN_H

//read in from previous MD run
double **read_in(string filename,int STEP);

/*molecular dynamics calculation, output atomic position, velocity, forces at given step, 
also output the total energy, potential energy, kinetic energy and temperature at given step.*/
void mdrun(int STEP);

#endif