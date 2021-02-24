#include "../include/vertex.hpp"
#include "../include/graph.hpp"
#include "../include/reader.hpp"
#include "../lib/fort.hpp"

#include <string>
#include <iostream>
#include <chrono>

int main()
{
    Reader r;

    std::string files[8] = {
        "./graphs/frb30-15-1.clq",
        "./graphs/frb35-17-1.clq",
        "./graphs/frb40-19-1.clq",
        "./graphs/frb45-21-1.clq",
        "./graphs/frb50-23-1.clq",
        "./graphs/frb53-24-1.clq",
        "./graphs/frb56-25-1.clq",
        "./graphs/frb59-26-1.clq",
    };

    int chromaticNumbers[8] = {30, 35, 40, 45, 50, 53, 56, 59};

    int vertexesNumbers[8] = {450, 595, 760, 945, 1150, 1272, 1400, 1534};

    int edges[8] = {83198, 148859, 247106, 386854, 580603, 714129, 869624, 1049256};

    for (int i = 0; i < 8; i++)
    {
        std::vector<Vertex *> v = r.readGraphFromFile(files[i], chromaticNumbers[i], vertexesNumbers[i]);

        fort::char_table table;
        table << fort::header
              << "Vertexes"
              << "Edges"
              << "Colors"
              << "Milisseconds" << fort::endr;

        table << vertexesNumbers[i];

        table << edges[i];

        Graph *g = new Graph(v);

        auto start = std::chrono::high_resolution_clock::now();
        g->dsatur();
        auto stop = std::chrono::high_resolution_clock::now();

        if (g->hasDsaturWorked())
        {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            table << g->getTotalColors();
            table << duration.count() << fort::endr;
        }
        else
        {
            std::cout << "Coloring doesnt worked. Debug the graph:" << std::endl;
            g->printGraph();
        }

        std::cout << table.to_string() << std::endl;
    }

    return 0;
}
