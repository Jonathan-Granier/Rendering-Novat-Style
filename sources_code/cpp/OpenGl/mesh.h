/**
* @file mesh.h
* @author Jonathan Granier
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*/

#ifndef MESH_H
#define MESH_H

// GLEW lib: needs to be included first!!
#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>

#include <vector>
#include <glm/glm.hpp>
#include "vertex.h"

/**
 * @brief A Mesh is a vector of vertex and a vector of int that define the indices of vertex of polygons of the mesh.
 */
class Mesh
{
public:

    /**
     * @brief set _vertices and _indices compute the center and the radius and start setupMesh.
     * @param vertices : a vector of vertex.
     * @param indices : a vector of int that define the indices of vertex of polygons of the mesh.
     */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);


    /**
     * @brief set _vertices and _indices compute the center and the radius and start setupMesh.
     * @param vertices : a vector of vertex.
     * @param indices : a vector of int that define the indices of vertex of polygons of the mesh.
     * @param width :  the width of the mesh if it's a MNT mesh.
     * @param height : the height of the mesh if it's a MNT mesh.
     */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, int width, int height,float ymin, float ymax);

    ~Mesh();
    /**
     * @brief Draw the mesh.
     */
    void draw();


    /**
     * @brief Compute the center of the mesh
     */
    void computeCenter();

    /**
     * @brief Compute the radius of the mesh
     */
    void computeRadius();

    /**
    * @brief print the number of vertex and the number of polygone of the mesh.
    */
    void printInfo();


    /**
     * @brief get _center
     * @return the center of the mesh
     */
    glm::vec3 getCenter() const;

    /**
     * @brief get _radius
     * @return the radius of the mesh
     */
    float getRadius() const;



    /**
    * @return The width of the mesh.
    */
    int getWidth() const;

    /**
    * @return The height of the mesh.
    */
    int getHeight() const;

    /**
    * @return The min value of the DEM (or the min value of the y in all the vertex).
    */
    float getYmin() const;

    /**
    * @return The max value of the DEM (or the max value of the y in all the vertex).
    */
    float getYmax() const;


private :


    /** Vertex Array Object. */
    unsigned int _vao;
    /** Vertex Buffer Object.*/
    unsigned int _vbo;
    /** Element Buffer Object.*/
    unsigned int _ebo;

    /** Vector of vertex.*/
    std::vector<Vertex> _vertices;

    /** Vector of int that define the indices of vertex of polygons of the mesh.*/
    std::vector<unsigned int> _indices;

    /** The radius of the mesh.*/
    glm::vec3 _center;

    /** The radius of the mesh.*/
    float _radius;

    /** The width of the mesh. */
    const int _width;
    /** The height of the mesh. */
    const int _height;

    /** The min value of the DEM (or the min value of the y in all the vertex). */
    float _ymin;

    /** The max value of the DEM (or the max value of the y in all the vertex).*/
    float _ymax;


    /**
     * @brief load the mesh data into the GPU with a VAO, VBO and EBO.
     */
    void setupMesh();


};

#endif // MESH_H
