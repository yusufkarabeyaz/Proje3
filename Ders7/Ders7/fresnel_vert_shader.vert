
#version 120

// sabit degiskenler
uniform mat4 MVP,ModelView;


// diziden alinacak degiskenler
attribute vec4 Position;
attribute vec3 Normal;

// fragment shader'a aktarilacak veriler
varying vec3 normal;
varying vec4 pos;

// vertex shader main metodu
void main()
{	
    vec4 vVertex = vec4(ModelView * Position);
    // gl_Position ekranda noktanin nerede olacagini belirtir.
    gl_Position = MVP * Position;
    normal = mat3(MVP)*Normal;
    pos = vVertex;
}


