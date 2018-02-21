#include "vertex.h"


Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords)
{
    this->Position=position;
    this->Normal=normal;
    this->TexCoords=texCoords;
}

Vertex::Vertex(float px, float py, float pz, float nx, float ny, float nz, float tu, float tv)
{
    this->Position = glm::vec3(px,py,pz);
    this->Normal = glm::vec3(nx,ny,nz);
    this->TexCoords = glm::vec2(tu,tv);
}

Vertex::Vertex(float px, float py, float pz, float tu, float tv)
{
    this->Position = glm::vec3(px,py,pz);
    this->Normal = glm::vec3(0.0f,0.0f,0.0f);
    this->TexCoords = glm::vec2(tu,tv);
}

Vertex::Vertex(float px, float py, float pz)
{
    this->Position = glm::vec3(px,py,pz);
    this->Normal = glm::vec3(0.0f,0.0f,0.0f);
    this->TexCoords = glm::vec2(0.0f,0.0f);
}


bool Vertex::operator<(const Vertex that) const{
        return memcmp((void*)this, (void*)&that, sizeof(Vertex))>0;
}
