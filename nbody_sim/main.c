#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cell.h"
#include "body.h"
#include "initialize.h"
#include "solver.h"

/*
Author: Nicola Grenon Vinci
*/

int main() { // data

    FILE * out;
    out = fopen("data/2_bodies.dat", "w"); // Output file
    if(out== NULL) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    // System parameters
    int num_bodies = 1000000;

    int nx = 40;
    int ny = 40;
    int nz = 40;

    double xrange = 100;
    double yrange = 100;
    double zrange = 100;

    float t = 1000;
    float cur_t = 0.0;
    float dt = 1;

    Cell *** space; // 3d array of cells
    space = Cell_InitSpace(nx, ny, nz); // Initial cell space and link neighbours

    Body * bodies;
    bodies = InitializeRandom(num_bodies, nx, ny, nz, xrange, yrange, zrange); // Initialize the n-body system
    Print_Bodies(out, bodies, num_bodies);


    Cell *current;

    while (cur_t < t) {

        printf("time %lf\n", cur_t);
        Space_Density(space, bodies, num_bodies, nx, ny, nz, xrange, yrange, zrange); // Density density
        Potential(space, nx, ny, nz, xrange, yrange, zrange); // Potential relaxation
        Force(bodies, num_bodies); // Linear integration of potential
        Evolve(bodies, num_bodies, dt); // Apply force to bodies
        if ((int) floor(cur_t) % 100 == 0)
            Print_Bodies(out, bodies, num_bodies);
        cur_t += dt;

    }

    free(space);
    free(bodies);

    fclose(out);

    return 0;

}
