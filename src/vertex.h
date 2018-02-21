#ifndef VERTEX_H
#define VERTEX_H

#include <string.h>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"



class Vertex
{
public:
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;



    Vertex(glm::vec3 position,glm::vec3 normal,glm::vec2 texCoords);
    Vertex(float px, float py, float pz, float nx, float ny, float nz, float tu, float tv);
    Vertex(float px, float py, float pz, float tu, float tv);
    Vertex(float px, float py, float pz);
    bool operator<(const Vertex that) const;




};





#endif // VERTEX_H
