PROG = bin/exec
CC = g++
CPPFLAGS = -O0 -g -W -Wall -pedantic -std=c++17
OBJS = main.o graph.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)
	mv *.o build/

main.o: include/graph.hpp
	$(CC) $(CPPFLAGS) -c src/main.cpp

graph.o: include/graph.hpp
	$(CC) $(CPPFLAGS) -c src/graph.cpp

clean:
	rm -f build/*.o