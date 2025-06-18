#!/bin/bash

# Parametry wejsciowe
problems=(0 1)
algorithms=(0 1)
nodes=(100 250 500 750 1000 1250 1500)
densities=(0.1 0.25 0.5 0.75 0.99)
iterations=50

# Tworzymy katalog na wyniki (jesli nie istnieje)
mkdir -p results

# Petla po wszystkich kombinacjach
for problem in "${problems[@]}"; do
  for algorithm in "${algorithms[@]}"; do
    for node in "${nodes[@]}"; do
      for density in "${densities[@]}"; do
        output_file="results/out_p${problem}_a${algorithm}_n${node}_d${density}.txt"
        echo "Running: ./aizog --test $problem $algorithm $node $density $iterations $output_file"
        ./aizog --test $problem $algorithm $node $density $iterations "$output_file"
      done
    done
  done
done