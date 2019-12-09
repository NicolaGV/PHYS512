#ifndef CELL_H
#define CELL_H

typedef struct node Cell;

#include "body.h"



typedef struct node {

    double rho; // density
    double mass; // mass contained, helps with potential
    double pot; // potential
    int *int_pos; // grid x, y, z //debug

    // neighbours
    struct node **nbr; //-dx,+dx,-dy,+dy,-dz,+dz

} Cell;

Cell *** Cell_3D_Alloc(int nx, int ny, int nz);

Cell ***Cell_InitSpace(int nx, int ny, int nz);

void Cell_LinkSpace(Cell ***Space, int nx, int ny, int nz);

void Cell_LinkSpace_Periodic(Cell ***Space, int nx, int ny, int nz);

void Space_Density(Cell *** Space, Body * bodies, int num_bodies, int nx, int ny, int nz, double xrange, double yrange, double zrange);


#endif
