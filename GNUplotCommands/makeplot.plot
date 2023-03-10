#!/usr/bin/gnuplot -persist
width=0.25
bin(x, s) = int (x/s)
set boxwidth width
plot 'edges.dat' u (bin($1,width)):(1.0) \
s f w boxes fs solid 0.5 title 'гистограмма'

