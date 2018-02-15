// Ensemble de fonction supplementaire pour la lib glm.
// Auteur : Jonathan Granier
// Fait à l'arrache





#ifndef GLM_ADD_H
#define GLM_ADD_H
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <math.h>


using namespace glm;

// Need for trackball
vec3 normal(vec3 v);
bool hasNan(vec3 v);
bool hasInf(vec3 v);
vec3 cross(vec3 v1, vec3 v2);
//Need for camera
float length(vec3 v);
mat4 translateEq(mat4 m,vec3 v);
mat4 identityTranslateEq(vec3 v);

mat4 quatToMat4(quat q);



#endif // GLM_ADD_H
