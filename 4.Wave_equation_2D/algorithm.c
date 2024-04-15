#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "auxilary.h"

//Initial Condition
double I(double x, double y){
    return 0;
}

//Termo de fonte
double f(double x, double y, double Nx, double Ny, double x_max, double y_max, int i, int j, double t){

    if(i<(Nx/2 + Nx/100) && i>(Nx/2 - Nx/100)){
        if(j<(Ny/2 + Ny/100) && j>(Ny/2 - Ny/100)){
            return 5*sin(30*M_PI*t/20);
        }
    }
    // if(i == Nx/2 && j==Ny/2){
    //     // return 20*sin(30*M_PI*t/20);
    //     return 5*sin(30*M_PI*t/20);
    // }
    return 0;
}

int main(int argc, char const *argv[])
{ 

    int Nx = 10000, Ny = 10000, T=10;
    double a = 10.0, b=10.0, dx=a/Nx, dy = b/Ny;
    double *x, *y, **u, **unm1, **unm2;
    double t, c=1, Cx = 0.5, Cy=0.5, dt = Cx*dx/c, Cx2=Cx*Cx, Cy2=Cy*Cy;
    int Nt = floor(T/dt);  
    int i, j, file_index=0;
    /*Frames
        print_interval = total_files (T/dt) / frames
    */
    int frames = 200, print_interval = floor(T/dt)/frames, print_counter=1;
    int n_files = Nt/print_interval + 2;
    
    FILE *time_file;
    time_file = fopen("output/Execution_time.txt", "w");

    FILE *output;
    output = fopen("output/test_matrix.bin", "wb");
    fwrite(&Nx, sizeof(int), 1, output);
    fwrite(&Ny, sizeof(int), 1, output);
    fwrite(&n_files, sizeof(int), 1, output);

    clock_t begin, end;
    begin = clock();

    x = malloc(Nx * sizeof(double));
    for (i=0; i<Nx; i++) x[i] = i*dx;
    y = malloc(Ny * sizeof(double));
    for (i=0; i<Ny; i++) y[i] = i*dy;

    u = malloc(Ny * sizeof(double *));
    for (i=0; i<Ny; i++){
        u[i] = malloc(Nx* sizeof(double));
    }
    unm1 = malloc(Ny * sizeof(double *));
    for (i=0; i<Ny; i++){
        unm1[i] = malloc(Nx * sizeof(double));
    }
    unm2 = malloc(Ny * sizeof(double *));
    for (i=0; i<Ny; i++){
        unm2[i] = malloc(Nx * sizeof(double));
    }
    
    //Calculating step 0 (initial condition)
    for(j=0; j<Ny; j++){
        for(i=0; i<Nx; i++){
            unm2[j][i] = I(x[i], y[j]);
        }
    }

    write_multiple_matrix(unm2, Nx, Ny, output);
    file_index++;

    // Calculating step 1
    for(j=1; j<Ny-1; j++){
        for(i=1; i<Nx-1; i++){
            unm1[j][i] = unm2[j][i] + 0.5*Cx2*(unm2[j][i+1] - 2*unm2[j][i] + unm2[j][i-1]) 
            + 0.5*Cy2*(unm2[j+1][i] - 2*unm2[j][i] + unm2[j-1][i]) + 0.5*dx*dx*f(x[i], y[j], Nx, Ny, x[Nx-1], y[Ny-1], i, j, 1);
        }
    }
    //Enforce boundary conditions
    for(i=0; i<Nx; i++){
        unm1[0][i] = 0;
        unm1[Nx-1][i] = 0;
    }
    for(j=0; j<Ny; j++){
        unm1[j][0] = 0;
        unm1[j][Ny-1] = 0;
    }

    write_multiple_matrix(unm1, Nx, Ny, output);
    file_index++;
    
    
    // Main Algorithm
    for(t=0; t<T; t+=dt){
        //Boundary Conditions
        for(i=0; i<Nx; i++){
            u[0][i] = 0;
            u[Nx-1][i] = 0;
        }
        for(j=0; j<Ny; j++){
            u[j][0] = 0;
            u[j][Ny-1] = 0;
        }   

        //Calculating unp1
        for(j=1; j<Ny-1; j++){
            for(i=1; i<Nx-1; i++){
                u[j][i] = -unm2[j][i] + 2*unm1[j][i] + Cx2*(unm1[j][i+1] - 2*unm1[j][i] + unm1[j][i-1]) + 
                Cy2*(unm1[j+1][i] - 2*unm1[j][i] + unm1[j-1][i]) + dx*dx*f(x[i],y[i],Nx, Ny, x[Nx-1], y[Ny-1], i, j, t);
            }
        }

        copy_matrix(unm2, unm1, Nx, Ny);
        copy_matrix(unm1, u, Nx, Ny);

        if(print_counter >= print_interval){
            printf("Current time step: %lf\n", t);
            write_multiple_matrix(u, Nx, Ny,output);
            print_counter=0;
        }
        print_counter++;

        file_index++;
    }

    FILE *test;
    test = fopen("output/test.bin", "wb");
    write_multiple_matrix(u, Nx, Ny, test);


    printf("Frames: %d\nPrint Interval: %d", frames + 2, print_interval);
    fclose(output);


    end = clock();
    fprintf(time_file, "Elapsed Time:%lf\ndx = %g \t dy = %g\nNx = %d \t Ny = %d\na=%lf\nb=%lf\nT=%d\nc=%lf\nCx=%lf \t Cy=%lf",
    (double)(end-begin)/CLOCKS_PER_SEC, dx, dy, Nx, Ny, a, b, T, c, Cx, Cy);

    return 0;
}

