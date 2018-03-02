#include "vertex.h"
#include <string.h>
#include <iostream>

using namespace std;
using namespace glm;
Vertex::Vertex(vec3 position, vec3 normal, vec2 texCoords)
{
    this->Position=position;
    this->Normal=normal;
    this->TexCoords=texCoords;
}

Vertex::Vertex(float px, float py, float pz, float nx, float ny, float nz, float tu, float tv)
{
    this->Position = vec3(px,py,pz);
    this->Normal = vec3(nx,ny,nz);
    this->TexCoords = vec2(tu,tv);
}

Vertex::Vertex(float px, float py, float pz, float tu, float tv)
{
    this->Position = vec3(px,py,pz);
    this->Normal = vec3(0.0f,0.0f,0.0f);
    this->TexCoords = vec2(tu,tv);
}

Vertex::Vertex(float px, float py, float pz)
{
    this->Position = vec3(px,py,pz);
    this->Normal = vec3(0.0f,0.0f,0.0f);
    this->TexCoords = vec2(0.0f,0.0f);
}


bool Vertex::operator<(const Vertex that) const{
        return memcmp((void*)this, (void*)&that, sizeof(Vertex))>0;
}

void Vertex::print(){
    cout  << "Position : (" << Position.x << "," << Position.y << "," << Position.z
          << ") Normal : (" << Normal.x << "," << Normal.y << "," << Normal.z
          << ") TeXCoords : (" << TexCoords.x  << "," << TexCoords.y << ")"
          << endl;
}
