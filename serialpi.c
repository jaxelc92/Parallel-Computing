// SERIAL PI IMPLEMENTATION
#include <stdio.h>
#include <time.h>

static long num_steps = 1000000000;

int main()
{
    clock_t t;
    t = clock();
    int i;
    double x, pi, sum = 0.0;
    double step = 1.0 / (double)num_steps;
    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("pi: %lf in %f seconds", pi, time_taken);
    return 0;
}