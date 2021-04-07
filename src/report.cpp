#include "../include/report.h"
#include "../include/reader.h"
#include "../lib/fort.hpp"

#include <string>
#include <iostream>
#include <chrono>
#include <map>

void Report::brown()
{
    Reader r;

    std::map<std::string, int> files = {
        {"3k_graph.txt", 0},
        {"4k_graph.txt", 1},
        {"5k_graph.txt", 2},
    };

    int chromaticNumbers[3] = {3, 4, 5};
    int vertexesNumbers[3] = {7, 7, 5};
    int edges[3] = {11, 18, 10};

    fort::char_table table;
    table << fort::header
          << "Graph"
          << "Vertexes"
          << "Edges"
          << "Colors"
          << "Milisseconds" << fort::endr;

    for (std::map<std::string, int>::iterator it = files.begin(); it != files.end(); ++it)
    {
        std::string nameFile = it->first;
        int vertex = vertexesNumbers[it->second];
        int chromaticNumber = chromaticNumbers[it->second]; 
        int edge = edges[it->second];

        std::vector<Vertex *> v = r.readGraphFromFile("./our_graphs/" + nameFile, chromaticNumber, vertex);

        table << nameFile;
        table << vertex;
        table << edge;

        Graph *g = new (std::nothrow) Graph(v);
        auto start = std::chrono::high_resolution_clock::now();
        g->brown();
        auto stop = std::chrono::high_resolution_clock::now();

        if (g->hasAlgorithmWorked())
        {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            table << g->getTotalColors();
            table << duration.count() << fort::endr;
        }
        else
        {
            std::cout << "Coloring doesnt worked" << std::endl;
        }
    }

    std::cout << table.to_string() << std::endl;
}

void Report::dsatur()
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
              << "Colored with"
              << "Chromatic number"
              << "Milisseconds" << fort::endr;

        table << vertexesNumbers[i];

        table << edges[i];

        Graph *g = new Graph(v);

        auto start = std::chrono::high_resolution_clock::now();
        g->dsatur();
        auto stop = std::chrono::high_resolution_clock::now();

        if (g->hasAlgorithmWorked())
        {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            table << g->dsaturTotalColor();
            table << chromaticNumbers[i];
            table << duration.count() << fort::endr;
        }
        else
        {
            std::cout << "Coloring doesnt worked" << std::endl;
        }

        std::cout << table.to_string() << std::endl;
    }
}

void Report::tabucol()
{
    std::cout << "TODO" << std::endl;
}