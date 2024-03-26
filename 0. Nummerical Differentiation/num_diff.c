#include <stdio.h>
#include <math.h>

double f(double x){
    return sin(x);
}

double dfdx(double x, double dx){
    return (f(x + dx) - f(x))/dx;
}

double central_dfdx(double x, double dx){
    return (f(x + dx) - f(x - dx))/2*dx;
}

double second_central_dfdx(double x, double dx){
    return (4*f(x + dx) + f(x - 2*dx) -4* f(x - dx) - f(x + 2*dx))/(4*dx);
}

int main(int argc, char const *argv[])
{
    //archive
    FILE *forward, *central, *second_central;
    forward = fopen("forward.csv", "w");
    central = fopen("central.csv", "w");
    second_central = fopen("second_central.csv", "w");

    if (forward == NULL){
        printf("Failed to open forward file");
        return 1;
    }

    if (central == NULL){
        printf("Failed to open central file");
        return 1;
    }

    if (second_central == NULL){
        printf("Failed to open central file");
        return 1;
    }

    //ploting
    double X_0, X_f;
    double x, dx=0.1;

    X_0 = 0;
    X_f = 100;

    for(x=X_0; x<X_f; x += dx){
        //foward
        fprintf(forward, "%lf, %lf, %lf, %.8lf\n", x, f(x), dfdx(x, dx), cos(x) - dfdx(x, dx));
        //central
        fprintf(central, "%lf, %lf, %lf, %.8lf\n", x, f(x), central_dfdx(x, dx), cos(x) - central_dfdx(x, dx));
        //second central
        fprintf(second_central, "%lf, %lf, %lf, %.8lf\n", x, f(x), second_central_dfdx(x, dx), cos(x) - second_central_dfdx(x, dx));
    }

    fclose(forward);
    fclose(central);
}
