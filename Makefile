obj-m += ml_module.o
MY_CFLAGS += -g -DDEBUG
ccflags-y += ${MY_CFLAGS}
ccflags-y := -I./ -std=gnu99 -fstack-protector -msoft-float -msse -msse2 -msse3 -msse4
# CFLAGS_ml_module.o := -I./ -std=gnu99 -fstack-protector -msoft-float -msse -msse2 -msse3 -msse4
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
	dmesg -C
	insmod ml_module.ko
	rmmod ml_module
	dmesg
