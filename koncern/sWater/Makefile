include ../common.mk
OBJ = water.o hot.o 
#all: water
water:$(OBJ) ../sLib/libcommon.a
	$(CC)  $^ $(LDFLAGS)  -o $@
	@echo $(ROOT) .............................................
.PHONY:clean
clean:
	@rm -f *.o *.d* water

