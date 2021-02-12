#include "../include/vertex.hpp"

Vertex::Vertex(int id)
{
    this->id = id;
}

Vertex::~Vertex() {}

void Vertex::addAdjacentVertex(Vertex *vertex)
{
    // check vertex existis
    // for (auto it = this->adj.begin(); it != this->adj.end(); ++it)
    //     if ( (*it)->id == vertex->id ) return;

    this->adj.push_back(vertex);
    vertex->addAdjacentVertex(this);
}

bool Vertex::isAdjacent(Vertex &vertex)
{
    for (auto v = this->adj.begin(); v != this->adj.end(); ++v)
        if ((*v)->getId() == vertex.getId())
            return true;

    return false;
}

bool Vertex::hasNeighborhoodsWithSameColor(int color, Vertex &neighborhood)
{
    for (auto it = this->adj.begin(); it != this->adj.end(); ++it)
        if ((*it)->isColored() && (*it)->getId() != neighborhood.getId())
            if ((*it)->getVertexColor() == color)
                return true;
    return false;
}

void Vertex::updateNeighborhoodsSaturationDegree()
{
    for (auto it = this->adj.begin(); it != this->adj.end(); ++it)
    {
        if (!(*it)->hasNeighborhoodsWithSameColor(this->getVertexColor(), *this))
        {
            (*it)->incrementSaturationDegree();
        }
    }
}

void Vertex::incrementSaturationDegree()
{
    this->saturationDegree += 1;
}

// gets and sets

bool Vertex::isColored()
{
    return this->colored;
}

int Vertex::getVertexColor()
{
    return this->currentColor;
}

int Vertex::getDegree()
{
    return (int)this->adj.size();
}

int Vertex::getId()
{
    return this->id;
}