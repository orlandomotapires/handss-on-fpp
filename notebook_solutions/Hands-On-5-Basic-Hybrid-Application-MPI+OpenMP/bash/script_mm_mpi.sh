#!/bin/sh

for ((i=1; i<=32; i*=2))
do
  for ((j=200; j<=1000; j+=200))
  do
    mpirun -np "$i" ./material/mm-mpi "$j"
  done
  echo 
done
