include ../common.mk
OBJ = data.o
#all: data
data:$(OBJ) ../sLib/libcommon.a 
	$(CC) $^ $(LDFLAGS)  -o $@

.PHONY:clean
clean:
	@rm -f *.o *.d* data

