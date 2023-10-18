#!/bin/sh

for ((i=1; i<=32; i*=2)) # num_threads
do
    for ((j=1; j<=4; j*=2)) # num_processors
    do    

        if [ "$i" == 1 ] && [ "$j" == 2 ]; then 
            break
        fi

        for ((k=200; k<=1000; k+=200))
        do
            mpirun -np "$j" ./material/mm-mpi_openmp "$k" "$i"
        done
        
    done
done
