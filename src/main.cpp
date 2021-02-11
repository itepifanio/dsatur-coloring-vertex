#include "../include/graph.hpp"

int main()
{
    Graph g;
    
    for(int i = 0; i < 8; i++){
        g.addVertex();
    }

    g.addEdge(0, 1);
    g.addEdge(0,2);
    g.addEdge(0,3);
    g.addEdge(0,6);
    g.addEdge(1,0);
    g.addEdge(1,4);
    g.addEdge(1,5);
    g.addEdge(2,0);
    g.addEdge(2,6);
    g.addEdge(3,0);
    g.addEdge(3,6);
    g.addEdge(4,1);
    g.addEdge(4,5);
    g.addEdge(4,7);
    g.addEdge(5,1);
    g.addEdge(5,7);
    g.addEdge(5,4);
    g.addEdge(6,0);
    g.addEdge(6,2);
    g.addEdge(6,3);
    g.addEdge(6,7);
    g.addEdge(7,6);
    g.addEdge(7,5);
    g.addEdge(7,4);

    g.printGraph();

    return 0;
}
