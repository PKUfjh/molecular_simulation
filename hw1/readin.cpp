#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <unistd.h>

using namespace std;


int main() {
    ifstream infile;
    ofstream outfile;
    infile.open("../geo.in",ios::in);
    char buff[250];
    getcwd(buff,250);
    string cwd(buff);

    cout << "working direactory" << cwd << endl;

    const char *startline = "\%ATOMIC_POSTION";
    const char *middleline = "\%ATOMIC_VELOCITY";

    char buf[2024];

    do
    {
        infile.getline(buf,sizeof(buf));
    } while (strstr(buf,startline) == NULL);
    

    outfile.open("../geo.out",ios::out);
    outfile << buf << " in Bohr units" << endl;
    outfile.close();


    while (infile.getline(buf,sizeof(buf)))
    {
        outfile.open("../geo.out",ios::app);
        if (strstr(buf,middleline) != NULL)
        {
            outfile << "\n";
            outfile << buf << " in Bohr units" << endl;
            outfile.close();
            continue;
        }
        
        const char *d = " \t";
        char *p= strtok(buf,d);

        outfile << p << "\t";

        do
        {   
        double A_num;
        double Bohr_num;
        p = strtok(NULL,d);

        if (p == NULL)
        {
            break;
        }
        A_num = atof(p);
        Bohr_num = A_num*1.8897161646321;
        outfile.precision(10);
        outfile << Bohr_num << "\t";

        }while(p);

    outfile << "\n";
    outfile.close();
    };

    return 0;
}