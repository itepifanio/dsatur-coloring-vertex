#include "../include/graph.hpp"

#include <iostream>

Graph::Graph(std::vector<Vertex*> &vertexes) {
    this->vertexes = vertexes;
    this->colors.insert(1);
}

Vertex * Graph::findMaximumDegree() 
{
    auto aux = this->vertexes.begin();

    // Iterates over the vector of vertices comparing the degrees
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
        if ((*it)->getDegree() > (*aux)->getDegree()){
            aux = it;
        }
    
    return *aux;
}

Vertex* Graph::findMaximumSaturationDegree()
{
    int maxSaturation = 0;

    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
        if ( ((*it)->getSaturationDegree() > maxSaturation) && (!(*it)->isColored()) )
            maxSaturation = (*it)->getSaturationDegree();            

    int degree = 0;

    Vertex* maxSaturated = nullptr;

    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it){
        if ( ((*it)->getSaturationDegree() == maxSaturation) && (!(*it)->isColored()) ){
            if ( (*it)->getDegree() >= degree )
            {
                degree = (*it)->getDegree();
                maxSaturated = *it;
            }
        }
    }

    return maxSaturated;
}

bool isFullColored();
bool isValid(); // no adjacent vertices with the same color
int getTotalColors();

void Graph::printGraph() {
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it){
        std::cout << std::endl;
        (*it)->printAdjVertexes();
        std::cout << (*it)->getId(); 
        std::cout << std::endl; 
    } 
}