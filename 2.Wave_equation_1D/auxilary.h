#include <stdio.h>

void copy_vector(double *arr1, double *arr2, int size){
    //Copy arr1 into arr2
    
    int i;

    for(i=0; i<size; i++){
        arr2[i] = arr1[i];
    }
}

void print_vector(double *vector, int size){
    int i=0;
    for(i=0; i<size; i++){
        printf("%lf\t", vector[i]);
    }

    return;
}

void print_matrix(double **matrix, int row, int col){
    int i, j;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void write_vector(double *vector, int size, FILE *path){
    int i;
    for(i=0; i<size-1; i++){
        fprintf(path, "%.8lf,", vector[i]);
    }
    fprintf(path, "%.8lf", vector[i]);
    fprintf(path, "\n");
}

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