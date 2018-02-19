#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>

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
    bool getSimilarVertexIndex(Vertex &in_v,std::vector<Vertex> &out_v,unsigned int & result);
    bool is_near(float v1, float v2);
};

#endif // MESHLOADER_H
