include ../common.mk
OBJ = init.o
Kinit:$(OBJ) ../sLib/libcommon.a
	$(CC)  $^ $(LDFLAGS)  -o $@
	@echo $(ROOT) .............................................
.PHONY:clean
clean:
	@rm -f *.o *.d* Kinit

