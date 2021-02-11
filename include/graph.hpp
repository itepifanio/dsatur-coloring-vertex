#ifndef _GRAPH_H_ 
#define _GRAPH_H_

#include <vector>

class Graph {
    private:
        std::vector<std::vector<int>> adj;
        int v;
        int e;
    public:
        Graph();
        Graph(int v);
        ~Graph();
        void addEdge(int u, int v);
        void addVertex();
        void printGraph();
        static Graph randomGraph(int v);
};

#endif