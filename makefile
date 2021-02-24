PROG = bin/exec
CC = g++
CPPFLAGS = -O0 -g -W -Wall -pedantic -std=c++17
OBJS = main.o graph.o vertex.o fort.o reader.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)
	mv *.o build/

main.o: include/graph.hpp lib/fort.hpp
	$(CC) $(CPPFLAGS) -c src/main.cpp

graph.o: include/graph.hpp include/vertex.hpp
	$(CC) $(CPPFLAGS) -c src/graph.cpp

fort.o: lib/fort.hpp
	$(CC) $(CPPFLAGS) -c lib/fort.cpp

reader.o: include/reader.hpp include/vertex.hpp
	$(CC) $(CPPFLAGS) -c src/reader.cpp

vertex.o: include/vertex.hpp
	$(CC) $(CPPFLAGS) -c src/vertex.cpp

clean:
	rm -f build/*.o