#include "../include/graph.hpp"

#include <iostream>

Graph::Graph(std::vector<Vertex *> &vertexes)
{
    this->vertexes = vertexes;
    // this->colors.insert(1);
}

Vertex *Graph::findMaximumDegree()
{
    auto aux = this->vertexes.begin();

    // Iterates over the vector of vertices comparing the degrees
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
    {
        if ((*it)->getDegree() > (*aux)->getDegree())
        {
            aux = it;
        }
    }

    return *aux;
}

Vertex *Graph::findMaximumSaturationDegree()
{
    int maxSaturation = 0;

    Vertex *maxSaturated = nullptr;

    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
    {
        if (((*it)->getSaturationDegree() > maxSaturation) && (!(*it)->isColored()))
        {
            maxSaturation = (*it)->getSaturationDegree();
            maxSaturated = *it;
        }
    }

    int degree = 0;

    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
    {
        if (((*it)->getSaturationDegree() == maxSaturation) && (!(*it)->isColored()))
        {
            if ((*it)->getDegree() >= degree)
            {
                degree = (*it)->getDegree();
                maxSaturated = *it;
            }
        }
    }

    return maxSaturated;
}

void Graph::incrementColoredVertexes()
{
    this->coloredVertexes += 1;
}

int Graph::getColoredVertex()
{
    return this->coloredVertexes;
}

bool Graph::isColored()
{
    bool colored = true;
    
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it) {
        std::cout << "current vertex color" << (*it)->getCurrentColor() << std::endl;
        if ( !(*it)->isColored() ) return false;
    }
    
    return colored;
}

void Graph::printGraph()
{
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
    {
        std::cout << std::endl;
        (*it)->printAdjVertexes();
        std::cout << (*it)->getId() << " Color " << (*it)->getCurrentColor();
        std::cout << std::endl;
    }
}

void Graph::dsatur()
{
    if (this->vertexes.size() == 0)
    {
        return;
    }

    // the first iteration ignores the saturation degree
    auto maxVertexDegree = this->findMaximumDegree();
    maxVertexDegree->setColored(true);
    maxVertexDegree->colorVertex(this->colors);
    maxVertexDegree->updateNeighborhoodsSaturationDegree();
    maxVertexDegree->updateCurrentSaturationDegree();

    while(! this->isColored()) {
        auto maxSaturationDegree = this->findMaximumSaturationDegree();
        maxSaturationDegree->colorVertex(this->colors);
        maxSaturationDegree->setColored(true);
        std::cout << "is colored " << (bool)maxSaturationDegree->isColored() << std::endl;
        // this->incrementColoredVertexes();
        maxSaturationDegree->updateNeighborhoodsSaturationDegree();
    }
}

bool Graph::hasDsaturWorked()
{
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
    {
        int currentColor = (*it)->getCurrentColor();
        
        for (auto adj = (*it)->adj.begin(); adj != (*it)->adj.end(); ++adj)
        {
            if (currentColor == (*adj)->getCurrentColor()) return false;
        }
    }

    return true;
}

int Graph::getTotalColors() {
    return this->colors.size();
}