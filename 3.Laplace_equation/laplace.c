#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../2.Wave_equation_1D/auxilary.h"


int main(int argc, char const *argv[])
{
    double w = 1, a = 3*M_PI, b = M_PI;
    int Nx = 1000, Ny = 500, i, j, n, max_iter=1e5;  
    double dx=a/Nx, dy = b/Ny, uxx, uyy;
    double x[Nx], y[Ny];
    double **u;

    FILE *output;
    output = fopen("output.csv", "w");

    for(i=0; i<Nx; i++) x[i] = i*dx;
    for(i=0; i<Ny; i++) y[i] = i*dy;

    u = malloc(Ny * sizeof(double *));
    for(i=0; i<Ny; i++){
        u[i] = calloc(Nx, sizeof(double));
    }

    //initial conditions
    for(i=0; i<Nx; i++) u[0][i] = 0;
    for(i=0; i<Ny; i++) u[i][0] = 0;
    for(i=0; i<Nx; i++) u[Ny-1][i] = sin(w*x[i])/sin(w*a);
    for(i=0; i<Ny; i++) u[i][Nx-1] = sinh(w*y[i])/sinh(w*b);

    for(n=0; n<max_iter; n++){
        for(j=1; j<Ny-1; j++){
            for(i=1; i<Nx-1; i++){
                uxx = u[j][i+1] + u[j][i-1];
                uyy = u[j+1][i] + u[j-1][i];
                u[j][i] = (dy*dy*uxx + dx*dx*uyy)/(2*(dx*dx + dy*dy));
            }
        }
    }

    write_matrix(u, Ny, Nx, output);
    fclose(output);

    return 0;
}

