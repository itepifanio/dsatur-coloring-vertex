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

void Graph::setColoredVertex(int c)
{
    this->coloredVertexes = c;
}

void Graph::vertexOrderAscByDegree()
{
    std::sort(
        this->vertexes.begin(), 
        this->vertexes.end(), 
        [](const Vertex *v1, const Vertex *v2) { // anonymous function c++
            return (v1->adj.size() > v2->adj.size());
        }
    );
}

std::set<int> Graph::calculateU(Vertex *v, int q)
{
    std::set<int> colorsUsedByNeightborhoods, U, result;

    for (int i = 1; i <= q+1; i++) // colors 1 to q+1
    {
        U.insert(i);
    }
    
    for (auto it = v->adj.begin(); it != v->adj.end(); it++) // neighborhood colors
    {
        colorsUsedByNeightborhoods.insert((*it)->getCurrentColor());
    }

    // calculate the diff between the U and the neighborhood colors
    std::set_difference(
        U.begin(),
        U.end(),
        colorsUsedByNeightborhoods.begin(),
        colorsUsedByNeightborhoods.end(),
        std::inserter(
            result,
            result.end()
        )
    );

    return result;
}

// there's some bug here
int Graph::smallestIndexJSuchThatVjColorIsEqualTo(int k)
{
    int j = (int) this->vertexes.size();

    for(auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it) {
        if((*it)->getCurrentColor() == k) {
            return j;
        }

        j++;
    }

    std::cout << "nooo" << std::endl;
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
    int li = 1;
    bool updateU = true;
    
    while (i > 1) {
        if (updateU) {    
            U = this->calculateU(this->vertexes[i-1], q);
        }

        if(U.empty()) {
            i = i - 1;
            q = li;
            updateU = false;
        } else {
            int j = *U.begin();
                        
            this->vertexes[i-1]->setCurrentColor(j);
            this->colors.insert(j);

            U.erase(j);

            if (j < k) {
                if(j > q) {
                    q = q + 1;
                }

                if(i == n) {
                    std::cout << "Storing solution: " << this->colors.size() << std::endl;
                    // this->setColoredVertex(this->colors.size()); // store the current solution?
                    k = q;
                    this->smallestIndexJSuchThatVjColorIsEqualTo(k); // very weird this function, not sure if its ok
                    i = j - 1;
                    q = k - 1;
                    updateU = false;
                } else {
                    li = q;
                    i = i + 1;
                    updateU = true;
                }
            } else {
                i = i - 1;
                q = li;
                updateU = false;
            }
        }
    }
}