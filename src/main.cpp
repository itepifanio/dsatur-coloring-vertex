#include "../include/vertex.hpp"
#include "../include/graph.hpp"

#include <iostream>
#include <chrono>

std::vector<Vertex *> test(int n)
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

    std::cout << "     " << edges;

    return vertexes;
}

int main()
{

    std::cout << "| Graph | Edges | Colors | Milisseconds |" << std::endl;
    
    for (int i = 0; i < 3600; i += 100)
    {
        std::cout << "  " << i;

        std::vector<Vertex *> a = test(i);
        
        Graph *g = new Graph(a);

        auto start = std::chrono::high_resolution_clock::now();
        g->dsatur();
        auto stop = std::chrono::high_resolution_clock::now();

        if (g->hasDsaturWorked())
        {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            std::cout << "       " << g->getTotalColors();
            std::cout << "       " << duration.count() <<
            std::endl;
        }
        else
        {
            std::cout << "Coloring doesnt worked. Debug the graph:" << std::endl;
            g->printGraph();
        }
    }

    return 0;
}
