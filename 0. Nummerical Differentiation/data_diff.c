#include <stdio.h> 
#include <math.h>

// central implementation
double central_d2fdx2(double x, double y, double y_before, double y_later, double dx){
    return (y_before + 2*y + y_later)/(dx*dx);
}

//backward implementaion
double backward_d2fdx2(double x, double y, double y_before, double y_bbefore, double dx){
    return (y - 2*y_before + y_bbefore)/(dx*dx);
}

//forward implementaion
double forward_d2fdx2(double x, double y, double y_later, double y_llater, double dx){
    return (y_llater - 2*y_later + y)/(dx*dx);
}

int main(int argc, char const *argv[])
{
    //generating some data
    FILE *input_data;
    input_data = fopen("input_data.csv", "w");

    if input_data = NULL{
        prinf("Failed to open the file input_data");
        return 1;
    }

    double lower_limit = 0, upper_limit = 10, step = 0.1;
    double x;

    for(x=lower_limit; x<upper_limit; x += step){
        fprintf(input_data, "%lf %lf", x, sin(x))
    }

    fclose(input_data)


    //Implement second order method
    FILE *output;
    output = fopen("output_data.csv", "w");

    if output = NULL{
        prinf("Failed to open the file output_data");
        return 1;
    }
    
    //calculating the first point using foward difference
    
    //I'm gonna stop this because it becomes a problem of reading data in C
    fprintf(output, "%lf %lf %lf %.8lf", )
    for(x=lower_limit; x<upper_limit; x += step){
        
    }

    return 0;
}
