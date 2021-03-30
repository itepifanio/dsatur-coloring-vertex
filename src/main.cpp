#include "../include/vertex.hpp"
#include "../include/graph.hpp"
#include "../include/reader.hpp"
#include "../lib/fort.hpp"

#include <string>
#include <iostream>
#include <chrono>
#include <map>

std::vector<Vertex *> test(int n, fort::char_table &table)
{
    std::vector<Vertex *> vertexes;
    int edges = 0;

    for (int i = 0; i < n; ++i)
    {
        Vertex *v = new Vertex(i + 1);

        vertexes.push_back(v);
    }

    std::srand( ( unsigned int )std::time( nullptr ) );

    for (int j = 0; j < std::rand() % 10000; ++j)
    {
        for (int i = 0; i < n; ++i)
        {
            int adjacent = i;
            while (adjacent == i)
            {
                adjacent = std::rand() % (n - 1);
            }

            edges++;
            vertexes[i]->addAdjacentVertex(vertexes[adjacent]);
        }
    }

    table << edges;

    return vertexes;
}

void print(std::vector<Vertex *> v, fort::char_table &table)
{
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
        auto d = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        table << "error";
        table << d.count() << fort::endr;
        std::cout << "Coloring doesnt worked. Debug the graph:" << std::endl;
    }
}

int main(int argc, char** argv)
{
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

    for(int j = 10; j < 100; j+=10) {
        table << j;
        table << j;
        print(test(j, table), table);
    }

    // if(argc == 3) 
    // {
    //     std::string nameFile(argv[1]);
    //     int i = files[nameFile];
        
    //     Reader r;
    //     std::vector<Vertex *> v = r.readGraphFromFile("./our_graphs/"+nameFile, chromaticNumbers[i], vertexesNumbers[i]);
        
    //     table << nameFile;
    //     table << vertexesNumbers[i];
    //     table << edges[i];

    //     print(v, nameFile, table);
    // } else {
    //     Reader r;
    //     for (std::map<std::string,int>::iterator it=files.begin(); it!=files.end(); ++it) {
    //         std::vector<Vertex *> v = r.readGraphFromFile("./our_graphs/"+it->first, chromaticNumbers[it->second], edges[it->second]);
            
    //         table << nameFile;
    //         table << vertexesNumbers[it->second];
    //         table << edges[it->second];

    //         print(v, it->first, table);
    //     }
    // }

    std::cout << table.to_string() << std::endl;

    return 0;
}
