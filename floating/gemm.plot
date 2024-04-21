#------------------------------------------------------------------------------
#
# Gnuplot script for matrix experiment
#
# collect data
# > gcc -O2 mmult-blas.c -DQUIET -lcblas
# > ./collect.sh > mm-blas.dat
# > gcc -O2 mmult-transpose.c -DQUIET -lcblas
# > ./collect.sh > mm-trans.dat
#
# run plotter with
# > gnuplot -persist -c gemm.plot
#
#------------------------------------------------------------------------------
#
# This file is licensed after LGPL v3
# Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
#
#------------------------------------------------------------------------------

set term png
set grid
set key left top
set xlabel "AX size (given AY is 1200 and BY is 800)"
set ylabel "time (seconds)"

# Blas vs manual impl
set output "sgemm_blas.png"
plot 'mm-blas.dat' with linespoints title 'BLAS result',\
     'mm-trans.dat' with linespoints t 'Manual mmult'

