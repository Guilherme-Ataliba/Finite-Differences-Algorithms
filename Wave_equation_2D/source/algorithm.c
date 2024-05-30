#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../include/auxilary.h"

// Macro Definitions  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define Nx 200
#define Ny 200
#define T 10
#define a 10.0
#define b 10.0
#define dx (a/Nx)
#define dy (b/Ny)
#define Cx 0.5
#define Cy 0.5
#define Cx2 (Cx*Cx)
#define Cy2 (Cy*Cy)


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Initial Condition
double I(double x, double y){
    return 0;
}

//Termo de fonte
double f(double x, double y, double x_max, double y_max, int i, int j, double t){

    if(i<(Nx/2 + Nx/100) && i>(Nx/2 - Nx/100)){
        if(j<(Ny/2 + Ny/100) && j>(Ny/2 - Ny/100)){
            return 5*sin(30*M_PI*t/20);
        }
    }

    return 0;
}

void create_all(double** x, double** y, double ***u, double ***unm1, double*** unm2){
    int i;
    
    *x = malloc(Nx * sizeof(double));
    for (i=0; i<Nx; i++) (*x)[i] = i*dx;

    *y = malloc(Ny * sizeof(double));
    for (i=0; i<Ny; i++) (*y)[i] = i*dy;

    *u = malloc(Ny * sizeof(double *));
    for (i=0; i<Ny; i++){
        (*u)[i] = malloc(Nx* sizeof(double));
    }
    *unm1 = malloc(Ny * sizeof(double *));
    for (i=0; i<Ny; i++){
        (*unm1)[i] = malloc(Nx * sizeof(double));
    }
    *unm2 = malloc(Ny * sizeof(double *));
    for (i=0; i<Ny; i++){
        (*unm2)[i] = malloc(Nx * sizeof(double));
    }
}

void step_zero(double*** unm2, double **x, double **y){
    int i, j;

    printf("Calculating step 0\n");
    //Calculating step 0 (initial condition)
    for(j=0; j<Ny; j++){
        for(i=0; i<Nx; i++){
            (*unm2)[j][i] = I((*x)[i], (*y)[j]);
        }
    }
}

void step_one(double ***unm1, double ***unm2, double **x, double **y){
    int i, j;
    
    printf("Calculating step 1\n");
    // Calculating step 1
    for(j=1; j<Ny-1; j++){
        for(i=1; i<Nx-1; i++){
            (*unm1)[j][i] = (*unm2)[j][i] + 0.5*Cx2*((*unm2)[j][i+1] - 2*(*unm2)[j][i] + (*unm2)[j][i-1]) 
            + 0.5*Cy2*((*unm2)[j+1][i] - 2*(*unm2)[j][i] + (*unm2)[j-1][i]) + 0.5*dx*dx*f((*x)[i], (*y)[j], (*x)[Nx-1], (*y)[Ny-1], i, j, 1);
        }
    }
}

void next_step(double ***u, double ***unm1, double ***unm2, double **x, double **y, double *t){
    int i, j;

    for(j=1; j<Ny-1; j++){
        for(i=1; i<Nx-1; i++){
            (*u)[j][i] = -(*unm2)[j][i] + 2*(*unm1)[j][i] + Cx2*((*unm1)[j][i+1] - 2*(*unm1)[j][i] + (*unm1)[j][i-1]) + 
            Cy2*((*unm1)[j+1][i] - 2*(*unm1)[j][i] + (*unm1)[j-1][i]) + dx*dx*f((*x)[i],(*y)[i], (*x)[Nx-1], (*y)[Ny-1], i, j, *t);
        }
    }
}

void enforce_boundary_conditions(double ***U){
    int i, j;

    for(i=0; i<Nx; i++){
        (*U)[0][i] = 0;
        (*U)[Nx-1][i] = 0;
    }
    for(j=0; j<Ny; j++){
        (*U)[j][0] = 0;
        (*U)[j][Ny-1] = 0;
    }
}

int main(int argc, char const *argv[])
{ 

    double *x, *y, **u, **unm1, **unm2;
    double t, c=1, dt = Cx*dx/c;
    int Nt = floor(T/dt);  
    int i, j;
    
    // We have to define the number of files in a smart way, since it may not result in a integer value
    int frames = 202, print_interval = ceil(T/dt/frames), print_counter=print_interval;
    int n_files = floor(T/dt/print_interval)+2;
    
    FILE *time_file;
    time_file = fopen("output/Execution_time.txt", "w");

    char dir_path[] = "output/multi_matrix/";
    int file_index=0;
    
    FILE *exec_info;
    exec_info = fopen("output/multi_matrix/exec_info.csv", "w");
    fprintf(exec_info, "Nx,Ny,n_files,a,b\n%d,%d,%d,%lf,%lf", Nx, Ny, n_files, a, b);
    fclose(exec_info);

    clock_t begin, end;
    begin = clock();

    create_all(&x, &y, &u, &unm1, &unm2);
    
    printf("=-=-=-=-=-=-=-=-=-=-= Start of Processing =-=-=-=-=-=-=-=-=-=-=\n");

    step_zero(&unm2, &x, &y);

    write_dir_matrix(unm2, Nx, Ny, dir_path, &file_index);

    step_one(&unm1, &unm2, &x, &y);
    
    //Enforce boundary conditions
    enforce_boundary_conditions(&unm1);

    write_dir_matrix(unm1, Nx, Ny, dir_path, &file_index);
    
    
    // Main Algorithm
    for(t=0; t<T; t+=dt){
        //Boundary Conditions
        enforce_boundary_conditions(&u);

        //Calculating unm1
        next_step(&u, &unm1, &unm2, &x, &y, &t);

        copy_matrix(unm2, unm1, Nx, Ny);
        copy_matrix(unm1, u, Nx, Ny);

        if(print_counter >= print_interval){
            printf("Current time step: %.2lf/%d\n", t, T);
            write_dir_matrix(u, Nx, Ny, dir_path, &file_index);
            print_counter=0;
        }
        print_counter++;
    }

    printf("=-=-=-=-=-=-=-=-=-=-= End of Processing =-=-=-=-=-=-=-=-=-=-=\n");

    printf("Frames: %d\nPrint Interval: %d\n", frames + 2, print_interval);


    end = clock();
    fprintf(time_file, "Elapsed Time:%lf\ndx = %g \t dy = %g\nNx = %d \t Ny = %d\na=%lf\nb=%lf\nT=%d\nc=%lf\nCx=%lf \t Cy=%lf",
    (double)(end-begin)/CLOCKS_PER_SEC, dx, dy, Nx, Ny, a, b, T, c, Cx, Cy);

    return 0;
}

