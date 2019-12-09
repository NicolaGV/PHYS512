#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cell.h"
#include "body.h"

Cell *** Cell_3D_Alloc(int nx, int ny, int nz) {

    int i, j;

    Cell ***cells = (Cell***) malloc(nx * sizeof(Cell **));
    for (i = 0; i < nx; i++) {
        cells[i] = (Cell**) malloc(ny * sizeof(Cell *));
        for (j = 0; j < ny; j++) {
            cells[i][j] = (Cell*) malloc(nz * sizeof(Cell));
        }
    }
    return cells;


}

Cell *** Cell_InitSpace(nx, ny, nz) {

    Cell *current, ***Space;

    Space = Cell_3D_Alloc(nx, ny, nz); // Allocate memory

    // Create cells
    int x, y, z;
    for(x = 0; x < nx; x++) {
        for(y = 0; y < ny; y++) {
            for (z = 0; z < nz; z++) {

                current = &(Space)[x][y][z];

                current->nbr = (Cell **)malloc(sizeof(Cell *)*6);
                current->int_pos = (int *) malloc(sizeof(int) * 3);
                current->int_pos[0] = x;
                current->int_pos[1] = y;
                current->int_pos[2] = z;
                current->rho = 0.0;
                current->mass = 0.0;
                current->pot = 0.0;

            }
        }
    }


     // Assign cell neighbours (including boundary conditions)
    Cell_LinkSpace(Space, nx, ny, nz);

    return Space;
}

void Cell_LinkSpace(Cell ***Space, int nx, int ny, int nz) {

    Cell * current;

    int x, y, z;
    for(x=0; x<nx; x++) {
        for(y=0; y<ny; y++) {
            for (z=0; z<nz; z++) {

                current = &(Space)[x][y][z];

                // x boundaries
                if (x==0) {
                    current->nbr[0] = current; // non-periodic
                } else {
                    current->nbr[0] = &(Space)[x-1][y][z];
                }

                if (x==nx-1){
                    current->nbr[1] = current; // non-periodic
                } else {
                    current->nbr[1] = &(Space)[x+1][y][z];
                }

                // y boundaries
                if (y==0) {
                    current->nbr[2] = current; // non-periodic
                } else {
                    current->nbr[2] = &(Space)[x][y-1][z];
                }

                if (y==ny-1){
                    current->nbr[3] = current; // non-periodic
                } else {
                    current->nbr[3] = &(Space)[x][y+1][z];
                }

                // z boundaries
                if (z==0) {
                    current->nbr[4] = current; // non-periodic

                } else {
                    current->nbr[4] = &(Space)[x][y][z-1];
                }

                if (z==nz-1){
                    current->nbr[5] = current; // non-periodic

                } else {
                    current->nbr[5] = &(Space)[x][y][z+1];
                }

            }
        }
    }

    return;
}

void Cell_LinkSpace_Periodic(Cell ***Space, int nx, int ny, int nz) {

    Cell * current;

    int x, y, z;
    for(x=0; x<nx; x++) {
        for(y=0; y<ny; y++) {
            for (z=0; z<nz; z++) {

                current = &(Space)[x][y][z];

                // x boundaries
                if (x==0) {
                    current->nbr[0] = &(Space)[nx-1][y][z]; // periodic
                } else {
                    current->nbr[0] = &(Space)[x-1][y][z];
                }

                if (x==nx-1){
                    current->nbr[1] = current; // non-periodic
                    //current->nbr[1] = &(Space)[0][y][z] // periodic
                } else {
                    current->nbr[1] = &(Space)[x+1][y][z];
                }

                // y boundaries
                if (y==0) {
                    current->nbr[2] = &(Space)[x][ny-1][z]; // periodic
                } else {
                    current->nbr[2] = &(Space)[x][y-1][z];
                }

                if (y==ny-1){
                    current->nbr[3] = current; // non-periodic
                    //current->nbr[1] = &(Space)[x][0][z]; // periodic
                } else {
                    current->nbr[3] = &(Space)[x][y+1][z];
                }

                // z boundaries
                if (z==0) {
                    current->nbr[4] = current;
                    current->nbr[4] = &(Space)[x][y][nz-1]; // periodic

                } else {
                    current->nbr[4] = &(Space)[x][y][z-1];
                }

                if (z==nz-1){
                    current->nbr[5] = &(Space)[x][y][0]; // periodic

                } else {
                    current->nbr[5] = &(Space)[x][y][z+1];
                }

            }
        }
    }

    return;
}

