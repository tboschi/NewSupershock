#!/data/tboschi/gnuplot/bin/gnuplot -persist
#
#    
#    	G N U P L O T
#    	Version 5.2 patchlevel 4    last modified 2018-06-01 
#    
#    	Copyright (C) 1986-1993, 1998, 2004, 2007-2018
#    	Thomas Williams, Colin Kelley and many others
#    
#    	gnuplot home:     http://www.gnuplot.info
#    	faq, bugs, etc:   type "help FAQ"
#    	immediate help:   type "help"  (plot window: hit 'h')
# set terminal qt 0 font "Sans,9"
# set output
unset clip points
set clip one
unset clip two
set errorbars front 1.000000 
set border 31 front lt black linewidth 1.000 dashtype solid
set zdata 
set ydata 
set xdata 
set y2data 
set x2data 
set boxwidth
set style fill  empty border
set style rectangle back fc  bgnd fillstyle   solid 1.00 border lt -1
set style circle radius graph 0.02 
set style ellipse size graph 0.05, 0.03 angle 0 units xy
set dummy x, y
set format x "% h" 
set format y "% h" 
set format x2 "% h" 
set format y2 "% h" 
set format z "% h" 
set format cb "% h" 
set format r "% h" 
set ttics format "% h"
set timefmt "%d/%m/%y,%H:%M"
set angles radians
set tics back
unset grid
unset raxis
set theta counterclockwise right
set style parallel front  lt black linewidth 2.000 dashtype solid
set key title "" center
set key fixed right top vertical Right noreverse enhanced autotitle nobox
set key noinvert samplen 4 spacing 1 width 0 height 0 
set key maxcolumns 0 maxrows 0
set key noopaque
unset label
unset arrow
set style increment default
unset style line
unset style arrow
set style histogram clustered gap 2 title textcolor lt -1
unset object
set style textbox transparent margins  1.0,  1.0 border  lt -1 linewidth  1.0
set offsets 0, 0, 0, 0
set pointsize 1
set pointintervalbox 1
set encoding utf8
unset polar
unset parametric
unset decimalsign
unset micro
unset minussign
set view 60, 30, 1, 1
set view azimuth 0
set rgbmax 255
set samples 100, 100
set isosamples 10, 10
set surface 
unset contour
set cntrlabel  format '%8.3g' font '' start 5 interval 20
set mapping cartesian
set datafile separator whitespace
unset hidden3d
set cntrparam order 4
set cntrparam linear
set cntrparam levels auto 5 unsorted
set cntrparam firstlinetype 0
set cntrparam points 5
set size ratio 0 1,1
set origin 0,0
set style data points
set style function lines
unset xzeroaxis
unset yzeroaxis
unset zzeroaxis
unset x2zeroaxis
unset y2zeroaxis
set xyplane relative 0.5
set tics scale  1, 0.5, 1, 1, 1
set mxtics default
set mytics default
set mztics default
set mx2tics default
set my2tics default
set mcbtics default
set mrtics default
set nomttics
set xtics border in scale 1,0.5 mirror norotate  autojustify
set xtics  norangelimit logscale autofreq 
set ytics border in scale 1,0.5 mirror norotate  autojustify
set ytics  norangelimit logscale autofreq 
set ztics border in scale 1,0.5 nomirror norotate  autojustify
set ztics  norangelimit autofreq 
unset x2tics
unset y2tics
set cbtics border in scale 1,0.5 mirror norotate  autojustify
set cbtics  norangelimit autofreq 
set rtics axis in scale 1,0.5 nomirror norotate  autojustify
set rtics  norangelimit autofreq 
unset ttics
set title "" 
set title  font "" norotate
set timestamp bottom 
set timestamp "" 
set timestamp  font "" norotate
set trange [ * : * ] noreverse nowriteback
set urange [ * : * ] noreverse nowriteback
set vrange [ * : * ] noreverse nowriteback
set xlabel "" 
set xlabel  font "" textcolor lt -1 norotate
set x2label "" 
set x2label  font "" textcolor lt -1 norotate
set xrange [ 0.01 : 2 ] noreverse writeback
set x2range [ * : * ] noreverse writeback
set ylabel "" 
set ylabel  font "" textcolor lt -1 rotate
set y2label "" 
set y2label  font "" textcolor lt -1 rotate
set yrange [ * : * ] noreverse writeback
set y2range [ * : * ] noreverse writeback
set zlabel "" 
set zlabel  font "" textcolor lt -1 norotate
set zrange [ * : * ] noreverse writeback
set cblabel "" 
set cblabel  font "" textcolor lt -1 rotate
set cbrange [ * : * ] noreverse writeback
set rlabel "" 
set rlabel  font "" textcolor lt -1 norotate
set rrange [ * : * ] noreverse writeback
unset logscale
set logscale y 10
set logscale x 10
unset jitter
set zero 1e-08
set lmargin  -1
set bmargin  -1
set rmargin  -1
set tmargin  -1
set locale "en_GB.UTF-8"
set pm3d explicit at s
set pm3d scansautomatic
set pm3d interpolate 1,1 flush begin noftriangles noborder corners2color mean
set pm3d nolighting
set palette positive nops_allcF maxcolors 0 gamma 1.5 color model RGB 
set palette rgbformulae 7, 5, 15
set colorbox default
set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
set style boxplot candles range  1.50 outliers pt 7 separation 1 labels auto unsorted
set loadpath 
set fontpath 
set psdir
set fit brief errorvariables nocovariancevariables errorscaling prescale nowrap v5
GNUTERM = "qt"
## Last datafile plotted: "m/nRHO0_E_M_m_U.dat"
plot "m/nEM_E_M_T_m_U.dat"  u 1:2 w l lw 2 lc 2, "d/nEM_E_M_T_d_U.dat"  u 1:2 w l lw 2 dt 2 lc 2, \
     "m/EPI_E_M_T_m_U.dat"  u 1:2 w l lw 2 lc 3, "d/EPI_E_M_T_d_U.dat"  u 1:2 w l lw 2 dt 2 lc 3, \
     "m/MPI_E_M_T_m_U.dat"  u 1:2 w l lw 2 lc 7, "d/MPI_E_M_T_d_U.dat"  u 1:2 w l lw 2 dt 2 lc 7, \
     "m/EKA_E_M_T_m_U.dat"  u 1:2 w l lw 2 lc 1, "d/EKA_E_M_T_d_U.dat"  u 1:2 w l lw 2 dt 2 lc 1, \
     "m/MKA_E_M_T_m_U.dat"  u 1:2 w l lw 2 lc 5, "d/MKA_E_M_T_d_U.dat"  u 1:2 w l lw 2 dt 2 lc 5, \
     "m/MKAx_E_M_T_m_U.dat" u 1:2 w l lw 2 lc 6, "d/MKAx_E_M_T_d_U.dat" u 1:2 w l lw 2 dt 2 lc 6, \
     "m/EKAx_E_M_T_m_U.dat" u 1:2 w l lw 2 lc 0, "d/EKAx_E_M_T_d_U.dat" u 1:2 w l lw 2 dt 2 lc 0, \
     "m/ERHO_E_M_T_m_U.dat" u 1:2 w l lw 2 lc 4, "d/ERHO_E_M_T_d_U.dat" u 1:2 w l lw 2 dt 2 lc 4, \
     "m/MRHO_E_M_T_m_U.dat" u 1:2 w l lw 2 lc 8, "d/MRHO_E_M_T_d_U.dat" u 1:2 w l lw 2 dt 2 lc 8, \
#    EOF
