#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <iomanip>
#include <math.h>

using namespace std;

ifstream infile;
ofstream outfile;

int natoms = 0;string geo_path = ""; double r_cut = 0.0 ; double extra_cut = 0.0; int neighbor_n = 0; //input parameters

double atomslist[1024][3];


void initialize(){
    infile.open("input",ios::in);
    char buf[1024];

    while (infile.getline(buf,sizeof(buf)))
    {
        const char *d = " \t";
        char *p= strtok(buf,d);
        if (p == NULL)
        {
            continue;
        }
        string title;
        title = p;
        
        if (title == "natoms")
        {
            p = strtok(NULL,d);
            natoms = atof(p);
        } 
        else if (title == "geo_path")
        {
            p = strtok(NULL,d);
            geo_path = p;
        }else if (title == "r_cut")
        {
            p = strtok(NULL,d);
            r_cut = atof(p);
        }else if (title == "extra_cut")
        {
            p = strtok(NULL,d);
            extra_cut = atof(p);
        }
        else if (title == "neighbor_n")
        {
            p = strtok(NULL,d);
            neighbor_n = atof(p);
        }
        else
        {
            continue;
        }
    }
    infile.close();
}

class Atom
{
private:
    /* data */
public:
    string ID;
    int index;
    double pos[3];
    double vel[3];
    double list[];
    // declare function
    void set(string ID_name,int index_num);
    void setpos(double position[3]);
    void setvel(double velocity[3]);
};

void Atom::set(string ID_name,int index_num){    
    ID = ID_name;
    index = index_num;
}

void Atom::setpos(double position[3]){
    memcpy(pos,position,sizeof(pos));
}

void Atom::setvel(double velocity[3]){
    memcpy(vel,velocity,sizeof(vel));
}



void savepos(){
    infile.open("geo.in",ios::in);
    const char *startline = "\%ATOMIC_POSTION";
    const char *middleline = "\%ATOMIC_VELOCITY";
    char buf[1024];

    do
    {
        infile.getline(buf,sizeof(buf));
    } while (strstr(buf,startline) == NULL);

    int index = 0;
    while (infile.getline(buf,sizeof(buf)))
    {
        if (strstr(buf,middleline) != NULL)
        {
            break;
        }
        
        const char *d = " \t";
        char *p= strtok(buf,d);

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
        atomslist[index][pos] = A_num;
        pos ++;
        }while(p);
        index++;
    };


}

double distance(double alist[3], double blist[3]){
    double dis = 0.0;
    for (int i = 0; i < 3; i++)
    {
        dis += pow(alist[i]-blist[i],2);
    }

    dis = sqrt(dis);

    return dis;
}


int main() {
    initialize();
    savepos();
    int nlist[natoms]; 
    int list[natoms][neighbor_n];
    for (int i = 0; i < natoms; i++)
    {   
        nlist[i] = 0;
        for (int j = 0; j < natoms; j++)
        {
            double dist = distance(atomslist[i],atomslist[j]);
            if (dist <= (r_cut + extra_cut))
            {
                nlist[i]++;
                list[i][nlist[i]] = j;
            }
            
        }
        
    }
    outfile.open("geo12.out",ios::out);
    outfile << "neighbor list for #12 atom" << endl;
    for (int i = 0; i < nlist[11]; i++)
    {   
        int neighbor_num = list[11][i];
        outfile << list[11][i] << "\t";
        for (int i = 0; i < 3; i++)
        {
            outfile << atomslist[neighbor_num][i] << "\t";
        }
        outfile << "\n";
        
    }
    
    return 0;
}