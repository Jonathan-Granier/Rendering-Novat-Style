#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <vector>
#include <string>
#include "glm/glm.hpp"
#include "vertex.h"

class vertexLoader
{
public:
    vertexLoader();

    std::vector<Vertex> vertexFromHardCode();
    std::vector<Vertex> vertexFromObj(const std::string &path);
    std::vector<Vertex> vertexFromMNT(const std::string &path);


};

#endif // MESHLOADER_H
