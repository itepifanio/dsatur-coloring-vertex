#include "../include/vertex.hpp"

#include <iostream>

Vertex::Vertex(int id)
{
    this->id = id;
}

Vertex::~Vertex() {}

void Vertex::addAdjacentVertex(Vertex *vertex)
{
    // check vertex exist
    for (auto it = this->adj.begin(); it != this->adj.end(); ++it) {
        if ( (*it)->id == vertex->id ) {
            return;
        }
    }

    this->adj.push_back(vertex);
    vertex->addAdjacentVertex(this);
}

bool Vertex::isAdjacent(Vertex &vertex)
{
    for (auto v = this->adj.begin(); v != this->adj.end(); ++v) {
        if ((*v)->getId() == vertex.getId()) {
            return true;
        }
    }

    return false;
}

bool Vertex::hasNeighborhoodsWithSameColor(int color, Vertex &neighborhood)
{
    for (auto it = this->adj.begin(); it != this->adj.end(); ++it) {
        if ((*it)->isColored() && (*it)->getId() != neighborhood.getId()) {
            if ((*it)->getVertexColor() == color) {
                return true;
            }
        }
    }

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

// check neighborhoods colors and the overall colors, if it has colors that is not used by 
// the vertex neighborhoods then one is applied to the current vertex. If all colors was alreasy
// aplied then it creates a new one and apply it to the current vertex.
void Vertex::colorVertex(std::set<int, std::greater<int> > &colors) 
{
    std::set<int, std::greater<int>> neighborhoodsColors;
    std::set<int, std::greater<int>> colorsStillCanBeUsed;
    for (auto it = this->adj.begin(); it != this->adj.end(); ++it)
        if ((*it)->isColored()) neighborhoodsColors.insert( (*it)->getVertexColor() );
    
    std::set_difference(
        colors.begin(), colors.end(),
        neighborhoodsColors.begin(), neighborhoodsColors.end(),
        std::inserter(colorsStillCanBeUsed, colorsStillCanBeUsed.end())
    );

    if (colorsStillCanBeUsed.size() > 0) {
        this->setCurrentColor(*colorsStillCanBeUsed.begin());
        
        return;
    }

    colors.insert(*colors.end() + 1 );
    this->setCurrentColor(*colors.end());
}

// aux

void Vertex::incrementSaturationDegree()
{
    this->saturationDegree += 1;
}

// gets and sets

int Vertex::getSaturationDegree()
{
    return this->saturationDegree;
}

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

int  Vertex::getCurrentColor()
{
    return this->currentColor;
}

void Vertex::setCurrentColor(int color)
{
    this->currentColor = color;
}


void Vertex::printAdjVertexes() {
    std::cout << "{"; 
        for (auto it = this->adj.begin(); it != this->adj.end(); ++it){
            std::cout << (*it)->getId() << ", "; 
        } 
    std::cout << "}, //";
}