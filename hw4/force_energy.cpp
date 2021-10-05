#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string.h>
#include <iomanip>
#include <math.h>

using namespace std;

ifstream infile;
ofstream outfile;

int natoms;string geo_path = ""; double r_cut = 0.0 ; double extra_cut = 0.0; int neighbor_n = 0; //input parameters

double epsilon;double sigma; //input parameters for L-J potential

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
        else if (title == "epsilon")
        {
            p = strtok(NULL,d);
            epsilon = atof(p);
        }
        else if (title == "sigma")
        {
            p = strtok(NULL,d);
            sigma = atof(p);
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
    int nei_num;
    int *nei_list = new int[nei_num];
    // declare function
    void setpos(double position[3]);
    void setvel(double velocity[3]);
    // void setneighbor_num(int neighbor_num);
    // void setneighbor_list(int *neighbot_list);
};


void Atom::setpos(double position[3]){
    memcpy(pos,position,sizeof(pos));
}

void Atom::setvel(double velocity[3]){
    memcpy(vel,velocity,sizeof(vel));
}


Atom *atoms = new Atom[900];

void set_atoms(){
    infile.open("geo.in",ios::in);
    const char *startline = "\%ATOMIC_POSTION";
    const char *middleline = "\%ATOMIC_VELOCITY";
    char buf[1024];

    do
    {
        infile.getline(buf,sizeof(buf));
    } while (strstr(buf,startline) == NULL);

    int ind = 0;
    while (infile.getline(buf,sizeof(buf)))
    {
        double poslist[3];
        if (strstr(buf,middleline) != NULL)
        {
            break;
        }
        
        string id_name;
        const char *d = "\t";
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
        poslist[pos] = A_num;
        pos ++;
        }while(p);
        atoms[ind].index = ind;
        atoms[ind].ID = id_name;
        atoms[ind].setpos(poslist);
        ind++;
    };

    ind = 0;
    while (infile.getline(buf,sizeof(buf)))
    {   
        double vellist[3];
        const char *d = "\t";
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
        vellist[pos] = A_num;
        pos ++;
        }while(p);
        atoms[ind].setvel(vellist);
        ind++;
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

void set_neighlist(){
    int nlist[natoms]; 
    int list[natoms][neighbor_n];
    for (int i = 0; i < natoms; i++)
    {   
        nlist[i] = 0;
        for (int j = 0; j < natoms; j++)
        {
            if (j == i)
            {
                continue;
            }
            
            double dist = distance(atoms[i].pos,atoms[j].pos);
            if (dist <= (r_cut + extra_cut))
            {
                list[i][nlist[i]] = j;
                nlist[i]++;
            }
        }
        atoms[i].nei_num = nlist[i];
        atoms[i].nei_list = list[i];
    }

}

double LJ_potential(double alist[3],double blist[3]){
    double u;
    double r_ab;
    double tem;
    double tem_cut;
    r_ab = distance(alist,blist);
    tem = pow(sigma/r_ab,6);
    tem_cut = pow(sigma/r_cut,6);
    if (r_ab > r_cut)
    {
        u = 0;
    }else{
        u = 4*epsilon*(pow(tem,2)-tem) - 4*epsilon*(pow(tem_cut,2)-tem_cut);
    }
    return u;
}

double LJ_force(Atom atom1){
    double force = 0.0;
    
    return force;
}


double energy(Atom atom1){
    double energy = 0.0;
    for (int i = 0; i < atom1.nei_num; i++)
    {
        energy = energy + LJ_potential(atom1.pos,atoms[atom1.nei_list[i]].pos);
    }
    return energy;
}


int main() {
    initialize();
    set_atoms();
    set_neighlist();
    cout << signbit(-0.2) << endl;
    cout << energy(atoms[13]) << endl; //test
       
    return 0;
}