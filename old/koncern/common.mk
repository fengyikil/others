# compile macro
CC	= gcc
ROOT := $(shell pwd)
INCL = -I../include
CFLAGS	= -O2 -Wall
CFLAGS +=$(INCL) 
LDFLAGS	=-lrt -lpthread 
include $(sources:.c=.d)
%.d : %.c
	set -e; rm -f $@;\
	$(CC) -MM $(CFLAGS) $< > $@.$$$$ ;\
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' <$@.$$$$ > $@;\
	    rm -f $@.$$$$
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
