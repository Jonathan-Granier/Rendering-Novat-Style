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


    /**
     * @brief set _vertices and _indices compute the center and the radius and start setupMesh.
     * @param vertices : a vector of vertex.
     * @param indices : a vector of int that define the indices of vertex of polygons of the mesh.
     * @param width :  the width of the mesh if it's a MNT mesh.
     * @param height : the height of the mesh if it's a MNT mesh.
     */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, int width, int height, int xmax, int ymax);

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

    /**
     * @brief
     */
    void computeNormalMap();


    /**
     * @brief Return the normal Map of a MTN mesh, do nothing otherwise
     * @return the normal Map of a MNT Mesh , empty if not.
     */
    std::vector<float> getNormalMap();

    /**
     * @brief Return the heith Map of a MTN mesh, do nothing otherwise
     * @returnthe height Map of a MNT Mesh , empty if not.
     */
    std::vector<float> getHeightMap();
    /*  Mesh Data  */



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

    /**
     * @brief a Vertex Array Object.
     */
    unsigned int _VAO;


    int getWidth() const;

    int getHeight() const;

    int getYmin() const;

    int getYmax() const;

private :

    unsigned _VBO;                      /** < a Vertex Buffer Object.*/
    unsigned _EBO;                      /** < a Element Buffer Object.*/
    std::vector<Vertex> _vertices;      /** < a vector of vertex.*/
    std::vector<unsigned int> _indices; /** <  a vector of int that define the indices of vertex of polygons of the mesh.*/
    glm::vec3 _center;                  /** < The radius of the mesh.*/
    float _radius;                      /** < The radius of the mesh.*/


    const int _width;
    const int _height;
    const int _ymin;
    const int _ymax;



};

#endif // MESH_H
