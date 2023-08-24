#!/bin/sh

for i in 100 200 300 400 500 600 700 800 900 1000
do
  OMP_NUM_THREADS=$1  ./mm  "$i"
done
