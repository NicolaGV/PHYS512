#ifndef BODY_H
#define BODY_H

typedef struct particle Body;

#include "cell.h"

typedef struct particle{

    double mass;
    double *p; // position x, y, z
    double *v; // velocity x, y, z
    double *f; // current force applied fx, fy, fz

    struct node ** cells; // cells containins mass density
    double * portion; // portion of density assigned to cells
    // struct node * cell; // cell containing center

} Body;

void Print_Bodies(FILE * out, Body * bodies, int body_num);

#endif // BODY_H
