#ifndef INIT_H
#define INIT_H

#include "cell.h"
#include "body.h"

Body * InitializeRandom(int num_bodies, int nx, int ny, int nz, double xrange, double yrange, double zrange);

Body * Initialize_orbit(int num_bodies, int nx, int ny, int nz, double xrange, double yrange, double zrange);

#endif

