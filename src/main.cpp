#include "../include/vertex.hpp"
#include "../include/graph.hpp"
#include "../include/reader.hpp"
#include "../lib/fort.hpp"

#include <string>
#include <iostream>
#include <chrono>

int main()
{
    Vertex *a = new Vertex(1);
    Vertex *b = new Vertex(2);
    Vertex *c = new Vertex(3);
    Vertex *d = new Vertex(4);
    Vertex *e = new Vertex(5);
    Vertex *f = new Vertex(6);
    Vertex *g = new Vertex(7);
    Vertex *h = new Vertex(8);

    a->addAdjacentVertex(b);
    a->addAdjacentVertex(g);
    a->addAdjacentVertex(f);
    f->addAdjacentVertex(h);
    f->addAdjacentVertex(d);
    d->addAdjacentVertex(e);
    d->addAdjacentVertex(c);
    c->addAdjacentVertex(e);
    c->addAdjacentVertex(b);
    e->addAdjacentVertex(b);

    std::vector<Vertex*> graph; 
    
    graph.push_back(a);
    graph.push_back(b);
    graph.push_back(c);
    graph.push_back(d);
    graph.push_back(e);
    graph.push_back(f);
    graph.push_back(g);
    graph.push_back(h);

    Graph *graphs = new Graph(graph);

    graphs->brown();

    return 0;
}
