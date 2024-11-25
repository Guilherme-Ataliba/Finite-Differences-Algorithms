#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> //biblioteca pra gente conseguir ver o tempo que ta rodando 

#define Nx 120
#define Ny 60
#define max_iter 1e6
#define V0 1
#define a 1
#define b 1

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

double** inicializa_matriz(){
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
        u[i][0] = V0; //f(-b,y)=V_0
    for(i=0; i<Nx; i++)
         u[Ny-1][i] = 0; //f(x,a)=0
    for(i=0; i<Ny; i++)
        u[i][Nx-1] = V0; //f(b,y)=V_0

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
                u[j][i] = (DY*uxx + DX*uyy)/C;
            }
        }
}


int main(int argc, char const *argv[])
{
    int i, j, n; //max_iter define a convergência  
    double dx=(2*b)/Nx, dy = a/Ny, uxx, uyy;
    double DX = dx*dx, DY = dy*dy;
    double **u;
    clock_t antes, depois, temp_exe; //variável do tipo tempo   

    //criando arquivo
    FILE *saida, *tempo;
    saida = fopen("saida.csv", "w");
    tempo = fopen("tempo.txt", "w");

    antes = clock();
    
    u=inicializa_matriz();
    
    u=condicao_de_contorno(u);

    for(i=0; i<max_iter; i++){
        calculo_potencial(u, DX, DY);

        //  printf("numero de iterações: %d de %lf \n", i+1, max_iter);
    }
   
    escreve_matriz(u, Ny, Nx, saida);
    fclose(saida);

    depois = clock();

    temp_exe = (depois - antes)/CLOCKS_PER_SEC; //mede frames por segundo, esses frames variam de pc pra pc ou biblio pra biblio, pra pegar o meu uso o clock_per_sec.

    fprintf(tempo, "tempo de execução: %lf", (double)temp_exe);
    fclose(tempo);

    return 0;
}

