set terminal pngcairo enhanced font "arial,20" fontscale 1.0 size 2048, 2048 
set output 'watercolor_curve.png'
set title "Fonction aquarelle" 
#set output 'overlay_curve.png'
set grid nopolar
set grid layerdefault   lt 0 linecolor 0 linewidth 0.500,  lt 0 linecolor 0 linewidth 0.500
set samples 21, 21
set hidden3d
set isosamples 11, 11
set view 60,300
set style data lines
set xlabel "Ombrage détails (d)" 
set xlabel  offset character -3, -2, 0 font "" textcolor lt -1 norotate
set xrange [ 0.0000 : 1.0000 ] noreverse nowriteback
set ylabel "Ombrage flou (f)" 
set ylabel  offset character 3, -2, 0 font "" textcolor lt -1 rotate
set yrange [ 0.0000 : 1.0000 ] noreverse nowriteback
set zlabel "A(d,f)" 
set zlabel  offset character -5, 0, 0 font "" textcolor lt -1 norotate
DEBUG_TERM_HTIC = 119
DEBUG_TERM_VTIC = 119
## Last datafile plotted: "$grid"
#splot (y<=0.5) ? 2*x*y : 1-2*(1-x)*(1-y)
splot y-(y-y*y)*(1-2*x) ti "A(d,f) = d-(d-d^2)(1-2f)"
