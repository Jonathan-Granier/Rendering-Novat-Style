#ifndef MESH_H
#define MESH_H


#include <vector>
#include <glm/glm.hpp>
#include "vertex.h"

/**
 * @brief A Mesh is a vector of vertex and a vector of int that define the indices of vertex of polygons of the mesh.
 */
class Mesh
{
public:

    /* Functions */
    /**
     * @brief set _vertices and _indices compute the center and the radius and start setupMesh.
     * @param vertices : a vector of vertex.
     * @param indices : a vector of int that define the indices of vertex of polygons of the mesh.
     */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~Mesh();
    /**
     * @brief Draw the mesh.
     */
    void Draw();
    /**
     * @brief load the mesh data into the GPU with a VAO, VBO and EBO.
     */
    void setupMesh();


    /**
     * @brief Compute the center of the mesh
     */
    void computeCenter();

    /**
     * @brief Compute the radius of the mesh
     */
    void computeRadius();

    /*  Mesh Data  */

    /**
     * @brief a Vertex Array Object.
     */
    unsigned int _VAO;


    /**
     * @brief get _center
     * @return the center of the mesh
     */
    glm::vec3 center() const;

    /**
     * @brief get _radius
     * @return the radius of the mesh
     */
    float radius() const;

private :
    /**
     * @brief a Vertex Buffer Object.
     */
    unsigned _VBO;
    /**
     * @brief a Element Buffer Object.
     */
    unsigned _EBO;

    /**
     * @brief a vector of vertex.
     */
    std::vector<Vertex> _vertices;
    /**
     * @brief a vector of int that define the indices of vertex of polygons of the mesh.
     */
    std::vector<unsigned int> _indices;

    /**
     * @brief The center of the mesh.
     */
    glm::vec3 _center;

    /**
     * @brief The radius of the mesh.
     */
    float _radius;


};

#endif // MESH_H
