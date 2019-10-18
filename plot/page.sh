#!/bin/bash

gnuplot -persist <<EOF

reset
set title "page fault/frame num(random)"
set xlabel "frame num"
set ylabel "page fault"
set xtics 10
set ytics 5000
set terminal png
set key right
set output 'PageFigure/random_page_result.png'

plot [0:100][40000:100000]'random_result/fifo_rand.txt' using 1:2 with linespoints linewidth 2 title 'FIFO',\
'random_result/opt_rand.txt' using 1:2 with linespoints linewidth 2 title 'opt',\
'random_result/esc_rand.txt' using 1:2 with linespoints linewidth 2 title 'esc',\
'random_result/lrusc_rand.txt' using 1:2 with linespoints linewidth 2 title 'lrusc'


reset
set title "page fault/frame num(locality)"
set xlabel "frame num"
set ylabel "page fault"
set xtics 10
set ytics 4000
set terminal png
set key right
set output 'PageFigure/locality_page_result.png'

plot [0:100][25000:80000]'locality_result/fifo_locality.txt' using 1:2 with linespoints linewidth 2 title 'FIFO',\
'locality_result/opt_locality.txt' using 1:2 with linespoints linewidth 2 title 'opt',\
'locality_result/esc_locality.txt' using 1:2 with linespoints linewidth 2 title 'esc',\
'locality_result/lrusc_locality.txt' using 1:2 with linespoints linewidth 2 title 'lrusc'


reset
set title "page fault/frame num(my_ref)"
set xlabel "frame num"
set ylabel "page fault"
set xtics 10
set ytics 5000
set terminal png
set key right
set output 'PageFigure/my_ref_page_result.png'

plot [0:100][5000:100000]'my_ref_result/fifo_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'FIFO',\
'my_ref_result/opt_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'opt',\
'my_ref_result/esc_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'esc',\
'my_ref_result/lrusc_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'lrusc'

EOF
