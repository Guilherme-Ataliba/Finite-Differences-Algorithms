#include <stdio.h>
#include "utilidades.h"

void write_matrix(double **matrix, int row, int col, FILE *path){
    int i, j;
    for(i=0; i<row; i++){
        for(j=0; j<col-1; j++){
            fprintf(path, "%.4lf,", matrix[i][j]);
        }
        fprintf(path, "%.4lf", matrix[i][col-1]);
        fprintf(path, "\n");
    }
}
