#ifndef POS_DISTANCE_H
#define POS_DISTANCE_H

//compute the distance between two coordinates
double single_distance(double alist[3], double blist[3]);

//compute the shortest distance under PBC
double *shortest(double alist[3],double blist[3]);

//restrict the atoms coordinates in the box
void restrict_in_box(double alist[3]);

#endif