#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <math.h>

using namespace std;

ifstream infile;
ofstream outfile;

//function which takes the input coordinate, and output the wave position
void write_wave(double A, double k, double phi, double a1, double a2, double a3,string filename){
    outfile.open(filename,ios::app);
    // xyz file for transverse wave
    if (filename == "BN_trans.xyz")
    {
        outfile << a1 +  A*cos(k* a3 + phi) << "\t";
        outfile << a2 << "\t";
        outfile << a3 ;
    }
    // xyz file for longitudial wave
    else if (filename == "BN_long.xyz")
    {
        outfile << a1 << "\t";
        outfile << a2 << "\t";
        outfile << a3 +  A*cos(k* a3 + phi) ;
    }
    else{
        cout << "wrong name" << endl;
    }
}


int main() {
    string filename = "BN_long.xyz";

    infile.open("BN_1024atoms.xyz",ios::in);

    char buf[2024];

    const char *startline = "(8,0) BN Nanotube (1,1,32) replication";

    //read until the atomic position information
    do
    {
        infile.getline(buf,sizeof(buf));
    } while (strstr(buf,startline) == NULL);


    // write the title of the output file
    outfile.open(filename,ios::out);
    outfile << 1024 << endl;
    outfile << "(8,0) BN Nanotube (1,1,32) replication" << endl;
    outfile.close();

    while (infile.getline(buf,sizeof(buf)))
    {   
        outfile.open(filename,ios::app);
        const char *d = " \t";
        char *p= strtok(buf,d);

        outfile << p << "\t";
        outfile.close();

        double numlist[3] = {1,2,3};

        double A_num;

        // save three atomic coordinates into a number array
        for (int i = 0; i < 3; i++)
        {
            p = strtok(NULL,d);
            A_num = atof(p);
            numlist[i] = A_num;
        }

        
        write_wave(0.8, 0.5, 0.5, numlist[0], numlist[1], numlist[2],filename);
          
    outfile << "\n";
    outfile.close();
    };

    return 0;
}