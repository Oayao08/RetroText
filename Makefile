CC=gcc
CFLAGS=-Wall -Wextra -std=c99
SRC=src/main.c
OUT=retrotext

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
