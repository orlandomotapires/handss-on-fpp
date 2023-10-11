#!/bin/sh

for ((i=2; i<=64; i*=2))
do
  echo "Number of threads:" $i "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="  
  for ((j=200; j<=1000; j+=200))
  do
    OMP_NUM_THREADS="$i" ./material/mm "$j"
  done
  echo 
done
