#include <stdio.h>
#include <math.h>
#include "auxilary.h"

double I(double x, double A, double L){
    return A*sin(M_PI/L*x);
}

int main(int argc, char const *argv[])
{
    // N is the amount of points on the grid
    // (x0, xf) are the initial and end points of the x range
    int Nt = 30, Nx = 10;
    double x0 = 0.0, xf = 1.0, t0 = 0.0, tf=2.0;
    double dx = (xf - x0)/(Nx-1), dt = (tf - t0)/(Nt-1), c=1.0;
    double x[Nx], t[Nt], u_n[Nx], u[Nx], u_nm1[Nx];
    double C = c*dt/dx, L=xf-x0, A=2;
    double C2 = C*C;
    int i, n;
    
    FILE *output;
    output = fopen("output.csv", "w");

    //Set x and t arrays
    for(i=0; i<Nx; i++){
        x[i] = i*dx;
    }
    for(i=0; i<Nt; i++){
        t[i] = i*dt;
    }   
    

    // Set initial conditions u(x, 0) = I(x)
    for(i=0; i<Nx; i++){
        u_n[i] = I(x[i], 2, L);
    }

    //Apply the formula for the first step
    for(i=1; i<Nx-1; i++){
        u[i] = u_n[i] - 0.5*C2*(u_n[i+1] - 2*u_n[i] + u_n[i-1]);
    }

    // Enforce boundary conditions
    u[0] = 0;
    u[Nx-1] = 0;

    //output
    write_vector(u, Nx, output);


    //Switch variables before next iteration
    copy_vector(u_n, u_nm1, Nx);
    copy_vector(u, u_n, Nx);

    printf("C: %lf, C2: %lf\n", C, C2);

    for(n=1; n<Nt; n++){
        //Update all inner mesh points at time t[n+1]
        for(i=1; i<Nx; i++){
            u[i] = 2.0*u_n[i] - u_nm1[i] + C2*(u_n[i+1] - 2.0*u_n[i] + u_n[i-1]);
        }
        

        //Insert boundary conditions
        u[0]=0;
        u[Nx-1]=0;

        //output
        write_vector(u, Nx, output);

        //Switch variables before next step
        copy_vector(u_n, u_nm1, Nx);
        copy_vector(u, u_n, Nx);
    }

    fclose(output);

    return 0;
}
