#include <iostream>
#include <string.h>
#include "global.h"

using namespace std;

int main(){
    Atom atom;
    atom.ID = "dwwd";
    double pos[3] = {32.2332,434333,4343};
    atom.setpos(pos);
    cout << atom.pos[0] <<endl;

    return 0;
}