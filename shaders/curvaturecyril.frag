#version 420

#extension GL_ARB_texture_cube_map_array : enable

#define M_PI 3.14159265358979f
#define M_2tPI 6.28318530717959f
#define M_PI_2 1.5707963267949f
#define M_4tPI 12.5663706143592f
#define M_PI_Sq 9.86960440108934f

#define EPSILON 0.00001f

in vec3 ReflectDir;
in vec3 v3NormalWorld;
in vec2 v2TexCoord;
in vec4 v4TangentWorld;
in vec3 v3ViewWorld;
in vec3 v3PosWorld ;

///subroutine void RenderPassType();
///subroutine uniform RenderPassType RenderPass;

uniform sampler2D PositionTex ;
uniform sampler2D NormalTex;

uniform sampler2D DirectionsTex ;				// contains directions as vec3 in rgb, for the gaussian profile basis.
uniform sampler2D AnisoGaussianCoefsTex ;		// contains coefficients of the anisotropic gaussians on this basis

uniform samplerCube CubeMapTex;

uniform samplerCubeArray CubeMapArrTex;

uniform int DrawSkyBoxMode;

uniform int   LMax;
uniform int   ENVMAP_WIDTH;
uniform int   AntialiasingMode;
uniform int   MaxExcentricitySteps;
uniform int   MaxScaleSteps;
uniform float ReflectFactor;
uniform vec4  MaterialColor;
uniform float Exposure;
uniform float GammaInv;
uniform int   ImageWidth ;
uniform float HorizontalFieldOfView ;
uniform vec3  WorldCameraPosition ;
uniform vec2  ScreenSize;
uniform vec3  xx;
uniform vec3  yy;
uniform vec3  zz;

uniform int passNum;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec3 PositionData;
layout (location = 2) out vec3 NormalData;

vec4 getAnisotropicGaussianCoef(int scale_index,int excentricity_index,int l,int m)
{
  // Each line l of the direction texture contains all directions for -l<=m<=l

  vec4 res ;
  res.rgb = texelFetch(DirectionsTex,ivec2(l+m,l),0).rgb ;
  //res.rgb = texelFetch(DirectionsTex,ivec2(3+3,3),0).rgb ;
  //res.a = 1.0f ;
  //return res ;

  if(scale_index < 0) scale_index = 0 ;
  if(scale_index >= MaxScaleSteps) scale_index = MaxScaleSteps-1 ;
  if(excentricity_index < 1) excentricity_index = 0 ;
  if(excentricity_index >= MaxExcentricitySteps) excentricity_index = MaxExcentricitySteps;

//l=0;m=0;excentricity_index=1;scale_index=1;
//vec4 c = texelFetch(AnisoGaussianCoefsTex,ivec2( 0 ,1),0) ;
//res.a = c[0] ;

  vec4 c = texelFetch(AnisoGaussianCoefsTex,ivec2(  (l*(l+1)+m)/4,  (excentricity_index-1)*MaxScaleSteps + scale_index  ),0) ;
  res.a = c[ (l*(l+1)+m) % 4 ] ;

  return res ;
}

// Screen-space shape operator

