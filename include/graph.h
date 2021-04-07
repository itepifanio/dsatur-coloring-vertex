#ifndef _GRAPH_H_ 
#define _GRAPH_H_

#include <vector>

#include "vertex.h"
#include <set>

class Graph {
    private:
        std::vector<Vertex*> vertexes;
        std::set<int, std::greater<int>> colors;
        int v;
        int e;
        int coloredVertexes = 0;
        int qtdColors = 1;
    public:
        Graph(std::vector<Vertex*> &vertexes);
        ~Graph();
        Vertex* findMaximumDegree();
        Vertex* findMaximumSaturationDegree();
        bool    isFullColored();
        int     getTotalColors();
        void    printGraph();
        void    dsatur();
        void    incrementColoredVertexes();
        bool    isColored();
        int     getColoredVertex();
        void    setColoredVertex(int c);
        bool    hasDsaturWorked();
        void    brown();
        void    vertexOrderAscByDegree();
        std::set<int>    calculateU(Vertex *v, int q);
        int     smallestIndexJSuchThatVjColorIsEqualTo(int k);
};

#endif