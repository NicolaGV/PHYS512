#ifndef SOLVER_H
#define SOLVER_H

#include "cell.h"
#include "body.h"

void Potential(Cell *** Space, int nx, int ny, int nz, double xrange, double yrange, double zrange);

void Force(Body *bodies, int num_bodies, double * energy);

void Evolve(Body *bodies, int num_bodies, float dt, double * energy);

void EvolvePeriodic(Body * bodies, int num_bodies, float dt, double xrange, double yrange, double zrange, double * energy);

#endif // SOLVER_H