vec3 getShapeOperator()
{
  // Hi mahdi.
  //
  // The last version of SS curvature we used was a devil approximation that we cannot use anymore because this
  // one is going to be used in the extreme conditions of pixels close to silouhette.
  //
  // What we need is:
  //			- the principal curvature directions in 3D, v1 and v2, which are tangent to the surface, so orthogonal to the normal n.
  //			- the main curvatures in these directions c1 and c2.
  //
  // To get them, we estimate the shape operator, which is the matrix
  //        S = [ a b ]
  //            [ c d ]
  // ...that gives the derivative of the normal when you move tangent to the surface in a direction indicated by 2D vector v:
  //
  //          S * v = \frac{ d n }{ d v }
  //
  // Once we have v1,v2,c1 and c2, we know that a symmetric gaussian beam that comes from a pixel, will bounce on the
  // surface and spread according to c1 and c2, in directions v1 and v2.
  // Along v1, for instance, the angular spread of a beam of angular size \delta\theta, after reflexion will be
  //
  //					\delta\theta_1 = \delta\theta d / \cos\theta  * c1
  //
  //    ... where
  //           d                   is the distance between the camera and the objet we hit
  //           \delta\theta        is the angular with of a pixel ( Fov / W, basically )
  //           c1                  curvature along v1
  //           \theta              angle between normal and view direction.
  //
  // Now to compute the shape operator, we need
  //
  //    1 - to compute the 3D vectors X and Y, tangent to the surface, that project on (1,0,0) and (0,1,0) in
  //        the screen (assuming z=(0,0,1) is the depth direction). We have therefore X.n=0 and Y.n=0.
  //        Assuming P is the point in world space and C is the camera in world space:
  //
  //            Vector xx = ScreenToWorld( vec3(1,0,0) )
  //            Vector yy = ScreenToWorld( vec3(0,1,0) )
  //            Vector zz = ScreenToWorld( vec3(0,0,1) )
  //
  //            X = normalize(  xx - (n.xx)zz/ (n.zz) ) 			// you can check, X.n=0
  //            Y = normalize(  yy - (n.yy)zz/ (n.zz) ) 			// you can check, Y.n=0
  //
  //    2 - compute the values of the shape operator along X and Y using:
  //
  //            vec3 Sx = ( textureFetch(normals, current_pixel + (1,0)) - textureFetch(normals,current_pixel) ) * (X.xx)
  //            vec3 Sy = ( textureFetch(normals, current_pixel + (0,1)) - textureFetch(normals,current_pixel) )	* (Y.yy)
  //
  //            // we multiply by X.xx and Y.yy to account for the projection on the surface
  //
  //    3 - define a vector B, orthogonal to X and n (Y is not, actually), and express B as a linear combination of X and Y
  //
  //            vec3 B = n^X										// with this, we have B= (Y-(X.Y)X) / |Y-(X.Y)X|
  //            float l1 = -X.Y / norm(Y - (X.Y)X)
  //            float l2 =    1 / norm(Y - (X.Y)X)		// we now have B=l1 X + l2 Y
  //
  //    4 - now convert Sx and Sy into the (X,B,n) coordinate system
  //
  //            vec2 shape_operator_times_X = ( X.Sx , B.Sx ) 		// normally B.Sx=0. To be verified.
  //            vec2 shape_operator_times_Y = ( X.Sy , B.Sy )
  //
  //    5 - compute the shape operator, by computing both columns as 2D vectors:
  //
  //            Vec2 shape_operator_column1 = shape_operator_times_X
  //            Vec2 shape_operator_column2 = shape_operator_times_X * l1 + shape_operator_times_Y * l2
  //
  //        // normally you should have shape_operator_column1[1] == shape_operator_column2[0], since the matrix is symmetric


        // step 1.
        vec2 uv = gl_FragCoord.xy / ScreenSize ;
        vec3 normal00 = normalize( texture(NormalTex, uv).rgb );
        vec3 position00 = normalize( texture(PositionTex, uv).rgb );

        vec3 X = normalize( xx - dot(normal00,xx) * zz / dot(normal00,zz) ) ;
        vec3 Y = normalize( yy - dot(normal00,yy) * zz / dot(normal00,zz) ) ;

        // check passed -> X.n=0 , Y.n=0
        //return vec3(dot(normal00,X));

        // step 2
        vec3 Sx = ( textureOffset(NormalTex, uv, ivec2(1,0)).rgb - normal00 );// * dot(X,xx) ;
        vec3 Sy = ( textureOffset(NormalTex, uv, ivec2(0,1)).rgb - normal00 );// * dot(Y,yy) ;

        // step 3
        vec3 B = cross(normal00, X) ;
        float norm = length(Y-dot(X,Y)*X) ;
        float l1 = dot(-X,Y) / norm ;
        float l2 = 1.0 / norm ;

        // step 4
        vec2 shape_operator_times_X = vec2( dot(X,Sx) , dot(B,Sx) ) ;
        vec2 shape_operator_times_Y = vec2( dot(X,Sy) , dot(B,Sy) ) ;

        // step 5
        vec2 shape_operator_column1 = shape_operator_times_X ;
        vec2 shape_operator_column2 = shape_operator_times_X * l1 + shape_operator_times_Y * l2 ;

///return abs(B);
///        float val = float(abs(shape_operator_column1.y - shape_operator_column2.x)<1e-6);
///return vec3(val);

    return vec3(shape_operator_column1.x, shape_operator_column2.y, shape_operator_column1.y);
}

