#include "../include/report.h"
#include "../include/reader.h"

#include <vector>

int main()
{
    // std::vector<std::vector<int>> graph = {
    //     {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    //     {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0},
    //     {0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
    //     {0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0},
    //     {1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0},
    //     {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
    //     {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    //     {0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1},
    //     {0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0},
    //     {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
    //     {0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0},
    //     {0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0}};

    Reader r;

    std::vector<std::vector<int>> graph = r.readGraphFromFileToAdjMatrix("./our_graphs/3k_graph.txt", 7);

    std::vector<Vertex*> test;

    Graph g(test);

    g.tabucol(graph, (int) graph.size(), 23);

    return 0;
}
