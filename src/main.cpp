#include "../include/vertex.hpp"
#include "../include/graph.hpp"

#include <iostream>
#include <chrono>

std::vector<Vertex*> test(int n)
{
    std::vector<Vertex*> vertexes;
    int edges = 0;

	for (int i=0; i < n; ++i) {
        Vertex *v = new Vertex(i+1);

		int start = rand()%n+1;
		int end = rand()%n+1;

		if (start > end) {
			int temp = start;
			start = end;
			end = temp;
		}

		for (int j = start; j<=end; ++j) {
            if(i+1 != j) {
                edges++;
			    v->addAdjacentVertex(new Vertex(rand()));
            }
		}

        vertexes.push_back(v);
    }

    std::cout << "Number of edges on the graph" << std::endl;
    std::cout << edges << std::endl;
    
    return vertexes;
}

int main()
{
    
    // for(int i = 0; i < 1000; i += 100) {
        int i = 8;
        std::vector<Vertex*> a = test(i);

        Graph *g = new Graph(a);

        auto start = std::chrono::high_resolution_clock::now(); 
        g->dsatur();
        auto stop = std::chrono::high_resolution_clock::now();

        if(g->hasDsaturWorked()) {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            
            std::cout <<
                "Graph with " << i << " vertexes "
                << "calculates " << g->getTotalColors() << " color and it"
                << " was executed in "
                << duration.count() << " microseconds."
            << std::endl;
        } else {
            std::cout << "Coloring doesnt worked. Debug the graph:" << std::endl;
            g->printGraph();
        }
    // }
    
    return 0;
}
