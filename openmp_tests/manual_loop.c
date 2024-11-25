    #include <stdlib.h>
    #include <stdio.h>
    #include <omp.h>

    int main(int argc, char const *argv[])
    {
        int i, j, chunk_size, start, end;
        int num_threads, thread_id;
        // omp_set_num_threads(4);

        
        #pragma omp parallel private(thread_id, i, chunk_size, start, end)
        {
            num_threads =  omp_get_num_threads();
            thread_id = omp_get_thread_num();
            
            printf("%f\n", ((80)*(thread_id)/num_threads));
        }
        
        return 0;
    }
