linux-udoo
==========

Linux Udoo Kernel - 3.18.x
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
 - HDMI audio
 - ASRC
 - sam3x port
 - i2c (no tested - could be unstable)
 - OTG (f.ex. modprobe g_mass_storage file=/dev/mmcblk0p1)
 - imx watchdog
 - imx thermal
 - GPIO - (check documentation for pins scheme and execute f.ex. "echo 40 > /sys/class/gpio/export" for gpio40)
 - SATA
 - CAN

 - Arduino with Udoo patch (export gpio 0 and 1: "echo 0 > /sys/class/gpio/export; echo 1 > /sys/class/gpio/export")
 - XBMC 
 - gstream vpu


Doesn't Work

 - CAAM (very unstable)
 - PCIe
 - freescale camera

