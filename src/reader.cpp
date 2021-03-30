#include "../include/reader.hpp"

#include <string>
#include <iostream>
#include <fstream>

Reader::Reader()
{
    this->vertexes = 0;
    this->chromaticNumber = 0;
}

std::vector<Vertex*> Reader::readGraphFromFile(std::string filename, int chromaticNumber, int vertexesNumber) 
{
    this->chromaticNumber = chromaticNumber;
    this->vertexes = vertexesNumber;

    std::vector<Vertex *> vertexes;

    std::ifstream file(filename);

	std::string line = "";

    std::vector<std::string> word;

    std::getline(file, line); // ignore head of the file

    line = "";

    // initialize vertexes
    for (int i = 0; i <= vertexesNumber; ++i)
    {
        Vertex *v = new Vertex(i + 1);

        vertexes.push_back(v);
    }

	while (std::getline(file, line))
	{
        std::size_t ini_pos = line.find(" ");
        std::string name = line.substr(0, ini_pos+1);

        ini_pos = line.find(" ");
        std::string aux = line.substr(ini_pos+1);
        std::size_t end_pos = aux.find(" ");
        
        std::string vertex1 = aux.substr(0, end_pos);
        std::string vertex2 = aux.substr(end_pos+1);

        // std::cout << std::stoi(vertex1) << std::endl; 
        // std::cout << std::stoi(vertex2) << std::endl;
        // std::cout << vertexes[std::stoi(vertex1)]->getId() << std::endl;   
        
        vertexes[std::stoi(vertex1)]->addAdjacentVertex(vertexes[std::stoi(vertex2)]);
	}

	file.close();

	return vertexes;
}

void Reader::split(std::string &str, char delim, std::vector<std::string> &out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}