#include "mesh.h"



#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/string_cast.hpp>
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

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, int width, int height, float ymin, float ymax) :
    _width(width),
    _height(height),
    _ymin(ymin),
    _ymax(ymax)
{

    _vertices = vertices;
    _indices = indices;
    computeCenter();
    computeRadius();
    setupMesh();
}


Mesh::~Mesh(){
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1,&_ebo);
    glDeleteBuffers(1,&_vbo);


}


void Mesh::draw()
{

    // draw mesh
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

/* Private functions */
// CATAPULTAGE
void Mesh::setupMesh()
{
    /*_vao.create();
    _vbo.create();
    _ebo.create();

    _vao.bind();

    _vbo.bind(GL_ARRAY_BUFFER);

*/
    cout << _indices.size() << endl;
    // create buffers/arrays
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    glGenBuffers(1,&_ebo);


    glBindVertexArray(_vao);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER,_vbo);

    glBufferData(GL_ARRAY_BUFFER,_vertices.size() * sizeof(Vertex),&_vertices[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,_indices.size()*sizeof(unsigned int),&_indices[0],GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glBindVertexArray(0);


}

void Mesh::computeCenter(){
    glm::vec3 c = glm::vec3(0.0f,0.0f,0.0f);
    unsigned int i;

    // computing center
    for(i=0;i<_vertices.size();i++) {
      c += _vertices[i].position;
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
      c = _vertices[i].position-_center;

      r = sqrt(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]);
      _radius = r>_radius ? r : _radius;
    }
}

void Mesh::printInfo()
{
    cout << "number of vertice : " << _vertices.size() << endl;
    cout << "number of polygone : " << _indices.size()/3 << endl;
}


vector<float> Mesh::getNormalMapObjectSpace(){

    vector<float> normalMap;
    // Reverse texture

    unsigned int index = 0;

    for(int i = 0 ; i < _height ; i++){
        for(int j=0; j < _width; j++){
            index = i*_width + j;
            glm::vec3 n = _vertices[index].normal;
            normalMap.push_back(n.x);
            normalMap.push_back(n.y);
            normalMap.push_back(n.z);
            normalMap.push_back(0.0f);
        }
    }
    return normalMap;
}



vector<float> Mesh::getNormalMapZUp(){
    vector<float> normalMap;
    unsigned int index = 0;

    // For oriente correctly the normal map (Z up)

    glm::mat4 viewMat = glm::lookAt(glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-1.0f));
    glm::mat3 normalMat = glm::inverseTranspose(viewMat);

    // Reverse texture
    for(int i = _height-1 ; i>= 0 ; i--){
        for(int j=0; j < _width; j++){
            index = i*_width + j;
            glm::vec3 n = _vertices[index].normal;
            n = glm::normalize(normalMat * n);

            normalMap.push_back(n.x);
            normalMap.push_back(n.y);
            normalMap.push_back(n.z);
            normalMap.push_back(0.0f);
        }
    }
    return normalMap;

}



vector<float> Mesh::getHeightMap()
{
    vector<float> heightMap;
    _ymin = 10000;
    _ymax = -10000;


    for(Vertex v : _vertices){
        heightMap.push_back(v.position.y);
        if(v.position.y > _ymax){
            _ymax = v.position.y;
        }
        if(v.position.y < _ymin){
            _ymin = v.position.y;
        }
    }
    return heightMap;
}


vector<float> Mesh::getReverseHeightMap(){
    vector<float> heightMap;

    _ymin = 10000;
    _ymax = -10000;

    unsigned int index = 0;
    // Reverse texture
    for(int i = _height-1 ; i>= 0 ; i--){
        for(int j=0; j < _width; j++){
            index = i*_width + j;
            heightMap.push_back(_vertices[index].position.y);
            if(_vertices[index].position.y > _ymax){
                _ymax = _vertices[index].position.y;
            }
            if(_vertices[index].position.y < _ymin){
                _ymin = _vertices[index].position.y;
            }
        }
    }
    return heightMap;
}





glm::vec3 Mesh::getCenter() const
{
    return _center;
}

float Mesh::getRadius() const
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

float Mesh::getYmin() const
{
    return _ymin;
}

float Mesh::getYmax() const
{
    return _ymax;
}
