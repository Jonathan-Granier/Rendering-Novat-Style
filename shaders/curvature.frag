#version 330 core

layout(location = 0) out vec4 outBuffer;

in vec2 texcoord;

uniform sampler2D normalMap;

uniform float sigma;

#define F 3.0 // used to define the window size (sigma*F)
#define RESOL 2.0 // multisampling (increase resolution)
#define PI 3.14159265359
#define PI2 6.28318531


#define F 3.0 // used to define the window size (sigma*F)
#define RESOL 2.0 // multisampling (increase resolution)
#define PI 3.14159265359
#define PI2 6.28318531

#define F 3.0 // used to define the window size (sigma*F)
#define RESOL 2.0 // multisampling (increase resolution)
#define PI 3.14159265359
#define PI2 6.28318531

float halfsize = ceil(F*sigma); // kernel halfsize
const float iresol = 1.0/RESOL; // step for sampling
const float eps = 1e-15;

vec2 ps = 1./vec2(textureSize(normalMap,0)); // pixel size

vec2 grad(in vec4 n) {
  const float f = 1; // forshortening in [0,1]. 1=a lot (true gradient), 0 = no forshortening.
  float d = -1./mix(1.,max(n.z,eps),f);
  return  vec2(n.x,n.y)*d;
}

float weight(in vec4 cn,in vec4 on) {
  // the alpha value
  const float sd = 0.1; // sigma for checking differences in depth
  float d = on.w-cn.w;
  return min(length(cn.xyz),exp(-(d*d)/(2.*sd*sd)));
}

vec2 mixedGrad(in vec2 gCenter,in vec2 gCurrent,in float w) {
  // takes weight into account to compute current value
  return mix(gCenter,gCurrent,w);
}

vec3 hessianMatrix(in vec4 pixel) {
  // precompute gaussian data (factor/denom)
  float sigma2 = sigma*sigma;
  float sigma4 = sigma2*sigma2;
  float f = -1./(PI2*sigma4);
  float d = 2.0*sigma2;

  vec3 H = vec3(0.);
  vec2 pg = grad(pixel); // gradient of the current pixel
  float pw = weight(pixel,pixel); // weight of the current pixel

  for(float i=-halfsize;i<=halfsize;i+=iresol) {
    for(float j=-halfsize;j<=halfsize;j+=iresol) {
      vec2 pos = vec2(i,j);
      vec4 n = texture(normalMap,texcoord+pos*ps);

      // current value (possibly mixed with the pixel)
      vec2 v = mixedGrad(pg,grad(n),weight(n,pixel));
      vec2 e = v*exp(-(pos.x*pos.x+pos.y*pos.y)/d);

      // update Hessian
      H.x = H.x + pos.x*f*e.x; // gxx
      H.y = H.y + pos.y*f*e.y; // gyy
      H.z = H.z + .5*(pos.x*f*e.y + pos.y*f*e.x); // gxy (=gyx)
    }
  }

  return H*pw;
}

vec4 eigenValues(in vec3 m) {
  float tmp = max(sqrt(m.x*m.x+4.0*m.z*m.z-2.0*m.x*m.y+m.y*m.y),0.);
  float k1  = 0.5*(m.x+m.y+tmp);
  float k2  = 0.5*(m.x+m.y-tmp);
  vec2  d1  = vec2(m.z,k1-m.x);
    vec2  d2  = vec2(k1-m.x,-m.z);

  d1 = length(d1)<eps ? vec2(0.) : normalize(d1);
  d2 = length(d2)<eps ? vec2(0.) : normalize(d2);

  // return max dir, max eigen-val, min eigen-val
  return abs(k1)>abs(k2) ? vec4(d1.x,d1.y,k1,k2) : vec4(d2.x,d2.y,k2,k1);
}


vec4 eigenValuesCyril(vec3 in_cov)
{
        float a = in_cov.x;
        float b = in_cov.y;
        float c = in_cov.z;

        if(c==0)
                return vec4(1.0,0.0,a,b) ;

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

        return vec4(cos_angle,sin_angle,lambda1,lambda2) ;
}



void main() {
  vec4 pix = texture(normalMap,texcoord);
  pix = normalize(pix);
  vec3 H = hessianMatrix(pix);
  vec4 ee = eigenValues(H);
  float mc = .5*(ee.z+ee.w);
  vec4 firstGaussianDeriv = vec4(ee);

  //outBuffer = firstGaussianDeriv;
  //outBuffer = vec4(ee.xy,0,0);


  if(gl_FragCoord.x <= 10 && gl_FragCoord.y <= 10){
    outBuffer = vec4(-1,1,1,0);
  }
  else if(texcoord.x < 0.5 && texcoord.y < 0.5){
    outBuffer = vec4(-1,0,0,0);
  }
  else if(texcoord.x < 0.5){
    outBuffer = vec4(1,-1,0,0);
  }
  else if(texcoord.y < 0.5){
    outBuffer = vec4(-1,1,0,0);
  }
  else
    outBuffer = vec4(0,-1,1,0);

}

