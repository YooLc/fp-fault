obj-m += cr0_ne.o

KDIR := /usr/src/linux
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

install:
	sudo insmod cr0_ne.ko

uninstall:
	sudo rmmod cr0_ne

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean