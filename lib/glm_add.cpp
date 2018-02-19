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

mat4 translateEq(mat4 m, vec3 v){
    m[3][0]+=v[0];
    m[3][1]+=v[1];
    m[3][2]+=v[2];
    return m;

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

    return mat4(1-2*(yy+zz) , 2*(xy-zw)  , 2*(xz+yw)  , 0,
                 2*(xy+zw)  , 1-2*(xx+zz), 2*(yz-xw)  , 0,
                 2*(xz-yw)  , 2*(yz+xw)  , 1-2*(xx+yy), 0,
                 0          , 0          , 0          , 1);

}

