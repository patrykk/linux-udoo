linux-udoo
==========

Linux Udoo Kernel
-----------------

Howto install:


Compile kernel

    make uImage LOADADDR=0x10008000  modules

install modules

    make modules_install

copy kernel file

    cp arch/arm/boot/uImage /boot/
	
compile dtb file

    make imx6q-udoo.dtb
 
copy dtb file

    cp arch/arm/boot/dts/uImage  /boot/

copy firmware

    cp firmware/imx/sdma/sdma-imx6q.bin /lib/firmware/imx/sdma/

configure your uboot 


Versions
--------

This has been tested with:
    - uboot-udoo-quad 2014.04, 
    - libcec-imx6 13.20141201
    - xf86-video-imx-viv 3.10.31_1.1.0 beta
    - gst-imx 0.9.9
    - imx-lib 3.10.31_1.1.0
    - imx-vpu 3.10.31_1.1.0
    - firmware-imx 3.10.31_1.1.0


What Works and What Doesn't
--------

Work:


 - wifi (stable)
 - VPU
 - GPU 
 - HDMI video
 - Xorg driver with xrandr
 - OpenCL
 - HDMI audio (unstable)
 - sam3x port
 - i2c (no tested - could be unstable) 
 

 - XBMC 


Doesn't Work


 - CAAM (very unstable)
 - PCIe
 - OTG (no tested)
 - freescale camera



