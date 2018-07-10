#ifndef VERTEX_H
#define VERTEX_H

#include "glm/glm.hpp"



/**
 * @brief A Type class that define a vertex with his position , his normal and his texture coordinates
 * The normal must be normalize and the texture coordinates must be between 0 and 1.
 */
class Vertex
{
public:
     /*!< The position of the vertex */
    glm::vec3 position;
     /*!< The normal of the vertex */
    glm::vec3 normal;
     /*!< the texture coordinates of the vertex */
    glm::vec2 texCoords;

    /**
     * @brief Basic constructor , all equal 0
     */
    Vertex();

    /**
     * @brief Constructor with 3 3D vectors.
     * @param position  3D vectors that define the position.
     * @param normal    3D vectors that define the normal.
     * @param texCoords 2D vectors that define the texture coordinates.
     */
    Vertex(glm::vec3 position,glm::vec3 normal,glm::vec2 texCoords);
    /**
     * @brief Constructor with 3 3D vectors.
     * @param position  3D vectors that define the position.
     * @param normal    3D vectors that define the normal.
     */
    Vertex(glm::vec3 position,glm::vec3 normal);

    /**
     * @brief Constructor with each value of each vector
     * @param px    the x of the position.
     * @param py    the y of the position.
     * @param pz    the z of the position.
     * @param nx    the x of the normal.
     * @param ny    the y of the normal.
     * @param nz    the z of the normal.
     * @param tu    the u of the texture coordinates.
     * @param tv    the v of the texture coordinates.
     */
    Vertex(float px, float py, float pz, float nx, float ny, float nz, float tu, float tv);
    /**
     * @brief Constructor with position and texture coordinates , the normal is initialized to (0,0,0).
     * @param px    the x of the position.
     * @param py    the y of the position.
     * @param pz    the z of the position.
     * @param tu    the u of the texture coordinates.
     * @param tv    the v of the texture coordinates.
     */
    Vertex(float px, float py, float pz, float tu, float tv);
    /**
     * @brief Constructor with only the position, the normal is initialized to (0,0,0) and texture coordinates are initilized to 0.
     * @param px    the x of the position.
     * @param py    the y of the position.
     * @param pz    the z of the position.
     */
    Vertex(float px, float py, float pz);

    /**
     * @brief test if that is superior to this
     * @param that   a vertex
     * @return true if that > this, else otherwise.
     */
    bool operator<(const Vertex that) const;
    /**
     * @brief Print the actual vertex.
     */
    void print();
};





#endif // VERTEX_H
