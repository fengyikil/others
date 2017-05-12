# compile macro
ROOT := $(shell pwd)
OTHER_DIR := $(ROOT)/sWater $(ROOT)/sData $(ROOT)/sKinit
all:libkoncern other install
libkoncern:
	$(MAKE) -C $(ROOT)/sLib
other:libkoncern
	@for n in $(OTHER_DIR); do $(MAKE) -C $$n ; done
install:
	cp $(ROOT)/sKinit/Kinit	     	./INSTALL
	cp $(ROOT)/sWater/water ./INSTALL
	cp $(ROOT)/sData/data	./INSTALL
#default:init other

clean:
	-$(MAKE) -C $(ROOT)/sLib clean
	-@rm ./INSTALL/*
	-@for j in $(OTHER_DIR); do make -C $$j clean; done
.PHONY:install clean
