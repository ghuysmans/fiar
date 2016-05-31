all: fiar
fiar: board.o ai.o fiar.o
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm *.o fiar
