CC	= gcc
CFLAGS	= -O2 -Wall
LDFLAGS	=-lrt -lpthread
sources = can.c bit.c
OBJ=$(sources:.c=.o)
all:libcommon.a
libcommon.a:$(OBJ)
	ar r $@ $^
include $(sources:.c=.d)
%.d : %.c
	set -e; rm -f $@;\
	$(CC) -MM $(CFLAGS) $< > $@.$$$$ ;\
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' <$@.$$$$ > $@;\
	    rm -f $@.$$$$
%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f  *.o *.d libcommon.a
