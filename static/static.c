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

    double pi, sum, SUMS[num_threads];
    double start_time = omp_get_wtime();
    double step = 1.0 / (double)num_steps;
    omp_set_num_threads(num_threads);

#pragma omp parallel for reduction(+ : sum) schedule(static)
    for (int i = 0; i < num_steps; i++)
    {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    double run_time = omp_get_wtime() - start_time;
    printf("\n pi with %ld steps is %lf in %lf seconds\n ", num_steps, pi, run_time);
    return run_time;
}