#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "body.h"

Body * InitializeRandom_Periodic(int num_bodies, int nx, int ny, int nz, double xrange, double yrange, double zrange) {
    Body * bodies = (Body *) malloc(num_bodies * sizeof(Body));
    Body * current;

    srand ( time(NULL) );


    int i;
    for (i = 0; i < num_bodies; i++) {

        current = &bodies[i];

        current->mass = 1;

        current->p = malloc(sizeof(double)*3);
        current->p[0] = (xrange) * ( (double)rand() / (double)RAND_MAX );
        current->p[1] = (yrange) * ( (double)rand() / (double)RAND_MAX );
        current->p[2] = (zrange) * ( (double)rand() / (double)RAND_MAX );

        current->v = malloc(sizeof(double)*3);
        current->v[0] = 0;
        current->v[1] = 0;
        current->v[2] = 0;

        current->f = malloc(sizeof(double)*3);
        current->f[0] = 0;
        current->f[1] = 0;
        current->f[1] = 0;

        current->cells = malloc(sizeof(Body*)*8);
        current->portion = malloc(sizeof(double)*8);
    }

    return bodies;

}

Body * InitializeRandom(int num_bodies, int nx, int ny, int nz, double xrange, double yrange, double zrange) {

    Body * bodies = (Body *) malloc(num_bodies * sizeof(Body));
    Body * current;

    srand ( time(NULL) );

    int i;
    for (i = 0; i < num_bodies; i++) {

        current = &bodies[i];

        current->mass = 1;

        // random position
        current->p = malloc(sizeof(double)*3);
        current->p[0] = (xrange - 2 * xrange/(nx-1)) * ( (double)rand() / (double)RAND_MAX ) + xrange/(nx-1);
        current->p[1] = (yrange - 2 * yrange/(ny-1)) * ( (double)rand() / (double)RAND_MAX ) + yrange/(ny-1);
        current->p[2] = (zrange - 2 * zrange/(nz-1)) * ( (double)rand() / (double)RAND_MAX ) + zrange/(nz-1);

        current->v = malloc(sizeof(double)*3);
        current->v[0] = 0;
        current->v[1] = 0;
        current->v[2] = 0;

        current->f = malloc(sizeof(double)*3);
        current->f[0] = 0;
        current->f[1] = 0;
        current->f[1] = 0;

        current->cells = malloc(sizeof(Body*)*8);
        current->portion = malloc(sizeof(double)*8);
    }

    return bodies;

}

Body * Initialize_orbit(int num_bodies, int nx, int ny, int nz, double xrange, double yrange, double zrange) {

    Body * bodies = (Body *) malloc(num_bodies * sizeof(Body));
    Body * current;

    current = &bodies[0];

    current->mass = 100;

    current->p = malloc(sizeof(double)*3);
    current->p[0] = 25;
    current->p[1] = 50;
    current->p[2] = 50;

    current->v = malloc(sizeof(double)*3);
    current->v[0] = 0;
    current->v[1] = 0.05;
    current->v[2] = 0;

    current->f = malloc(sizeof(double)*3);
    current->f[0] = 0;
    current->f[1] = 0;
    current->f[1] = 0;

    current->cells = malloc(sizeof(Body*)*8);
    current->portion = malloc(sizeof(double)*8);


    current = &bodies[1];

    current->mass = 100;

    current->p = malloc(sizeof(double)*3);
    current->p[0] = 75;
    current->p[1] = 50;
    current->p[2] = 50;

    current->v = malloc(sizeof(double)*3);
    current->v[0] = 0;
    current->v[1] = -0.05;
    current->v[2] = 0;

    current->f = malloc(sizeof(double)*3);
    current->f[0] = 0;
    current->f[1] = 0;
    current->f[1] = 0;

    current->cells = malloc(sizeof(Body*)*8);
    current->portion = malloc(sizeof(double)*8);

    return bodies;
}

Body * Initialize_One(int num_bodies, int nx, int ny, int nz, double xrange, double yrange, double zrange) {

    Body * bodies = (Body *) malloc(num_bodies * sizeof(Body));
    Body * current;

    current = &bodies[0];

    current->mass = 100;

    current->p = malloc(sizeof(double)*3);
    current->p[0] = 50;
    current->p[1] = 50;
    current->p[2] = 50;

    current->v = malloc(sizeof(double)*3);
    current->v[0] = 0;
    current->v[1] = 0;
    current->v[2] = 0;

    current->f = malloc(sizeof(double)*3);
    current->f[0] = 0;
    current->f[1] = 0;
    current->f[1] = 0;

    current->cells = malloc(sizeof(Body*)*8);
    current->portion = malloc(sizeof(double)*8);

    return bodies;
}

