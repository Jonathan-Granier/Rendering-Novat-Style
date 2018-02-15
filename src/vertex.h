#ifndef VERTEX_H
#define VERTEX_H

#include "glm/glm.hpp"

class Vertex
{
public:
    Vertex(glm::vec3 position,glm::vec3 normal,glm::vec2 texCoords);
    Vertex(float px, float py, float pz, float nx, float ny, float nz, float tu, float tv);
    Vertex(float px, float py, float pz, float tu, float tv);
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;




};

#endif // VERTEX_H
