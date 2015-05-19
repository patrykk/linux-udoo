linux-udoo
==========

Linux Udoo Kernel - 4.0.x
This branch will base on 3.14.28-ga freescales kernel

Howto install:
-----------------

Configure kernel
    make menuconfig (or some other way)

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
 - uboot-udoo-quad 2015.1 
 - libcec-imx6 13.20141201
 - xf86-video-imx-viv 3.10.53_1.1.0 (for lxdm need some patch)
 - gst-imx 0.10.1.r7
 - imx-lib 3.14.28_1.0.0
 - imx-vpu 5.4.28-1 (3.14.28)
 - firmware-imx 3.14.28_1.0.0
 - imx-gpu-viv-g2d 5.0.11.p4.4 (previous name: gpu-viv-g2d) 
 - imx-gpu-viv-(x11|fb) 5.0.11.p4.4 (previous name: gpu-viv-bin-mx6q)
 - libfslvpuwrap 1.0.58 (3.14.28)
 - libimxvpuapi
 - Xorg server 1.16.x
 - libcec-imx6 13.20141201


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
 - PWM (for inverted polarity need small patch) 
 - SATA - on quad
 - CAN (xcvr problem)
 - Arduino with Udoo patch (export gpio 0 and 117: "echo 0 > /sys/class/gpio/export; echo 117 > /sys/class/gpio/export")
 - XBMC 
 - gstream vpu
 - freescale camera (no tested)


Doesn't Work

 - CAAM (very unstable)
 - PCIe

