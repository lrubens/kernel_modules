# obj-m := ml_module.o
obj-m := ml_module_out.o
ml_module_out-objs := ml_module.o mm.o
MY_CFLAGS += -g -DDEBUG
ccflags-y += ${MY_CFLAGS}
ccflags-y := -I./ -std=gnu99 -fstack-protector 
all default: modules
# ml_module_out-objs : ml_module.o mm.o
# CFLAGS_ml_module.o := -I./ -std=gnu99 -fstack-protector -msoft-float -msse -msse2 -msse3 -msse4
# mm.o:
# 	gcc -O2 -c mm.c -C -o mm.o
modules: 
	gcc -O2 -c mm.c -C -o mm.o
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f mm.o
test:
	sudo dmesg -C
	sudo insmod ml_module_out.ko
	sudo rmmod ml_module_out
	sudo dmesg
