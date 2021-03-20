#include "../include/graph.hpp"

#include <iostream>

Graph::Graph(std::vector<Vertex *> &vertexes)
{
    this->vertexes = vertexes;
    this->colors.insert(1);
}

Vertex *Graph::findMaximumDegree()
{
    auto aux = this->vertexes.begin();

    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
    {
        if ((*it)->getDegree() > (*aux)->getDegree())
        {
            aux = it;
        }
    }

    return *aux;
}

// it also check tied max saturation degree
Vertex *Graph::findMaximumSaturationDegree()
{
    int maxSaturation = 0;
    std::vector<Vertex *> tied;

    Vertex *maxSaturated = nullptr;

    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
    {
        // check tied degrees
        if ((*it)->getSaturationDegree() == maxSaturation)
        {
            tied.push_back(*it);
        }

        if (((*it)->getSaturationDegree() > maxSaturation) && (!(*it)->isColored()))
        {
            maxSaturation = (*it)->getSaturationDegree();
            maxSaturated = *it;
            tied.clear();
        }
    }

    int maxDegree = 0;

    // iterates over tied vertexes and selects one of them
    for (auto it = tied.begin(); it != tied.end(); ++it)
    {
        if ((!(*it)->isColored()) && (*it)->getDegree() >= maxDegree)
        {
            maxDegree = (*it)->getDegree();
            maxSaturated = *it;
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
    return this->getColoredVertex() == (int)(this->vertexes.size() - 1);
}

void Graph::printGraph()
{
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
    {
        (*it)->printAdjVertexes();
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

    while (!this->isColored())
    {
        auto maxSaturationDegree = this->findMaximumSaturationDegree();
        maxSaturationDegree->colorVertex(this->colors);
        maxSaturationDegree->setColored(true);
        this->incrementColoredVertexes();
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
            if (currentColor == (*adj)->getCurrentColor())
                return false;
        }
    }

    return true;
}

int Graph::getTotalColors()
{
    return this->colors.size();
}

void Graph::vertexOrderAscByDegree()
{

    std::sort(
        this->vertexes.begin(), 
        this->vertexes.end(), 
        [](Vertex &v1, Vertex &v2) { // anonymous function c++
            return (v1.getDegree() < v2.getDegree());
        }
    );
}

void Graph::brown()
{
    int n = this->vertexes.size();
    this->vertexOrderAscByDegree();
    this->vertexes[0]->setCurrentColor((*this->colors.begin()));
    int i = 2;
    int k = n;
    int q = 1;
    std::set<int> U;
    int l1 = 1;
    bool updateU = true;

    while (i > 1) {
        if (updateU) {
            // calculate the set U such that Ui has the colors
            // in {1, 2, ..., q+1} minuts the ones that are not 
            // used by the neighbors of Vi
        }
    }
}