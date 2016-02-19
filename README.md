linux-udoo
==========

Linux Udoo Kernel - 4.4.x
This branch base on 3.14.54-ga freescales kernel - vivante driver 5.0.11p7.3

Howto install:
-----------------

Configure kernel

    make menuconfig (or use udoo config file: make udoo_quad_defconfig)

Compile kernel

    make zImage modules (or just: make -j5)

install modules

    make modules_install

copy kernel file

    cp arch/arm/boot/zImage /boot/
	
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
 - xf86-video-imx-viv 5.0.11.p7.1
 - gst-imx 0.11.1.r10.gb94ea3c-1
 - imx-lib 5,1
 - imx-vpu 5.4.31-1 (3.14.38)
 - firmware-imx 5.2
 - imx-gpu-viv-g2d 5.0.11.p7.1 (previous name: gpu-viv-g2d) 
 - imx-gpu-viv-(x11|fb) 5.0.11.p7.1 (previous name: gpu-viv-bin-mx6q)
 - libfslvpuwrap 1.0.58 (3.14.38)
 - libfslcodec - 4.0.7
 - libfslparser - 4.0.7
 - libimxvpuapi (branch vpulib-backend - git) 
 - Xorg server 1.17.x
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

