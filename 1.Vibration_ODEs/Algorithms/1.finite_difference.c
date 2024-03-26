#include <stdio.h>
#include <math.h>

double real(double *I, double *w, double *t){
    return *I * cos(*w * *t);
}

int main(int argc, char const *argv[])
{
    double I = 2.0, t0 = 0, tf = 6*M_PI, dt = 1e-3, w=1;
    double u, u_old[2], t;

    FILE *output;
    output = fopen("1-output.csv", "w");

    u_old[0] = I;
    u_old[1] = u_old[0] - 0.5* dt*dt * w*w * u_old[0];

    for (t=t0+dt; t<tf; t += dt){
        u = 2*u_old[1] - u_old[0] - dt*dt * w*w * u_old[1];
        u_old[0] = u_old[1];
        u_old[1] = u;

        fprintf(output, "%lf, %lf, %.8lf\n", t, u, real(&I, &w, &t) - u);
    }
    
    fclose(output);

    return 0;
}
