#include "../include/vertex.hpp"
#include "../include/graph.hpp"

#include <iostream>

int main()
{
    // TODO::BUILD THE VERTEXES THEN PASS TO THE GRAPH


    // add every step to run dsatur.


    std::vector<Vertex*> vertexes;

    Vertex *v1 = new Vertex(1);
    Vertex *v2 = new Vertex(2);
    Vertex *v3 = new Vertex(3);
    Vertex *v4 = new Vertex(4);
    Vertex *v5 = new Vertex(5);
    Vertex *v6 = new Vertex(6);
    Vertex *v7 = new Vertex(7);
    Vertex *v8 = new Vertex(8);
    
    v1->addAdjacentVertex(v2);
    v1->addAdjacentVertex(v3);
    v1->addAdjacentVertex(v4);
    v2->addAdjacentVertex(v6);
    v2->addAdjacentVertex(v5);
    v3->addAdjacentVertex(v7);
    v4->addAdjacentVertex(v7);
    v5->addAdjacentVertex(v6);
    v5->addAdjacentVertex(v8);
    v6->addAdjacentVertex(v8);
    v7->addAdjacentVertex(v8);
    
    vertexes.push_back(v1);
    vertexes.push_back(v2);
    vertexes.push_back(v3);
    vertexes.push_back(v4);
    vertexes.push_back(v5);
    vertexes.push_back(v6);
    vertexes.push_back(v7);
    vertexes.push_back(v8);

    Graph *g = new Graph(vertexes);

    g->printGraph();

    
    return 0;
}
