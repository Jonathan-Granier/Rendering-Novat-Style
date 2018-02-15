#include "mesh.h"

/* Public Function */


Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
    this->_vertices = vertices;
    this->_indices = indices;
    this->_textures = textures;
}


Mesh::~Mesh(){
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1,&_EBO);
    glDeleteBuffers(1, &_VBO);
}


void Mesh::Draw(Shader shader)
{


    unsigned int normalNr=1;

    for(unsigned int i=0;i<_textures.size();i++){
        string number;
        string name=_textures[i].type;

        if(name == "texture_normal"){
            number = std::to_string(normalNr++);
        }
        glActiveTexture(GL_TEXTURE0 + i);
        shader.setInt((name + number).c_str(),i);
        //glUniform1i(glGetUniformLocation(shader._ID, (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, _textures[i].id);
    }


    // draw mesh
    glBindVertexArray(_VAO);
    //glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);


    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

/* Private functions */
// CATAPULTAGE
void Mesh::setupMesh()
{

    // create buffers/arrays
    glGenVertexArrays(1,&_VAO);
    glGenBuffers(1,&_VBO);
  //  glGenBuffers(1,&_EBO);


    glBindVertexArray(_VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER,_VBO);

    glBufferData(GL_ARRAY_BUFFER,_vertices.size() * sizeof(Vertex),&_vertices[0],GL_STATIC_DRAW);
 //   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_EBO);
 //   glBufferData(GL_ELEMENT_ARRAY_BUFFER,_indices.size()*sizeof(unsigned int),&_indices[0],GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FLOAT,sizeof(Vertex),(void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    //glBindVertexArray(0);


}
