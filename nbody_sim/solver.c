#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cell.h"
#include "body.h"

void Potential(Cell *** Space, int nx, int ny, int nz, double xrange, double yrange, double zrange) {

    double POTENTIAL_FACTOR = 8.3855391*pow(10, -10);
    Cell *current;


    // gauss-seidel
    int it = 0;
    int num_it = 100;

    double xh = xrange/(nx-1);
    double yh = xrange/(ny-1);
    double zh = xrange/(nz-1);

    int x, y, z;
    while (it != num_it) {
        for(x = 0; x < nx; x++) {
            for(y = 0; y < ny; y++) {
                for (z = 0; z < nz; z++) {
                    current = &Space[x][y][z];
                    current->pot = 0.0;

                    current->pot += 1.0/6.0*(current->nbr[0]->pot + current->nbr[1]->pot + current->nbr[2]->pot
                                     + current->nbr[3]->pot + current->nbr[4]->pot + current->nbr[5]->pot);

                    current->pot -= 1.0/6.0*current->rho*(pow(xh, 2)+ pow(yh, 2) + pow(zh, 2));

                }
            }
        }
        it += 1;
    }
}

void Force(Body *bodies, int num_bodies, double * energy) {

    Body *current_b;
    Cell *current_c;

    int i;
    int j;
    for(i = 0; i < num_bodies; i++) {

        current_b = &bodies[i];

        // reset for current iteration
        current_b->f[0]=0.0;
        current_b->f[1]=0.0;
        current_b->f[2]=0.0;

        // iterate force through cloud-in-cell
        for (j = 0; j < 8; j++) {
            current_c = current_b->cells[j];
            current_b->f[0] -= current_b->portion[j] * (current_b->mass)*0.5*(current_c->nbr[1]->pot - current_c->nbr[0]->pot);
            current_b->f[1] -= current_b->portion[j] * (current_b->mass)*0.5*(current_c->nbr[3]->pot - current_c->nbr[2]->pot);
            current_b->f[2] -= current_b->portion[j] * (current_b->mass)*0.5*(current_c->nbr[5]->pot - current_c->nbr[4]->pot);

            // Potential energy
            *energy -= current_b->portion[j] * current_c->pot;
        }

    /*

    // Nearest neighbour
        current = &bodies[i];
        current->f[0] = -(current->mass)*0.5*(current->cell->nbr[1]->pot - current->cell->nbr[0]->pot);
        current->f[1] = -(current->mass)*0.5*(current->cell->nbr[3]->pot - current->cell->nbr[2]->pot);
        current->f[2] = -(current->mass)*0.5*(current->cell->nbr[5]->pot - current->cell->nbr[4]->pot);
    */

    }


}

// We have the force, we now change the velocity and the position of the bodies
void Evolve(Body *bodies, int num_bodies, float dt, double * energy) {

    Body *current;

    int i;
    for(i = 0; i < num_bodies; i++) {
        current = &bodies[i];

        current->v[0] += (current->f[0])/(current->mass)*dt;
        current->v[1] += (current->f[1])/(current->mass)*dt;
        current->v[2] += (current->f[2])/(current->mass)*dt;

        current->p[0] += current->v[0]*dt;
        current->p[1] += current->v[1]*dt;
        current->p[2] += current->v[2]*dt;

        // Kinetic energy
        *energy += current->v[0]*current->mass*current->mass;
        *energy += current->v[1]*current->mass*current->mass;
        *energy += current->v[2]*current->mass*current->mass;
    }
}

void EvolvePeriodic(Body * bodies, int num_bodies, float dt, double xrange, double yrange, double zrange,  double * energy) {
        Body *current;

    int i;
    for(i = 0; i < num_bodies; i++) {
        current = &bodies[i];

        current->v[0] += (current->f[0])/(current->mass)*dt;
        current->v[1] += (current->f[1])/(current->mass)*dt;
        current->v[2] += (current->f[2])/(current->mass)*dt;

        current->p[0] += current->v[0] * dt;
        current->p[1] += current->v[1] * dt;
        current->p[2] += current->v[2] * dt;

        // Periodicity
        if (current->p[0] < 0)
            current->p[0] += xrange;
        if (current->p[0] > xrange)
            current->p[0] -= xrange;
        if (current->p[1] < 0)
            current->p[1] += yrange;
        if (current->p[1] > yrange)
            current->p[1] -= yrange;
        if (current->p[2] < 0)
            current->p[2] += zrange;
        if (current->p[2] > zrange)
            current->p[2] -= zrange;

        // Kinetic energy
        *energy += current->v[0]*current->mass*current->mass;
        *energy += current->v[1]*current->mass*current->mass;
        *energy += current->v[2]*current->mass*current->mass;

    }
}
