#!/bin/sh

for ((i=1; i<=64; i*=2))
do
  for ((j=200; j<=1000; j+=200))
  do
    OMP_NUM_THREADS="$i" ./material/mm "$j"
  done
  echo 
done
