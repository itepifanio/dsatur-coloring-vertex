
#ifndef READER_H
#define READER_H

#include "../include/vertex.hpp"
#include <vector>
#include <string>

class Reader {
    private:
        int  chromaticNumber;
        int  vertexes;
    public:
        std::vector<Vertex*> readGraphFromFile(std::string filename);
        int getChromaticNumber();
        int getVertexesNumber();
};

#endif