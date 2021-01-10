
obj-m += getuidSyscallHookModule.o

all:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo insmod getuidSyscallHookModule.ko
	sudo rmmod getuidSyscallHookModule.ko
	dmesg

load: getuidSyscallHookModule.ko
	sudo insmod getuidSyscallHookModule.ko

print:
	dmesg

unload:
	sudo rmmod getuidSyscallHookModule.ko

create:
	sudo mknod -m 666 /dev/test1 c 124 0

delete:
	sudo rm /dev/test1
