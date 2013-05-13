#version 120

uniform mat4 MV;

// vertex shaderindan gelen veriler
varying vec3 normal;
varying vec4 pos;


// Fresnel example fragment shader

// Iþýk parametreleri
vec4 V = pos;			// vertex position
vec4 E = -pos;			// eye position
vec3 N = normalize(normal);			// surface normal

// direction of brightest point in environment map
const vec3 Ln = vec3(-.913, 0.365, 0.183);
const vec4 env = vec4(.1,.2,.3,1);

// lighting parameters -- could pass in as uniform
const float r0 = .1;		// Fresnel reflectance at zero angle
const vec4 ka = vec4(.1,.2,.3,1);
const vec4 kd = vec4(.5,.7,.9,0);
const vec4 ks = vec4(.4,.4,.4,0);
const float es = 16.;

void main()
{
    // lighting vectors
    vec3 Nn = normalize(normal);	// normal
    vec3 In = normalize(V.xyz*E.w - E.xyz*V.w); // -view
    vec3 Hn = normalize(Ln-In);	// half way between view & light

    // color
    float diff = max(0.,dot(Nn,Ln));
    float spec = pow(max(0.,dot(Nn,Hn)),es);
    vec4 col = ka + kd*diff + ks*spec;

    vec3 R = reflect(In,Nn);
    vec3 RH = normalize(R-In);
    float fresnel = r0 + (1.0-r0)*pow(1.0+dot(In,RH),5.0);
    gl_FragColor = mix(col,env,dot(fresnel,0));
}
