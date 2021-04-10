#include "../include/graph.h"

#include <iostream>

Graph::Graph(std::vector<Vertex *> &vertexes)
{
    this->vertexes = vertexes;
    this->colors.insert(1);
}
Graph::~Graph() {
    
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

int Graph::smallestIndexJSuchThatVjColorIsEqualTo(int k)
{
    int j = 0;

    while(true) {
        if(this->vertexes[j]->getCurrentColor() == k) {
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

    while (i > 1) {
        if (updateU) {    
            U[i-1] = this->calculateU(this->vertexes[i-1], q);
        }

        if(U[i-1].empty()) {
            i = i - 1;
            q = L[i-1];
            updateU = false;
        } else {
            int j = *U[i-1].begin();

            this->vertexes[i-1]->setCurrentColor(j);
            this->colors.insert(j);

            U[i-1].erase(j);

            if (j < k) {
                if(j > q) {
                    q = q + 1;
                }

                if(i == n) {
                    // this->setColoredVertex(this->colors.size()); // store the current solution?
                    k = q;
                    j = this->smallestIndexJSuchThatVjColorIsEqualTo(k); // very weird this function, not sure if its ok

                    i = j - 1;
                    q = k - 1;
                    updateU = false;
                } else {
                    L[i-1] = q;
                    i = i + 1;
                    updateU = true;
                }
            } else {
                i = i - 1;
                q = L[i-1];
                updateU = false;
            }
        }
    }
    this->qtdColors = k;
}

int Graph::tabucolf(std::vector<Vertex *> &vertexes, std::vector<int> &colors)
{
    int sum = 0;

    for(auto it = vertexes.begin(); it != vertexes.end(); ++it) {
        for(unsigned j = 0; j < (*it)->adj.size(); j++) {
            if((*it)->getId() == (*it)->adj[j]->getId()) { // edge check
                sum += 1;
            }
        }
    }

    return sum;
}

// greedy algorithm that creates the first coloring to tabucol
void Graph::initializeTabu(std::vector<Vertex*> &vertexes, int* colors, int k)
{
// A simple greedy algorithm that leaves the assigned color  if possible, gives another legal color or 
	// assigns a random color if nothing else is available.
	// First produce a random permutation for the vertex order
	int* perm = new int[(int) vertexes.size()];
	
    for (int i = 0; i < vertexes.size(); i++) {
		perm[i] = i;
	}

	for (int i = 0; i < (int) vertexes.size(); i++) {
		int p = rand() % (int) vertexes.size();
		int h = perm[i];
		perm[i] = perm[p];
		perm[p] = h;
	}

	int* taken = new int[k + 1];

	// Insure all colors are in the range [1, ... ,k]
	for (int i = 0; i < (int) vertexes.size(); i++) {
		if (colors[i]<1 || colors[i]>k) {
            colors[i] = 1;
        }
	}

	// Go through all nodes
	for (int ii = 0; ii < (int) vertexes.size(); ii++) {
		int i = perm[ii];
		// Build a list of used colors in the nodes neighborhood
		for (int j = 1; j <= k; j++) {
			taken[j] = 0;
		}

		for (int j = 0; j < g.n; j++) {
			// numConfChecks++;
			if (i != j && g[i][j]) {
				taken[colors[j]]++;
			}
		}
		
        // if the currently assigned color is legal, leave it otherwise find a new legal color, and if not possible
		// set it to a random color.
		if (taken[colors[i]] > 0) {
			int color = (rand() % k) + 1;
			for (int j = 1; j <= k; j++) {
				if (taken[j] == 0) {
					color = j;
					break;
				}
			}

			colors[i] = color;
		}
	}

	delete[] perm;
	delete[] taken;
}

void Graph::tabucol()
{
    int k = this->vertexes.size(); // number of colors

    int condition = 7;

    int reps = 100; // fixed 

    int nbmax = 10000; // maximum number of interactions

    int *colors;

    this->initializeTabu(this->vertexes, colors, k);


    int nbtir = 0;


    // while(this->tabucolf(tabuVertexes, colors) > 0 && nbtir < nbmax) {

    // }
}