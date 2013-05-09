//
//  main.cpp
//  Ders 6
//
//  Created by Gurel Erceis on 3/17/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//
// Thing to install and test before writing any code
// glm
// assimp (http://assimp.sourceforge.net/main_downloads.html)

#include <iostream>
#include <GL/glew.h>
#include "Scene.h"
#include <GLUT.h>
#include "FresnelShaderNode.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define WINDOW_TITLE_PREFIX "Ders 7"

void IdleFunction(void);
void ResizeFunction(int Width, int Height);
void setupScene();

unsigned FrameCount = 0;

int CurrentWidth = 1366,
CurrentHeight = 706,
WindowHandle = 0, mouseX = 0, mouseY = 0;

SceneNode* pad1;

Camera *camera;

Scene* scene;

float directionX = 1;
float directionY = 0.5;
float speed = 0.4;

static void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    scene->draw();
    
    glutSwapBuffers();
    FrameCount++;
}


void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

static void Mouse(int x, int y)
{
    GLfloat deltaX = (mouseX - x)/10;
    GLfloat deltaY = (mouseY - y)/10;
    camera->rotate(deltaX, 0, 1, 0);
    camera->rotate(deltaY, 1, 0, 0);
    mouseX = x;
    mouseY = y;
    glutPostRedisplay();
}

static void timerCallback (int value)
{
    if (0 != value) {
		char* TempString = (char*)
        malloc(512 + strlen(WINDOW_TITLE_PREFIX));
        
		sprintf(
                TempString,
                "%s: %d Frames Per Second @ %d x %d",
                WINDOW_TITLE_PREFIX,
                FrameCount * 4,
                CurrentWidth,
                CurrentHeight
                );
        
		glutSetWindowTitle(TempString);
		free(TempString);
	}
	FrameCount = 0;
	glutTimerFunc(250, timerCallback, 1);
}


void setupScene(){
    scene = new Scene();
    
    pad1 = new FresnelShaderNode("C:/Users/user/Desktop/Proje2_3.Homework/Ders7/Ders7/bunny.obj");
	//pad2 = new ScreenSpaceShaderNode("C:/Users/user/Desktop/Bilgisayar Proje 2/ders7solution/Ders7/Ders7/paddle.obj");
    
	//ball = new ScreenSpaceShaderNode("C:/Users/user/Desktop/Bilgisayar Proje 2/ders7solution/Ders7/Ders7/ball.obj");

    //pad1->scale(0.9,0.9,0.9);
    //pad2->scale(0.03,0.1,0.01);
	//ball->scale(0.03,0.03,0.01);

	//pad3->scale(0.03,0.1,0.01);
	//pad4->scale(0.03,0.1,0.01);
 
    scene->addNode(pad1);
    //scene->addNode(pad2);
    //scene->addNode(ball);

    camera = new Camera();
    
    camera->translate(0.f, 0.f, 1.f);
    
    pad1->translate(0.f, 0.f, 0.f);
    
    //pad2->translate( 30.f, 0.f, 0.f);
    
    scene->setCamera(camera);
}

int main (int argc, char ** argv)
{
    
    GLenum type;
    
	glutInit(&argc, argv);
	glutInitWindowSize(CurrentWidth,CurrentHeight);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
    type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	glutCreateWindow("");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
	  /* Problem: glewInit failed, something is seriously wrong. */
	  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
    glClearColor(0.0, 1.0, 0.0, 1.0);
    // Z-Buffer i aciyoruz
    glEnable(GL_DEPTH_TEST);
    
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE); 
    
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    
    printf("GLSL Version: %s\n",glslVersion);
    
    const GLubyte* glVersion = glGetString(GL_VERSION);
    
    printf("GL Version: %s\n",glVersion);
       
    setupScene();
    
    timerCallback(0);
    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(Draw);
	glutMotionFunc(Mouse);
    glutMainLoop();

    
    return 0;
}


