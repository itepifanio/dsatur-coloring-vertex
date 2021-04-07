PROG = bin/exec
CC = g++
CPPFLAGS = -O0 -g -W -Wall -pedantic -std=c++17
OBJS = main.o graph.o vertex.o fort.o reader.o report.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)
	mv *.o build/

main.o: include/report.h
	$(CC) $(CPPFLAGS) -c src/main.cpp

report.o: include/graph.h include/vertex.h lib/fort.hpp include/reader.h include/report.h
	$(CC) $(CPPFLAGS) -c src/report.cpp

graph.o: include/graph.h include/vertex.h
	$(CC) $(CPPFLAGS) -c src/graph.cpp

fort.o: lib/fort.hpp
	$(CC) $(CPPFLAGS) -c lib/fort.cpp

reader.o: include/reader.h include/vertex.h
	$(CC) $(CPPFLAGS) -c src/reader.cpp

vertex.o: include/vertex.h
	$(CC) $(CPPFLAGS) -c src/vertex.cpp

clean:
	rm -f build/*.o