
#ifndef GRAPHS_VERTEX_H
#define GRAPHS_VERTEX_H

#include <vector>
#include <set>
#include <algorithm>

class Vertex {
    private:
        int  id;
        int  saturationDegree = 0;
        bool colored = false;
        int  currentColor = -1;
    public:
        std::vector<Vertex*> adj;
        Vertex(int id);
        ~Vertex();
        void addAdjacentVertex(Vertex *vertex);
        int  getDegree();
        int  getId();
        bool isAdjacent(Vertex &vertex);
        bool hasNeighborhoodsWithSameColor(int color, Vertex &vertex);
        void updateNeighborhoodsSaturationDegree();
        void incrementSaturationDegree();
        bool isColored();
        int  getVertexColor();
        int  getSaturationDegree();
        int  getCurrentColor();
        void setCurrentColor(int color);
        void printAdjVertexes();
        void setColored(bool b);
        void updateCurrentSaturationDegree();
        void colorVertex(std::set<int, std::greater<int>> &colors);
};

#endif