
#!/bin/bash

gnuplot -persist <<EOF

reset
set title "interrupt/frame num(random)"
set xlabel "frame num"
set ylabel "interrupt"
set xtics 10
set ytics 5000
set terminal png
set key right
set output 'interruptFigure/random_int_page_result.png'

plot [0:100][50000:150000]'random_int_result/fifo_int_rand.txt' using 1:2 with linespoints linewidth 2 title 'FIFO',\
'random_int_result/opt_int_rand.txt' using 1:2 with linespoints linewidth 2 title 'opt',\
'random_int_result/esc_int_rand.txt' using 1:2 with linespoints linewidth 2 title 'esc',\
'random_int_result/lrusc_int_rand.txt' using 1:2 with linespoints linewidth 2 title 'lrusc'

reset
set title "interrupt/frame num(locality)"
set xlabel "frame num"
set ylabel "interrupt"
set xtics 10
set ytics 5000
set terminal png
set key right
set output 'interruptFigure/locality_int_result.png'

plot [0:100][10000:130000]'locality_int_result/fifo_int_locality.txt' using 1:2 with linespoints linewidth 2 title 'FIFO',\
'locality_int_result/opt_int_locality.txt' using 1:2 with linespoints linewidth 2 title 'opt',\
'locality_int_result/esc_int_locality.txt' using 1:2 with linespoints linewidth 2 title 'esc',\
'locality_int_result/lrusc_int_locality.txt' using 1:2 with linespoints linewidth 2 title 'lrusc'

reset
set title "interrupt/frame num(my_ref)"
set xlabel "frame num"
set ylabel "interrupt"
set xtics 10
set ytics 5000
set terminal png
set key right
set output 'interruptFigure/my_ref_int_result.png'

plot [0:100][10000:130000]'my_ref_int_result/fifo_int_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'FIFO',\
'my_ref_int_result/opt_int_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'opt',\
'my_ref_int_result/esc_int_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'esc',\
'my_ref_int_result/lrusc_int_my_ref.txt' using 1:2 with linespoints linewidth 2 title 'lrusc'

EOF


