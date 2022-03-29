
all: main server

main: main.c
	gcc main.c -o main

server: server.c
	gcc server.c -o server

.PHONY: clean all

clean:
	rm -f *.o main server