// Covariance matrix calculations
//
// - storage
//		Cov. matrices are stored as (a,b,c), where the matrix actually is
//               [ a c ]
//               [ c b ]
//
// Compute the rotation of the covariance matrix stored in argument.
//
vec3 left_right_rotation(vec3 in_cov_matrix,float cos_theta,float sin_theta)
{
        float a = in_cov_matrix.x ;
        float b = in_cov_matrix.y ;
        float c = in_cov_matrix.z ;

        float ap = a*cos_theta*cos_theta + b*sin_theta*sin_theta + 2*c*cos_theta*sin_theta ;
        float bp = a*sin_theta*sin_theta + b*cos_theta*cos_theta - 2*c*cos_theta*sin_theta ;
        float cp = c*(cos_theta*cos_theta - sin_theta*sin_theta) + (b-a)*cos_theta*sin_theta ;

        return vec3(ap,bp,cp) ;
}

vec3 left_right_multiply(vec3 in_cov_matrix,vec3 in_factor)
{
        float a1 = in_cov_matrix.x ;
        float b1 = in_cov_matrix.y ;
        float c1 = in_cov_matrix.z ;

        float a2 = in_factor.x ;
        float b2 = in_factor.y ;
        float c2 = in_factor.z ;

        return vec3(
                a1*a2*a2 + 2*a2*c1*c2 + b1*c2*c2,
                a1*c2*c2 + 2*c1*c2*b2 + b1*b2*b2,
                a1*a2*c2 + c1*a2*b2 + c1*c2*c2 + b1*b2*c2
                ) ;
}

vec3 left_right_curvature_shear(vec3 in_cov_matrix,float c1,float c2)
{
        return left_right_multiply( left_right_multiply( in_cov_matrix, vec3(c1,1,0) ), vec3(1,c2,0) ) ;
}

// Computes the eigenvalues and first eigenvector of the given covariance matrix. The eigenvector
// is determines by its angle with respect to the first canonical vector.
// The out vector contains
//				lambda1
//				lambda2
//				cos_theta
//				sin_theta
//
vec4 compute_cov_eigen_decomposition(vec3 in_cov)
{
        float a = in_cov.x;
        float b = in_cov.y;
        float c = in_cov.z;

        if(c==0)
                return vec4(a,b,1.0,0.0) ;

        float sqrt_delta = sqrt( (a-b)*(a-b)+4*c*c+1e-12 );	// B11-043
        // adding an epsilon makes it run!

        float lambda1 = (a+b+sqrt_delta)*0.5 ;
        float lambda2 = (a+b-sqrt_delta)*0.5 ;

        // if c==0, then a==lambda1, so we end up with d==0. That's why the case is handled earlier.

        float d = sqrt( (a-lambda1)*(a-lambda1) + c*c ) ;
        float cos_angle,sin_angle ;

        if(d==0.0)
        {
                cos_angle = 1.0 ;
                sin_angle = 0.0 ;
        }
        else
        {
                cos_angle = c/d ;
                sin_angle = (a-lambda1)/d ;
        }

        return vec4(lambda1,lambda2,cos_angle,sin_angle) ;
}

