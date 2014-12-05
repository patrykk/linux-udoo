linux-udoo
==========

Linux Udoo Kernel

Howto install:

Compile kernel
	make uImage LOADADDR=0x10008000  modules

install modules
	make modules_install

copy kernel file
	cp arch/arm/boot/uImage /boot/
	
compile dtb file
	make imx6q-udoo.dtb
 
copu dtb file
	cp arch/arm/boot/dts/uImage  /boot/

configure your uboot 

