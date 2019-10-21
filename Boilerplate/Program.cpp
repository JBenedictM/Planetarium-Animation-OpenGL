/*
* Program.cpp
*
*  Created on: Sep 10, 2018
*      Author: John Hall
*/

#include "Program.h"

#include <iostream>
#include <string>

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "RenderingEngine.h"
#include "Scene.h"

int state;

Program::Program() {
	setupWindow();
}

Program::~Program() {
	//Must be cleaned up in the destructor because these are allocated to the heap
	delete renderingEngine;
	delete scene;
}

void Program::start() {
	renderingEngine = new RenderingEngine();
	scene = new Scene(renderingEngine, window);

	//Main render loop
	while (!glfwWindowShouldClose(window)) {
		scene->displayScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
//		glfwWaitEventsTimeout(0.5);
	}

}

void Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function
	//Errors will be printed to the console
	glfwSetErrorCallback(ErrorCallback);

	//Attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 512;
	int height = 512;
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}
	glfwSetWindowUserPointer(window, this);

	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);
	
	//Set the custom function that tracks mouse scroll
	glfwSetScrollCallback(window, scroll_callback);

	//Set the custom function that tracks mouse position
	glfwSetCursorPosCallback(window, cursor_position_callback);

	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);

	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL()) {
		std::cout << "GLAD init failed" << std::endl;
		return;
	}

	//Query and print out information about our OpenGL environment
	QueryGLVersion();
}



void Program::QueryGLVersion() {
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}

void ErrorCallback(int error, const char* description) {
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	Program* p = (Program*)glfwGetWindowUserPointer(window);
	Scene* s = p->getScene();
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		s->phi += 5.0f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		s->phi -= 5.0f;
	}
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
			s->animateSpeed += 0.2f;
	}
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (s->animateSpeed > 0.2f) {
			s->animateSpeed -= 0.2f;

		}
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS ) {
			s->mode = 0;
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS ) {
		s->mode = 1;
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS ) {
		s->mode = 2;
	}

	if (key == GLFW_KEY_4 && action == GLFW_PRESS ) {
		s->mode = 3;
	}

	if (key == GLFW_KEY_5 && action == GLFW_PRESS ) {
		s->mode = 4;
	}
	if (key == GLFW_KEY_6 && action == GLFW_PRESS ) {
		s->mode = 5;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
	if((s->theta < 175) && (s->theta > 5))
		{
			s-> theta += 5.0f;
		}
		else if(s->theta >= 175)
			{
				s->theta = 174;
			}
		else if(s->theta <= 5)
			{
				s->theta = 6;
			}
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		if((s->theta < 175) && (s->theta > 5))
		{
			s-> theta -= 5.0f;
		}
		else if(s->theta >= 175)
			{
				s->theta = 174;
			}
		else if(s->theta <= 5)
			{
				s->theta = 6;
			}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Program* p = (Program*)glfwGetWindowUserPointer(window);
	Scene* s = p->getScene();
	if((s->radius <= 80) && (s->radius >= 30))
	{
		s->radius += yoffset;
	}
	else if(s->radius >= 80)
	{
		s->radius = 80;
	}
	else if(s->radius <= 30)
	{
		s->radius = 30;
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{	
	GLboolean leftButtonPressed;
	Program* p = (Program*)glfwGetWindowUserPointer(window);
	Scene* s = p->getScene();

	state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	if(state == GLFW_PRESS)
	{
		leftButtonPressed = true;
	}

	else if(state == GLFW_RELEASE)
	{
		leftButtonPressed = false;
	}

	if(leftButtonPressed)
		{
			if((s->theta < 178) && (s->theta > 2))
			{
				s->theta += (ypos-256)/256;
				s->phi += (xpos-256)/256;
			}
			else if(s->theta >= 178)
			{
				s->theta = 177;
				s->phi+=(xpos-256)/256;
			}
			else if(s->theta <= 2)
			{
				s->theta = 3;
				s->phi+=(xpos-256)/256;
			}

		}

}
