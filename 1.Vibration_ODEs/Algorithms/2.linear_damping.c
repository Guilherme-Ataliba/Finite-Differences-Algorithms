#include <stdio.h>
#include <math.h>

double s(double k, double u){
    return k*u;
}

double F(double w, double F0, double t){
    return F0 * cos(w*t);
}

int main(int argc, char const *argv[])
{
    double t0 = 0, T = 6*M_PI, dt = 1e-4;
    double w, I, V, m, b, k, F0, t, u;
    double u_old[2];

    FILE *output;
    output = fopen("2-output.csv", "w");

    I = 3;
    w = 2.0;
    V = 2;
    m = 1;
    b = 2;
    k = 1;
    F0 = 2;

    u_old[0] = I;
    u_old[1] = u_old[0] + dt*V + dt*dt / (2*m) * (-b*V - s(k, u_old[0]) + F(w, F0, t0));

    for(t=t0; t<T; t+=dt){
        u = (2*m*u_old[1] + (b/2*dt - m)*u_old[0] + dt*dt*(F(w, F0, t) - s(k, u_old[1])))/(m + b/2*dt);
        u_old[0] = u_old[1];
        u_old[1] = u;

        fprintf(output, "%lf, %lf\n", t, u);
    }

    fclose(output);


    return 0;
}
