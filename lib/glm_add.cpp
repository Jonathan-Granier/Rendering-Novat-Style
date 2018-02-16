#include "glm_add.h"

vec3 normal(vec3 v){
    const float tmp = 1.0 / length(v);
    return vec3( v[0] * tmp, v[1] * tmp, v[2] * tmp );
}
bool hasNan(vec3 v){
   return (isnan(v[0]) || isnan(v[1]) || isnan(v[2]));
}
bool hasInf(vec3 v){
    return (isinf(v[0]) || isinf(v[1]) || isinf(v[2]));
}


vec3 cross(vec3 v1, vec3 v2){
    return vec3(
                v1[1]*v2[2] - v1[2]*v2[1],
                v1[2]*v2[0] - v1[0]*v2[2],
                v1[0]*v2[1] - v1[1]*v2[0]
                );
}


//Need for camera
float length(vec3 v){
    return sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
}

//TODO delete
mat4 translateEq(mat4 m, vec3 v){

    return glm::translate(m,v);

/*    m[0][3]=v[0];
    m[1][3]=v[1];
    m[2][3]=v[2];
    return m;
*/
}


mat4 identityTranslateEq(vec3 v){
    mat4 m = mat4(); // build identity matrices 4x4
    return translateEq(m,v);

}


mat4 quatToMat4(quat q){
    float xx = q[1]*q[1];
    float xy = q[1]*q[2];
    float xz = q[1]*q[3];
    float xw = q[1]*q[0];
    float yy = q[2]*q[2];
    float yz = q[2]*q[3];
    float yw = q[2]*q[0];
    float zz = q[3]*q[3];
    float zw = q[3]*q[0];

    mat4 mat4_custom = mat4(1-2*(yy+zz), 2*(xy+zw)  , 2*(xz-yw)  , 0,
                 2*(xy-zw)  , 1-2*(xx+zz), 2*(yz+xw)  , 0,
                 2*(xz+yw)  , 2*(yz-xw)  , 1-2*(xx+yy), 0,
                 0          , 0          , 0          , 1);
    mat4 mat4_glm = glm::toMat4(q);

    std::cout << "-----QUAT TO MAT 4 ------"        << std::endl;
    std::cout << "mat4_custom : "   << glm::to_string(mat4_custom)  << std::endl;
    std::cout << "mat4_glm : "      << glm::to_string(mat4_glm)     << std::endl;

    return mat4_custom;


}

