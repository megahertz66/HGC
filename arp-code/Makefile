CC=gcc
SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRC))
INC=$(patsubst %.c,%.h,$(SRC))
EXE=test

$(EXE):$(OBJS)
	$(CC) -o $@ $^
%.o:%.c $(INC)
	$(CC) -o $@ -c $^
.PHONY:clean rebuild
clean:
	rm -f $(OBJS) $(EXE)
rebuild:clean $(EXE)