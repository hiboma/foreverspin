obj-m := foreverspin.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
insmod:
	insmod foreverspin.ko
rmmod:
	rmmod foreverspin.ko
