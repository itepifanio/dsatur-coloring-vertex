#ifndef _GRAPH_H_ 
#define _GRAPH_H_

#include <vector>

#include "vertex.hpp"
#include <set>

class Graph {
    private:
        std::vector<Vertex*> vertexes;
        std::set<int, std::greater<int> > colors;
        int v;
        int e;
        int coloredVertexes = 0;
    public:
        Graph(std::vector<Vertex*> &vertexes);
        ~Graph();
        Vertex* findMaximumDegree();
        Vertex* findMaximumSaturationDegree();
        bool    isFullColored();
        bool    isValid(); // no adjacent vertices with the same color
        int     getTotalColors();
        void    printGraph();
        void    dsatur();
        void    incrementColoredVertexes();
        bool    isColored();
        int     getColoredVertex();
};

#endif