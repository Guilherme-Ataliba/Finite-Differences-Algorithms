#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> //biblioteca pra gente conseguir ver o tempo que ta rodando 
#include "utilidades.h"

int main(int argc, char const *argv[])
{
    double w = 1, a = 1, b = 1;
    int Nx = 24,  Ny = 48, i, j, n, max_iter=1e2, V0=-5; //max_iter define a convergência  
    double dx=2*b/Nx, dy = a/Ny, uxx, uyy;
    double x[Nx], y[Ny];
    double **u;
    clock_t antes, depois, temp_exe; //variável do tipo tempo   

    FILE *output, *tempo;
    output = fopen("output.csv", "w");
    tempo = fopen("tempo.txt", "w");

    antes = clock();
    
    for(i=0; i<Nx; i++) x[i] = i*dx - b; //inicializando a matriz 
    for(i=0; i<Ny; i++) y[i] = i*dy;

    u = malloc(Ny * sizeof(double *));
    for(i=0; i<Ny; i++){
        u[i] = calloc(Nx, sizeof(double));
    }

    //condições de contorno
    for(i=0; i<Nx; i++) u[0][i] = 0; //f(x,0)=0
    for(i=0; i<Ny; i++) u[i][0] = V0; //f(-b,y)=V_0
    for(i=0; i<Nx; i++) u[Ny-1][i] = 0; //f(x,a)=0
    for(i=0; i<Ny; i++) u[i][Nx-1] = V0; //f(b,y)=V_0

    //loop de convergência
    for(n=0; n<max_iter; n++){
        for(j=1; j<Ny-1; j++){
            for(i=1; i<Nx-1; i++){
                uxx = u[j][i+1] + u[j][i-1];
                uyy = u[j+1][i] + u[j-1][i];
                u[j][i] = (dy*dy*uxx + dx*dx*uyy)/(2*(dx*dx + dy*dy));
            }
        }

        printf("numero de iterações: %d de %d \n", n+1, max_iter);
    }

    write_matrix(u, Ny, Nx, output);
    fclose(output);

    depois = clock();

    temp_exe = (depois - antes)/CLOCKS_PER_SEC; //mede frames por segundo, esses frames variam de pc pra pc ou biblio pra biblio, pra pegar o meu uso o clock_per_sec.

    fprintf(tempo, "tempo de execução: %lf", (double)temp_exe);
    fclose(tempo);

    return 0;
}

