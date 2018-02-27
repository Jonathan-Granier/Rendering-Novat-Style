#ifndef MESH_H
#define MESH_H



#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>


#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h>
#include <string>
#include <vector>

#include "shader.h"
#include "vertex.h"




class Mesh
{
public:


    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~Mesh();



    /*  Mesh Data  */
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;

    unsigned int _VAO;

    /* Function */
    void Draw();
    void setupMesh();



private :

    unsigned _VBO, _EBO;

};

#endif // MESH_H
