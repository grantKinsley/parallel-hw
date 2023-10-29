out:=loop_unfolding

.PHONY: all clean

all:
	gcc -Wall -o $(out).bin main.c util.c multiply.c -lm -pthread

clean:
	rm -rf $(out).bin
