
#ifndef GRAPHS_VERTEX_H
#define GRAPHS_VERTEX_H

#include <vector>

class Vertex {
    private:
        int  id;
        int  saturationDegree = 0;
        int  currentColor = -1;
        bool colored = false;
        std::vector<Vertex*> adj;
    public:
        Vertex(int id);
        ~Vertex();
        void addAdjacentVertex(Vertex *vertex);
        int  getDegree();
        int  getId();
        // void removeAdjacentVertex(Vertex *vertex);
        bool isAdjacent(Vertex &vertex);
        bool hasNeighborhoodsWithSameColor(int color, Vertex &vertex);
        void updateNeighborhoodsSaturationDegree();
        void incrementSaturationDegree();
        bool isColored();
        int  getVertexColor();
        void colorVertex(std::vector<int> &colors);
};

#endif