#include "../include/graph.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <string>

Graph::Graph(){
    this->v = 0;
    this->e = 0;
}

Graph::Graph(int v){
    this->v = 0;
    this->e = 0;
    
    for(int i = 0; i < v; i++){
        this->addVertex();
    }
}

Graph::~Graph(){}

void Graph::addVertex(){
    std::vector<int> v;
    this->adj.push_back(v);
    this->v++;
}

void Graph::addEdge(int u, int v){
    this->adj[u].push_back(v);
    this->e++;
}

void Graph::printGraph() {
    for (int v = 0; v < this->v; v++){ 
        std::cout << std::endl;
        std::cout << "{"; 
        for (auto x : this->adj[v]){
            std::cout << x << ", "; 
        } 
        std::cout << "}, //" << v+1; 
        std::cout << std::endl; 
    } 
}

/**
 * Recebe número de arestas e vertices e retorna um grafo aleatório
 * e <= v*(v-1)
 */ 
Graph Graph::randomGraph(int v){
    Graph graph;

	for (int i=0; i<v; ++i) {
        graph.addVertex();

		int start = rand()%v+1;
		int end = rand()%v+1;

		if (start > end) {
			int temp = start;
			start = end;
			end = temp;
		}

		for (int j=start; j<=end; ++j) {
            if(i+1 != j) {
			    graph.addEdge(i,j);
            }
		}
    }

    return graph;
}
