// Ensemble de fonction supplementaire pour la lib glm.
// Auteur : Jonathan Granier
// Fait à l'arrache





#ifndef GLM_ADD_H
#define GLM_ADD_H
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


#include <iostream>


namespace gml_add {
    // Need for trackball
    /**
     * @brief
     *
     * @param v
     * @return glm::vec3
     */
    glm::vec3 normal(glm::vec3 v);
    /**
     * @brief
     *
     * @param v
     * @return bool
     */
    bool hasNan(glm::vec3 v);
    /**
     * @brief
     *
     * @param v
     * @return bool
     */
    bool hasInf(glm::vec3 v);
    //Need for camera
    /**
     * @brief
     *
     * @param m
     * @param v
     * @return glm::mat4
     */
    glm::mat4 translateEq(glm::mat4 m,glm::vec3 v);
    /**
     * @brief
     *
     * @param v
     * @return glm::mat4
     */
    glm::mat4 identityTranslateEq(glm::vec3 v);
    /**
     * @brief
     *
     * @param q
     * @return glm::mat4
     */
    glm::mat4 quatToMat4(glm::quat q);
}



#endif // GLM_ADD_H
