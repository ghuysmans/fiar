all: fiar
fiar: board.o fiar.o
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm *.o fiar
