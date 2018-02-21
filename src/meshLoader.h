#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include "progressbar.h"

#include "glm/glm.hpp"
#include "mesh.h"





class meshLoader
{
public:
    meshLoader();

    //std::vector<Vertex> vertexFromHardCode();
    Mesh* vertexFromHardCode();
    Mesh* vertexFromObj(const std::string &path);
    Mesh* vertexFromMNT(const std::string &path);

private:

    Mesh *indexVBO(std::vector<Vertex> vertices);
    bool getSimilarVertexIndex(Vertex &v,std::map<Vertex,unsigned int> &VertexToOutIndex, unsigned int &result);
};

#endif // MESHLOADER_H
