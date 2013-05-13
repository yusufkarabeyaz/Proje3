
#version 120

// sabit degiskenler
uniform mat4 MVP,ModelView;


// diziden alinacak degiskenler
attribute vec4 Position;
attribute vec3 Normal;

// fragment shader'a aktarilacak veriler
varying vec3 normal;

// vertex shader main metodu
void main()
{	
	gl_Position = MVP * Position;
    normal = mat3(ModelView)*Normal;

}