// The decomposition over Gaussian mixtures for an elongated Gaussian is stored as:
//
//  [ l0, s0, x0, y0, l1, s1, x1, y1, l2, s2, x2, y2, .... ln, sn, xn, yn ]	  row for gaussian shape 1
//  [ l0, s0, x0, y0, l1, s1, x1, y1, l2, s2, x2, y2, .... ln, sn, xn, yn ]	  row for gaussian shape 2
//  [ l0, s0, x0, y0, l1, s1, x1, y1, l2, s2, x2, y2, .... ln, sn, xn, yn ]	  row for gaussian shape 3
//  [ l0, s0, x0, y0, l1, s1, x1, y1, l2, s2, x2, y2, .... ln, sn, xn, yn ]	  row for gaussian shape 4
//  ...
//
//    l  : lambda. Parameter to multiply the basis function to (float32)
//    s	: depth level of the basis function to use (float32)
//    xy	: point position for the function to use (float32 x 2)
//
//    Values are stored in the row by decreasing order of parameters, up to the resolution of the texture.
//
//  Shape parameters
//    Each line corresponds to a given value of the excentricity.
// 	We start at
//			line   i: e = (H-i-1)/H
//
//    With this, excentricity goes from 1 to 0 on a regular basis.
//
vec3 anisotropicAntialiasing(vec3 ReflectDir,int LMax)
{
  // compute input angular footprint of the pixel

  float distance_to_camera = length(v3PosWorld - WorldCameraPosition.xyz);

  // The shape operator should be computed in screen space in a separate pass.
  // It is stored as
  //							[ x z ]
  //							[ z y ]
  //
  vec3 ss_shape_operator = getShapeOperator() ; // Screen-space shape operator

  // Diagonalize the screen-space shape operator to find out the direction of anisotropy

  vec4 cov_eig = compute_cov_eigen_decomposition(ss_shape_operator) ;

  // The shape operator also gives us the anisotropy direction of the reflected ray, which is convenient
  // therefore we only need to take the vectors in the reflected direction, turned by the angle given
  // by the shape operator.

  float cos_theta = dot(v3NormalWorld,normalize(WorldCameraPosition.xyz - v3PosWorld)) ;

  float pixel_angular_footprint = HorizontalFieldOfView / float(ImageWidth) ;
  float angular_extent_1 = 2*pixel_angular_footprint * (1+2*cov_eig.x/cos_theta) ;
  float angular_extent_2 = 2*pixel_angular_footprint * (1+2*cov_eig.y) ;

  //return vec3(cos_theta,0.0,0.0) ;
  //return ss_shape_operator;
  //return v3NormalWorld;
  //return vec3(sqrt(cov_eig.x*cov_eig.x+cov_eig.y*cov_eig.y),0.0f,0.0f) ;
  //return vec3(angular_extent_1,angular_extent_2,0.0) ;
  //return vec3(excentricity,1.0/excentricity,0.0) ;

  // compute a suitable local coordinate system

  vec3 dir1,dir2 ;
  float angular_extent ;
  const int MAX_EXCENTRICITY = 15 ;
  const int MAX_SCALE        = 4 ;
  int scale_index ;

  // Compute a suitable local coordinate system, so that the max excentricity is always along dir1
  //
  if(angular_extent_1 < angular_extent_2)
  {
    angular_extent = angular_extent_2 ;

    float tmp = angular_extent_2 ;
    angular_extent_2 = angular_extent_1 ;
    angular_extent_1 = tmp ;

    dir2=normalize(cross(v3NormalWorld,ReflectDir)) ;
    dir1=cross(dir2,ReflectDir) ;
  }
  else
  {
    dir2=normalize(cross(v3NormalWorld,ReflectDir)) ;
    dir1=cross(dir2,ReflectDir) ;

    angular_extent = angular_extent_1 ;
  }
  scale_index = int(log(1.0 / angular_extent) / log(2.0)) ;

  float excentricity = angular_extent_1 / angular_extent_2 ;	// always > 1

  int excentricity_index = min(MAX_EXCENTRICITY,int(excentricity)) ;

//	return vec3(excentricity_index,scale_index,0) ;

  // now build the lookup directions and compute the actual shading.

  vec3 res = vec3(0,0,0) ;

  for(int l=0;l<=LMax;++l)
  {
    // Mipmap level is 0 for the original tex, 1 for level 1 blurred, etc.
    // We compute it as a function of the angular extent of the gaussian at level
    // Let n be the mipmap level, the angular extent that corresponds is
    //
    //      A = 2 PI / W * 2^n
    // but
    //		  A = PI / l
    //
    // So
    //			n = log_2 (W / (2l) )

    for(int m=-l;m<=l;++m)
    {
      // Gets the direction and the corresponding coefficient for the given scale and excentricity for
      // this particular (l,m) value.

      vec4 ani_coef = getAnisotropicGaussianCoef(scale_index,excentricity_index,l,m) ;

      // Compute the current lookup direction in the world coordinate system

      vec3 dir = dir1*ani_coef[0] + dir2*ani_coef[1] + ReflectDir*ani_coef[2] ;

      // normally we should use blm_params.y to find out the correct mipmap level in the envmap.

      res += ani_coef[3] * texture(CubeMapArrTex, vec4(dir,l)).rgb ;
    }
  }

  return res;
}

