#include "vertex.h"
#include <string.h>
#include <iostream>

using namespace std;
using namespace glm;
Vertex::Vertex()
{
    this->position = vec3(0.0f,0.0f,0.0f);
    this->normal = vec3(0.0f,0.0f,0.0f);
    this->texCoords = vec2(0.0f,0.0f);
}

Vertex::Vertex(vec3 position, vec3 normal, vec2 texCoords)
{
    this->position=position;
    this->normal=normal;
    this->texCoords=texCoords;
}

Vertex::Vertex(vec3 position, vec3 normal)
{
    this->position=position;
    this->normal=normal;
    this->texCoords = vec2(0.0f,0.0f);
}

Vertex::Vertex(float px, float py, float pz, float nx, float ny, float nz, float tu, float tv)
{
    this->position = vec3(px,py,pz);
    this->normal = vec3(nx,ny,nz);
    this->texCoords = vec2(tu,tv);
}

Vertex::Vertex(float px, float py, float pz, float tu, float tv)
{
    this->position = vec3(px,py,pz);
    this->normal = vec3(0.0f,0.0f,0.0f);
    this->texCoords = vec2(tu,tv);
}

Vertex::Vertex(float px, float py, float pz)
{
    this->position = vec3(px,py,pz);
    this->normal = vec3(0.0f,0.0f,0.0f);
    this->texCoords = vec2(0.0f,0.0f);
}


bool Vertex::operator<(const Vertex that) const{
        return memcmp((void*)this, (void*)&that, sizeof(Vertex))>0;
}

void Vertex::print(){
    cout  << "position : (" << position.x << "," << position.y << "," << position.z
          << ") normal : (" << normal.x << "," << normal.y << "," << normal.z
          << ") texCoords : (" << texCoords.x  << "," << texCoords.y << ")"
          << endl;
}

void Vertex::printNormal(){
    cout << "(" << normal.x << "," << normal.y << "," << normal.z << ")" ;
}
