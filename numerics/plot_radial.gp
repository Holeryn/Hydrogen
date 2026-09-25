set grid
set xlabel 'r'
set ylabel 'u(r)'
set title 'Autofunzioni radiali ridotte dell''idrogeno'
plot \
'radial_l0.dat' using 1:2 with lines lw 2 title 'l=0', \
'radial_l1.dat' using 1:2 with lines lw 2 title 'l=1', \
'radial_l2.dat' using 1:2 with lines lw 2 title 'l=2', \
'radial_l3.dat' using 1:2 with lines lw 2 title 'l=3'
