#ifndef POS_DISTANCE_H
#define POS_DISTANCE_H

//compute the distance between two coordinates
double single_distance(double alist[3], double blist[3]);

//compute the distance between two coordinates under PBC
double pos_distance(double alist[3], double blist[3]);

#endif