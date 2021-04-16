#include "../include/graph.h"

#include <iostream>
#include <map>

Graph::Graph(std::vector<Vertex *> &vertexes)
{
    this->vertexes = vertexes;
    this->colors.insert(1);
}
Graph::~Graph()
{
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

int Graph::dsaturTotalColor() // dsatur
{
    return this->colors.size();
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

bool Graph::hasAlgorithmWorked()
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
    return this->qtdColors;
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
        });
}

std::set<int> Graph::calculateU(Vertex *v, int q)
{
    std::set<int> colorsUsedByNeightborhoods, U, result;

    for (int i = 1; i <= q + 1; i++) // colors 1 to q+1
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
            result.end()));

    return result;
}

int Graph::smallestIndexJSuchThatVjColorIsEqualTo(int k)
{
    int j = 0;

    while (true)
    {
        if (this->vertexes[j]->getCurrentColor() == k)
        {
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
    std::vector<std::set<int>> U;
    std::vector<int> L;

    U.reserve(n);
    L.reserve(n);

    L[0] = 1;

    bool updateU = true;

    while (i > 1)
    {
        if (updateU)
        {
            U[i - 1] = this->calculateU(this->vertexes[i - 1], q);
        }

        if (U[i - 1].empty())
        {
            i = i - 1;
            q = L[i - 1];
            updateU = false;
        }
        else
        {
            int j = *U[i - 1].begin();

            this->vertexes[i - 1]->setCurrentColor(j);
            this->colors.insert(j);

            U[i - 1].erase(j);

            if (j < k)
            {
                if (j > q)
                {
                    q = q + 1;
                }

                if (i == n)
                {
                    // this->setColoredVertex(this->colors.size()); // store the current solution?
                    k = q;
                    j = this->smallestIndexJSuchThatVjColorIsEqualTo(k); // very weird this function, not sure if its ok

                    i = j - 1;
                    q = k - 1;
                    updateU = false;
                }
                else
                {
                    L[i - 1] = q;
                    i = i + 1;
                    updateU = true;
                }
            }
            else
            {
                i = i - 1;
                q = L[i - 1];
                updateU = false;
            }
        }
    }
    this->qtdColors = k;
}

void Graph::tabucol(std::vector<std::vector<int>> graph, int numberColors, int tabuSize, int reps, int maxIterations)
{
    std::vector<int> colors;

    for (int i = 0; i < numberColors; i++)
    {
        colors.push_back(i);
    }

    int iterations = 0;

    std::vector<std::pair<int, int>> tabuList;

    std::map<int, int> solution;

    // generate random solution
    for (int i = 0; i < (int)graph.size(); i++)
    {
        solution[i] = colors[rand() % (int)colors.size()];
    }

    std::map<int, int> aspirationalLevel; // A(z)

    while (iterations < maxIterations)
    {
        std::set<int> moveCandidates;
        
        int vertex = -1;
        int localConflicts = 0;

        for (int i = 0; i < (int)graph.size(); i++)
        {
            for (int j = (i + 1); j < (int)graph.size(); j++)
            {
                if (graph[i][j] > 0)
                {
                    if (solution[i] == solution[j])
                    {
                        moveCandidates.insert(i);
                        moveCandidates.insert(j);
                        localConflicts += 1;
                    }
                }
            }
        }

        if (localConflicts == 0)
        {
            break; // best colour found
        }

        // generate neighbourhoods solutions
        std::map<int, int> newSolution;

        for (int r = 0; r < reps; r++)
        {
            std::vector<int> vertexes;

            vertexes.reserve(moveCandidates.size());

            std::copy(moveCandidates.begin(), moveCandidates.end(), std::back_inserter(vertexes));

            // choose a node to move
            vertex = vertexes[rand() % (int)vertexes.size()];

            int newColor = colors[rand() % ((int)colors.size() - 1)];

            if (solution[vertex] == newColor)
            {
                newColor = (int)*colors.end(); // swap last color with the current
            }

            // creating neighborhood solution
            std::map<int, int> aux(solution); // aux to copy the solution to a new map
            newSolution = aux;

            newSolution[vertex] = newColor;

            // counting conflicts
            int newConflicts = 0;

            for (int i = 0; i < (int)graph.size(); i++)
            {
                for (int j = (i + 1); j < (int)graph.size(); j++)
                {
                    if (graph[i][j] > 0 && newSolution[i] == newSolution[j])
                    {
                        newConflicts += 1;
                    }
                }
            }

            if (newConflicts < localConflicts)
            {                                                          // found a better solution
                if (newConflicts <= aspirationalLevel[localConflicts]) // TODO::check this
                {
                    aspirationalLevel[localConflicts] = newConflicts - 1;

                    auto it = std::find(tabuList.begin(), tabuList.end(), std::make_pair(vertex, newColor));

                    if (it != tabuList.end())
                    {
                        tabuList.erase(it);
                        break;
                    }
                }
                else
                {

                    auto it = std::find(tabuList.begin(), tabuList.end(), std::make_pair(vertex, newColor));

                    if (it != tabuList.end()) // tabu move isnt good enought
                    {
                        continue;
                    }
                }

                break;
            }
        }

        // At this point, either found a better solution,
        // or ran out of reps, using the last solution generated

        // The current node color will become tabu.
        // add to the end of the tabu queue
        tabuList.push_back(std::make_pair(vertex, solution[vertex]));
        if ((int)tabuList.size() > tabuSize)
        {                                     // queue full
            tabuList.erase(tabuList.begin()); // remove the oldest move
        }

        // Move to next iteration of tabucol with new solution
        // solution = newSolution;
        iterations += 1;
    }

    // At this point, either conflict_count is 0 and a coloring was found,
    // or ran out of iterations with no valid coloring.
    for (auto it = solution.begin(); it != solution.end(); it++)
    {
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    }
}