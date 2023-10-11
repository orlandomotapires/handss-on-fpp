#!/bin/sh

for ((i=2; i<=64; i*=2)) # num_threads
do
    for ((j=2; j<=8; j*=2)) # num_processors
    do
        for ((k=200; k<=1000; k+=200))
        do
            mpirun -np "$j" ./material/mm-mpi_openmp  "$k" "$i" 
        done
    done
done
