#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> //biblioteca pra gente conseguir ver o tempo que ta rodando 
#include <omp.h>

#define Nx 60
#define Ny 60
#define max_iter 1e5

#define V0 1.0
#define a 1.0
#define b 1.0
#define aux 0

double **calcula_simetria(double **u){ //criar coluna fantasma, auxiliar
    int i, j;
    double **U;

    U = malloc(Ny * sizeof(double *));
    for (i=0; i<Ny; i++)
        U[i] = malloc(2*(Nx-aux) * sizeof(double));

    for(i=0; i<Ny; i++){
        for(j=0; j<Nx-aux; j++){
            U[i][j] = u[i][j];
        }
    }

    for(i=0; i<Ny; i++){
        for(j=0; j<Nx-aux; j++){
            U[i][j+Nx-aux] = u[i][Nx-aux-1-j];
        }
    }

    return U;
}

void escreve_matriz(double **matriz, int linha, int coluna, FILE *caminho){
    int i, j;
    for(i=0; i<linha; i++){
        for(j=0; j<coluna-1; j++){
            fprintf(caminho, "%.4lf,", matriz[i][j]);
        }
        fprintf(caminho, "%.4lf", matriz[i][coluna-1]);
        fprintf(caminho, "\n");
    }
}

double** inicializa_matriz(double dx, double dy){
    int i;
    double **u;

    u = malloc(Ny * sizeof(double *));
    for(i=0; i<Ny; i++){
        u[i] = calloc(Nx, sizeof(double)); //enchendo de zeros
    }

    return u;

}

double** condicao_de_contorno(double **u){
    int i;
    for(i=0; i<Nx; i++)
        u[0][i] = 0; //f(x,0)=0
    for(i=0; i<Ny; i++)
        u[i][0] = V0; //f(0,y)=0
    for(i=0; i<Nx; i++)
         u[Ny-1][i] = 0; //f(x,a)=0
    for(i=0; i<Ny; i++)
        u[i][Nx-1] = 0; //f(b,y)=V_0

    return u;
}

double** calculo_potencial(double **u, double DX, double DY){
    int i,j,n;
    double uxx, uyy;
    double C = 2*(DX + DY);

    //loop de convergência    
        for(j=1; j<Ny-1; j++){
            for(i=1; i<Nx-1; i++){
                uxx = u[j][i+1] + u[j][i-1];
                uyy = u[j+1][i] + u[j-1][i];
                u[j][i] = (DY*uxx + DX*uyy)/(C);
            }
        }

}


int main(int argc, char const *argv[])
{
    int k, j, n; //max_iter define a convergência  
    double dx=b/Nx, dy = a/Ny, uxx, uyy;
    double  DX = dx*dx, DY = dy*dy;
    double **u, **U;
    clock_t antes, depois, temp_exe; //variável do tipo tempo   

    //criando arquivo
    FILE *saida, *tempo;
    saida = fopen("saida.csv", "w");
    tempo = fopen("tempo.txt", "w");

    antes = clock();
    
    u=inicializa_matriz(dx, dy);
    
    u=condicao_de_contorno(u);

    #pragma omp parallel for private(k)
    for(k=0; k<(int)max_iter; k++){
    	calculo_potencial(u, DX, DY);

	// printf("numero de iterações: %d de %lf \n", i+1, max_iter);
    }
   
    U = calcula_simetria(u);
    escreve_matriz(U, Ny, 2*Nx, saida);
    fclose(saida);

    depois = clock();

    temp_exe = (depois - antes)/CLOCKS_PER_SEC; //mede frames por segundo, esses frames variam de pc pra pc ou biblio pra biblio, pra pegar o meu uso o clock_per_sec.

    fprintf(tempo, "tempo de execução: %lf", (double)temp_exe);
    fclose(tempo);

    return 0;
}

