#include "mesh.h"

#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>
#include <iostream>

using namespace std;
/* Public Function */


Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices) :
   _width(0),
   _height(0),
   _ymin(0),
   _ymax(0)
{
    _vertices = vertices;
    _indices = indices;
    computeCenter();
    computeRadius();
    setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, int width, int height) :
    _width(width),
    _height(height),
    _ymin(0),
    _ymax(0)
{

    _vertices = vertices;
    _indices = indices;
    computeCenter();
    computeRadius();
    setupMesh();
}


Mesh::~Mesh(){
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1,&_EBO);
    glDeleteBuffers(1, &_VBO);


}


void Mesh::Draw()
{

    // draw mesh
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

/* Private functions */
// CATAPULTAGE
void Mesh::setupMesh()
{

    // create buffers/arrays
    glGenVertexArrays(1,&_VAO);
    glGenBuffers(1,&_VBO);
    glGenBuffers(1,&_EBO);


    glBindVertexArray(_VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER,_VBO);

    glBufferData(GL_ARRAY_BUFFER,_vertices.size() * sizeof(Vertex),&_vertices[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,_indices.size()*sizeof(unsigned int),&_indices[0],GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glBindVertexArray(0);


}

void Mesh::computeCenter(){
    glm::vec3 c = glm::vec3(0.0f,0.0f,0.0f);
    unsigned int i;

    // computing center
    for(i=0;i<_vertices.size();i++) {
      c += _vertices[i].Position;
    }
    _center = c/(float)_vertices.size();


}






void Mesh::computeRadius(){
    // computing radius
    glm::vec3 c = glm::vec3(0.0f,0.0f,0.0f);
    float r;
    unsigned int i;

    _radius = 0.0;
    for(i=0;i<_vertices.size();i++) {
      c = _vertices[i].Position-_center;

      r = sqrt(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]);
      _radius = r>_radius ? r : _radius;
    }
}


vector<float> Mesh::getNormalMap(){

    vector<float> normalMap;

    for(Vertex v : _vertices){
        normalMap.push_back(v.Normal.x);
        normalMap.push_back(v.Normal.y);
        normalMap.push_back(v.Normal.z);
    }
    return normalMap;
}

vector<float> Mesh::getHeightMap()
{
    vector<float> heightMap;
    _ymin = 10000;
    _ymax = -10000;


    for(Vertex v : _vertices){
        heightMap.push_back(v.Position.y);
        if(v.Position.y > _ymax){
            _ymax = v.Position.y;
        }
        if(v.Position.y < _ymin){
            _ymin = v.Position.y;
        }
    }
    return heightMap;
}


glm::vec3 Mesh::center() const
{
    return _center;
}

float Mesh::radius() const
{
    return _radius;
}

int Mesh::getWidth() const
{
    return _width;
}

int Mesh::getHeight() const
{
    return _height;
}

int Mesh::getYmin() const
{
    return _ymin;
}

int Mesh::getYmax() const
{
    return _ymax;
}

