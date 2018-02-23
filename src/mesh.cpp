#include "mesh.h"

/* Public Function */


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->_vertices = vertices;
    this->_indices = indices;
    //this->_textures = textures;

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
    //glDrawArrays(GL_TRIANGLES,0,36);
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
    //glBindVertexArray(0);


}
