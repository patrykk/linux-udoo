linux-udoo
==========

Linux Udoo Kernel - 4.2.x
This branch base on 3.14.28/38-ga freescales kernel

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

    make imx6q-udoo.dtb (for quad)
    make imx6dl-udoo.dtb (for dl)
 
copy dtb file

    cp arch/arm/boot/dts/imx6q-udoo.dtb  /boot/ (for quad)
    cp arch/arm/boot/dts/imx6dl-udoo.dtb  /boot/ (for dl)

copy firmware

    cp firmware/imx/sdma/sdma-imx6q.bin /lib/firmware/imx/sdma/

configure your uboot 


Versions
--------

This has been tested with:
 - uboot-udoo-quad 2015.1 / uboot-udoo 2015.10-rc3 
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
 - HDMI video (with DVI adapter too) (kernel commands for stable HDMI: video=mxcfb0:dev=hdmi,1920x1080M@60,bpp=32)
 - LVDS support (kernel commands : video=mxcfb1:dev=ldb,LDB-WVGA,if=RGB666,bpp=32) (you need gpio-backlight for backlight support)
 - Xorg driver with xrandr
 - OpenCL
 - HDMI audio
 - Analog Audio (codec vt1613)
 - ASRC
 - sam3x port
 - i2c (no tested - could be unstable)
 - OTG (f.ex. modprobe g_mass_storage file=/dev/mmcblk0p1)
 - imx watchdog
 - imx thermal
 - GPIO - (check documentation for pins scheme and execute f.ex. "echo 40 > /sys/class/gpio/export" for gpio40)
 - PWM (for inverted polarity we added small patch) 
 - SATA - on quad
 - CAN 
 - Arduino with Udoo patch (we dont need reset sam3x via gio's. Please use last a arduino-udoo and reset via BOSSAC driver)
 - gstream vpu
 - freescale camera
 - touch screen 7' and 15'
 - CAAM
 - SPI (change disabled to okay in dtsi file)
 - 1wire (base on onewire-gpio - change disabled to okay in dtsi file)


Tested apps

 - XBMC (preloaded framebuffer libs)
 - gstream
 - chromium with EGL and flash 12.x
 - neverball
 - stellarium
 - celestia


Doesn't Work

 - PCIe

