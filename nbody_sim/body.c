#include <stdio.h>
#include <stdlib.h>

#include "body.h"

void Print_Bodies(FILE * out, Body * bodies, int body_num) {


    Body *current;

    // nearest point
    int i;
    for(i = 0; i < body_num; i++) {
        current = &bodies[i];
        fprintf(out, "%lf %lf %lf\n", current->p[0], current->p[1], current->p[2]);

    }


    fprintf(out, "\n\n");

    return;

}
