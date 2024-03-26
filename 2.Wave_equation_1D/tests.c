#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "auxilary.h"

double I(double x, double A, double L){
    return A*sin(M_PI/L*x);
}


int main(int argc, char const *argv[])
{
    int Nt = 100, Nx = 10;
    double t0 = 0.0, tf = 10.0, x0=0.0, xf=5.0;
    double dx = (xf - x0)/(Nx-1);
    // double dt = (tf - t0)/(Nt-1);
    // double C = c*dt/dx;
    // double C2 = C*C;
    double C2 = 0.8; //CFL = c*dt/dx
    double c= 2.0;
    double dt = C2*dx/c;

    double L=xf-x0, A=2;
    int i, n;

    FILE *output;
    output = fopen("output_test.csv", "w");

    //vectors
    double x[Nx];
    double **u;
    u = malloc(Nt * sizeof(double *));
    for(i=0; i<Nt; i++){
        u[i] = malloc(Nx * sizeof(double));
    }

    for(i=0; i<Nx; i++){
        x[i] = i*dx;
    }

    // Set initial conditions u(x, 0) = I(x)
    for(i=0; i<Nx; i++){
        u[0][i] = I(x[i], A, L);
    }

    //enforce boundary conditions
    u[0][0] = 0.0;
    u[0][Nx-1] = 0.0;

    //Apply the formula for the first step
    for(i=1; i<Nx-1; i++){
        u[1][i] = u[0][i] - 0.5*C2*(u[0][i+1] - 2*u[0][i] + u[0][i-1]);
    }

    //enforce boundary conditions
    u[1][0] = 0.0;
    u[1][Nx-1] = 0.0;
    
    for(n=2; n<Nt; n++){
        //Update all inner mesh points at time t[n+1]
        for(i=1; i<Nx-1; i++){
            u[n][i] = 2*u[n-1][i] - u[n-2][i] + C2*(u[n-1][i+1] - 2*u[n-1][i] + u[n-1][i-1]);
        }
        u[n][0] = 0;
        u[n][Nx-1] = 0;
    }

    write_matrix(u, Nt, Nx, output);
    fclose(output);

    return 0;
}

