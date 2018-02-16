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

using namespace glm;

// Need for trackball
vec3 normal(vec3 v);
bool hasNan(vec3 v);
bool hasInf(vec3 v);
//Need for camera
mat4 translateEq(mat4 m,vec3 v);
mat4 identityTranslateEq(vec3 v);

mat4 quatToMat4(quat q);



#endif // GLM_ADD_H