void main() {
    // This will call either pass1 or pass2
    //RenderPass();

    if(DrawSkyBoxMode > 0)
    {
        FragColor = texture(CubeMapTex, ReflectDir) ;
        // tone mapping
        FragColor.rgb = 1.0 - exp2( -Exposure * FragColor.rgb );
        FragColor.rgb = pow( FragColor.rgb, vec3(1.0/GammaInv) );

        return ;
    }

    if(passNum == 1)
    {
        // Store position, normal, and diffuse color in textures
        PositionData = v3PosWorld;
        NormalData = v3NormalWorld;
    }
    else if(passNum == 2)
    {
        // test
        {
///            vec2 uv = gl_FragCoord.xy / ScreenSize ;
///            vec3 pos = texture( PositionTex, uv ).rgb ;
///            vec3 norm = texture( NormalTex, uv ).rgb ;
///            FragColor.rgb = abs(getCurvatureXY()) ;
        }

        switch(AntialiasingMode)
        {
        case 0: FragColor.rgb = anisotropicAntialiasing(normalize(ReflectDir),LMax) ;
             break ;

        case 1: FragColor.rgb = texture(CubeMapTex, ReflectDir).rgb;
             break ;

        case 2: vec3 ss_shape_operator = getShapeOperator();
             vec4 cov_eig = compute_cov_eigen_decomposition(ss_shape_operator) ;

             FragColor.r = cov_eig.x*cov_eig.x + cov_eig.y*cov_eig.y ;	// Gaussian curvature
             FragColor.g = 0 ;
             FragColor.b = 0 ;
             break ;

        case 3: ss_shape_operator = getShapeOperator();
             cov_eig = compute_cov_eigen_decomposition(ss_shape_operator) ;

             FragColor.rgb = ss_shape_operator.xyz ;
             break ;

        case 4: FragColor.rgb = v3NormalWorld ;
             break ;

        case 5: FragColor.rgb = ReflectDir/ReflectDir.length() ;
             break ;
        };

    }

// 	if(AntialiasingMode > 0)
// 	{
// // tone-mapping
FragColor.rgb = 1.0 - exp2( -Exposure * FragColor.rgb );
FragColor.rgb = pow( FragColor.rgb, vec3(1.0/GammaInv) );
//	 }
//	 else
//	 FragColor.rgb /= Exposure ;
}
