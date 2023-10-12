#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

static long num_steps = 1000000000;
double step;

int main(int argc, char *argv[])
{

    // This value comes from the run_script bash script
    // The number is specified inside the bash script
    int num_threads = atoi(argv[1]);

    double pi, sum, THREAD_SUMS[num_threads];
    double start_time = omp_get_wtime();
    double step = 1.0 / (double)num_steps;
    omp_set_num_threads(num_threads);

#pragma omp parallel
    {
        int i = 0;
        int ID = omp_get_thread_num();
        int NUM_THREADS_L = omp_get_num_threads();
        double x, local_sum = 0;
        if (ID == 0)
        {
            num_threads = NUM_THREADS_L;
        }
        for (i = ID; i < num_steps; i += NUM_THREADS_L)
        {
            x = (i + 0.5) * step;
            local_sum += 4.0 / (1.0 + x * x);
        }

#pragma omp atomic
        sum += local_sum;
    }

    pi = step * sum;
    double run_time = omp_get_wtime() - start_time;
    printf("\n pi with %ld steps is %lf in %lf seconds\n ", num_steps, pi, run_time);
    return run_time;
}