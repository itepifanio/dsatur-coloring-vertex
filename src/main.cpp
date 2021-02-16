#include "../include/vertex.hpp"
#include "../include/graph.hpp"
#include "../lib/fort.hpp"


#include <iostream>
#include <chrono>

std::vector<Vertex *> test(int n, fort::char_table &table)
{
    std::vector<Vertex *> vertexes;
    int edges = 0;

    for (int i = 0; i < n; ++i)
    {
        Vertex *v = new Vertex(i + 1);

        vertexes.push_back(v);
    }

    for (int j = 0; j < rand() % (n - 1); j++)
    {
        for (int i = 0; i < n; ++i)
        {
            int adjacent = i;
            while (adjacent == i)
            {
                adjacent = rand() % (n - 1);
            }

            edges++;
            vertexes[i]->addAdjacentVertex(vertexes[adjacent]);
        }
    }

    table << edges;

    return vertexes;
}

int main()
{
    fort::char_table table;
    table << fort::header
         << "Graph" << "Edges" << "Colors" << "Milisseconds" << fort::endr;
    
    for (int i = 0; i <= 3600; i += 100)
    {
        table << i;

        std::vector<Vertex *> a = test(i, table);
        
        Graph *g = new Graph(a);

        auto start = std::chrono::high_resolution_clock::now();
        g->dsatur();
        auto stop = std::chrono::high_resolution_clock::now();

        if (g->hasDsaturWorked())
        {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            table << g->getTotalColors();
            table << duration.count() <<
            fort::endr;
        }
        else
        {
            std::cout << "Coloring doesnt worked. Debug the graph:" << std::endl;
            g->printGraph();
        }
    }

    std::cout << table.to_string() << std::endl;


    return 0;
}
