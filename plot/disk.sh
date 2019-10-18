#!/bin/bash

gnuplot -persist <<EOF

reset
set title "disk write/frame num(random)"
set xlabel "frame num"
set ylabel "disk write"
set xtics 10
set ytics 2000
set terminal png
set key right
set output 'DiskFigure/random_disk_result.png'

plot [0:100][20000:40000]'random_dis_result/fifo_dis_rand.txt' using 1:2 with linespoints linewidth 2 title 'FIFO',\
'random_dis_result/opt_dis_rand.txt' using 1:2 with linespoints linewidth 2 title 'opt',\
'random_dis_result/esc_dis_rand.txt' using 1:2 with linespoints linewidth 2 title 'esc',\
'random_dis_result/lrusc_dis_rand.txt' using 1:2 with linespoints linewidth 2 title 'lrusc'


reset
set title "disk write/frame num(locality)"
set xlabel "frame num"
set ylabel "disk write"
set xtics 10
set ytics 2000
set terminal png
set key right
set output 'DiskFigure/locality_disk_result.png'

plot [0:100][10000:32000]'locality_dis_result/fifo_dis_locality.txt' using 1:2 with linespoints linewidth 2 title 'FIFO',\
'locality_dis_result/opt_dis_locality.txt' using 1:2 with linespoints linewidth 2 title 'opt',\
'locality_dis_result/esc_dis_locality.txt' using 1:2 with linespoints linewidth 2 title 'esc',\
'locality_dis_result/lrusc_dis_locality.txt' using 1:2 with linespoints linewidth 2 title 'lrusc'


reset
set title "disk write/frame num(locality)"
set xlabel "frame num"
set ylabel "disk write"
set xtics 10
set ytics 2000
set terminal png
set key right
set output 'DiskFigure/my_ref_disk_result.png'

plot [0:100][5000:32000] 'my_ref_dis_result/fifo_dis_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'FIFO',\
'my_ref_dis_result/opt_dis_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'opt',\
'my_ref_dis_result/esc_dis_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'esc',\
'my_ref_dis_result/lrusc_dis_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'lrusc'

EOF
