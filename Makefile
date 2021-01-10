
obj-m += templateModule.o

all:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo insmod templateModule.ko
	sudo rmmod templateModule.ko
	dmesg

load: templateModule.ko
	sudo insmod templateModule.ko

print:
	dmesg

unload:
	sudo rmmod templateModule.ko

create:
	sudo mknod -m 666 /dev/test1 c 124 0

delete:
	sudo rm /dev/test1