// Cloud-in-cell density method
void Space_Density(Cell *** Space, Body * bodies, int num_bodies, int nx, int ny, int nz, double xrange, double yrange, double zrange) {

    double hx = xrange / (nx-1);
    double hy = yrange / (ny-1);
    double hz = zrange / (nz-1);
    double vol = hx * hy * hz;

    Cell * current_c;
    Body *current_b;
    int x, y, z;

    // Reinitialize to 0
    for(x=0; x<nx; x++) {
        for(y=0; y<ny; y++) {
            for (z=0; z<nz; z++) {
                current_c = &(Space)[x][y][z];
                current_c->rho = 0.0;
                current_c->mass = 0.0;
            }
        }
    }

    // cloud-in-cell
    int i;
    for (i = 0; i < num_bodies; i++) {

        current_b = &bodies[i];

        double ix = current_b->p[0]*(nx-1)/xrange;
        double iy = current_b->p[1]*(ny-1)/yrange;
        double iz = current_b->p[2]*(nz-1)/zrange;

        int lowx = floor(ix);
        int lowy = floor(iy);
        int lowz = floor(iz);

        int highx = ceil(ix);
        int highy = ceil(iy);
        int highz = ceil(iz);

        if (ix <= nx-1 && ix >=0 && iy <= ny-1 && iy >=0 && iz <= nz-1 && iz >=0) { // if not outside of bounds

            // assign neighbouring cells
            current_b->cells[0] = &(Space)[lowx][lowy][lowz];
            current_b->cells[1] = &(Space)[lowx][lowy][highz];
            current_b->cells[2] = &(Space)[lowx][highy][lowz];
            current_b->cells[3] = &(Space)[lowx][highy][highz];
            current_b->cells[4] = &(Space)[highx][lowy][lowz];
            current_b->cells[5] = &(Space)[highx][lowy][highz];
            current_b->cells[6] = &(Space)[highx][highy][lowz];
            current_b->cells[7] = &(Space)[highx][highy][highz];

            // portion of mass density
            double xbot = hx/2.0 - (ix - (highx + lowx)/2.0);
            double xtop = hx/2.0 + (ix - (highx + lowx)/2.0);

            double ybot = hy/2.0 - (iy - (highy + lowy)/2.0);
            double ytop = hy/2.0 + (iy - (highy + lowy)/2.0);

            double zbot = hz/2.0 - (iz - (highz + lowz)/2.0);
            double ztop = hz/2.0 + (iz - (highz + lowz)/2.0);

            // assign portion of density of cells
            current_b->portion[0] = xbot*ybot*zbot/vol/vol;
            current_b->portion[1] = xbot*ybot*ztop/vol/vol;
            current_b->portion[2] = xbot*ytop*zbot/vol/vol;
            current_b->portion[3] = xbot*ytop*ztop/vol/vol;
            current_b->portion[4] = xtop*ybot*zbot/vol/vol;
            current_b->portion[5] = xtop*ybot*ztop/vol/vol;
            current_b->portion[6] = xtop*ytop*zbot/vol/vol;
            current_b->portion[7] = xtop*ytop*ztop/vol/vol ;

            // assign density to cells
            current_b->cells[0]->rho = current_b->portion[0]*current_b->mass;
            current_b->cells[1]->rho = current_b->portion[1]*current_b->mass;
            current_b->cells[2]->rho = current_b->portion[2]*current_b->mass;
            current_b->cells[3]->rho = current_b->portion[3]*current_b->mass;
            current_b->cells[4]->rho = current_b->portion[4]*current_b->mass;
            current_b->cells[5]->rho = current_b->portion[5]*current_b->mass;
            current_b->cells[6]->rho = current_b->portion[6]*current_b->mass;
            current_b->cells[7]->rho = current_b->portion[7]*current_b->mass;

            /*
            printf("\n%lf %lf %lf\n", ix, iy, iz);
            printf("%lf %lf %lf %lf %lf %lf\n", lowx, highx, lowy, highy, lowz, highz);
            */

            /*
            int j;
            for (j=0; j < 8;j++) {
                printf("%lf\n", current_b->portion[j]);
            }
            */
        }
    }

    /*
    // nearest point
    int i;
    for(i = 0; i < num_bodies; i++) {

        current_b = &bodies[i];

        double ix = current_b->p[0]*nx/xrange;
        double iy = current_b->p[1]*ny/yrange;
        double iz = current_b->p[2]*nz/zrange;

        int lowx = floor(ix);
        int lowy = floor(iy);
        int lowz = floor(iz);

        int highx = ceil(ix);
        int highy = ceil(iy);
        int highz = ceil(iz);

        if (ix <= nx-1 && ix >=0 && iy <= ny-1 && iy >=0 && iz <= nz-1 && iz >=0) { // if not outside of bounds

            current_b->cell = &(Space)[ix - lowx < highx - ix ? lowx : highx]
                            [iy - lowy < highy - iy ? lowy : highy]
                            [iz - lowz < highz - iz ? lowz : highz];
            current_b->cell->mass += current_b->mass;
        }
    }

    // Update densities
    for(x=0; x<nx; x++) {
        for(y=0; y<ny; y++) {
            for (z=0; z<nz; z++) {
                current_c = &(Space)[x][y][z];
                current_c->rho = current_c->mass/vol;
            }
        }
    }
    */
}
