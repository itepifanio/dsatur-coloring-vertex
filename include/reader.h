
#ifndef READER_H
#define READER_H

#include "../include/vertex.h"
#include <vector>
#include <string>

class Reader {
    private:
        int  chromaticNumber;
        int  vertexes;
        void split(std::string &str, char delim, std::vector<std::string> &out);
    public:
        Reader();
        std::vector<Vertex*> readGraphFromFile(std::string filename, int chromaticNumber, int vertexes);
        std::vector<std::vector<int>> readGraphFromFileToAdjMatrix(std::string filename, int vertexes);
        int getChromaticNumber();
        int getVertexesNumber();
};

#endif