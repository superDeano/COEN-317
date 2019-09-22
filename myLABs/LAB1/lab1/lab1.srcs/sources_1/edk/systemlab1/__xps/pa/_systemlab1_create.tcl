######################################################
#
# XPS Tcl API script generated by PlanAhead
#
######################################################

cd "/nfs/home/d/d_chongs/Documents/COEN317/myLABS/LAB1/lab1/lab1.srcs/sources_1/edk/systemlab1"
if { [xload new systemlab1.xmp] != 0 } {
  exit -1
}
xset arch zynq
xset dev xc7z020
xset package clg484
xset speedgrade -1

xset binfo ZC702

if { [xset hier sub] != 0 } {
  exit -1
}
xset hdl vhdl
save proj
exit