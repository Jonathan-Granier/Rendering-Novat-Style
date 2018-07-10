/**
* @brief Set of add function for gml lib.
* @author Jonathan Granier
*/
#ifndef GLM_ADD_H
#define GLM_ADD_H
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


#include <iostream>



namespace gml_add {
    /**
     * @brief compute the normal of a 3D vector.
     *
     * @param v     A 3D vector.
     * @return The normal of v.
     */
    glm::vec3 normal(glm::vec3 v);
    /**
     * @brief Check if v have Nan value.
     *
     * @param v     A 3D vector.
     * @return      False if v don't have nan value , true otherwise.
     */
    bool hasNan(glm::vec3 v);
    /**
     * @brief Check if v have infinity value.
     *
     * @param v     A 3D vector.
     * @return      False if v don't have infinity value , true otherwise.
     */
    bool hasInf(glm::vec3 v);

    /**
     * @brief Add v to the last line of m.
     *
     * @param m     A 4x4 matrice.
     * @param v     A 3D vector.
     * @return      A new 4x4 matrice.
     */
    glm::mat4 translateEq(glm::mat4 m,glm::vec3 v);
    /**
     * @brief Add v to the last line of a indentity matrice.
     *
     * @param v     A 3D vector.
     * @return      A new 4x4 matrice.
     */
    glm::mat4 identityTranslateEq(glm::vec3 v);

    /**
     * @brief Translate a quad to a 4x4 matrice
     *
     * @param q         A quad.
     * @return          A new 4x4 matrice. 
     */
    glm::mat4 quatToMat4(glm::quat q);
}



#endif // GLM_ADD_H
