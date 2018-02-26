// Ensemble de fonction supplementaire pour la lib glm.
// Auteur : Jonathan Granier
// Fait à l'arrache





#ifndef GLM_ADD_H
#define GLM_ADD_H
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <math.h>
#include <iostream>


namespace gml_add {
    // Need for trackball
    glm::vec3 normal(glm::vec3 v);
    bool hasNan(glm::vec3 v);
    bool hasInf(glm::vec3 v);
    //Need for camera
    glm::mat4 translateEq(glm::mat4 m,glm::vec3 v);
    glm::mat4 identityTranslateEq(glm::vec3 v);
    glm::mat4 quatToMat4(glm::quat q);
}



#endif // GLM_ADD_H
