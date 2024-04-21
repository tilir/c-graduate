#!/bin/bash

for ((i = 1600; i < 5000; i = i + 400)); do
  ./a.out $i 1200 800
done
