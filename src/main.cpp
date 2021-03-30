#include "../include/vertex.hpp"
#include "../include/graph.hpp"
#include "../include/reader.hpp"
#include "../lib/fort.hpp"

#include <string>
#include <iostream>
#include <chrono>
#include <map>

int main(int argc, char** argv)
{
    Reader r;

    std::map<std::string, int> files = {
        {"3k_graph.txt", 0},
        {"4k_graph.txt", 1},
    };

    int chromaticNumbers[2] = {3, 4};
    int vertexesNumbers[2] = {7, 7};
    int edges[2] = {11, 18};
    
    if(argc == 2) 
    {
        std::string nameFile(argv[1]);
        int i = files[nameFile];
        std::vector<Vertex *> v = r.readGraphFromFile("./our_graphs/"+nameFile, chromaticNumbers[i], vertexesNumbers[i]);
        fort::char_table table;
        table << fort::header
                << "Graph"
                << "Vertexes"
                << "Edges"
                << "Colors"
                << "Milisseconds" << fort::endr;

        table << nameFile;
        table << vertexesNumbers[i];
        table << edges[i];
        
        Graph *g = new (std::nothrow) Graph(v);
        auto start = std::chrono::high_resolution_clock::now();
        g->brown();
        auto stop = std::chrono::high_resolution_clock::now();

        if (g->hasDsaturWorked())
        {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            table << g->getTotalColors();
            table << duration.count() << fort::endr;
            // g->printGraph();
        }
        else
        {
            std::cout << "Coloring doesnt worked. Debug the graph:" << std::endl;
        }

        std::cout << table.to_string() << std::endl;
    }

    return 0;
}
