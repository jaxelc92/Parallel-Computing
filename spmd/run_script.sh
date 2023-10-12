#!/bin/bash

# Number of times to run the program
num_runs=10

for threads in $(seq 1 10); do
    total_time=0

    for ((i=1; i<=$num_runs; i++)); do
        # Compile and run your program with the specified number of threads
        clang -Xclang -fopenmp -L/usr/local/opt/libomp/lib -I/usr/local/opt/libomp/include -lomp spmd.c -o spmdout
        program_output=$(./spmdout $threads)

        execution_time=$(echo "$program_output" | awk '/in/{print $(NF-1)}')

        echo "Threads: $threads, Run $i Time: $execution_time seconds"

        total_time=$(echo "$total_time + $execution_time" | bc)
    done

    # Calculate and print the mean time for this thread count
    mean_time=$(echo "scale=4; ($total_time/$num_runs)" | bc)
    echo "Threads: $threads, Mean Time: $mean_time seconds"
done
