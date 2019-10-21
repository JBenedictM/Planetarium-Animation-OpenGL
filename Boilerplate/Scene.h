/*
* Scene.h
*	Class for storing objects in a scene
*  Created on: Sep 10, 2018
*      Author: cb-ha
*/

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "Geometry.h"
#include "Parser.h"

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "SceneNode.h"


//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {
public:
	Scene(RenderingEngine* renderer, GLFWwindow* window);
	virtual ~Scene();


	//Send geometry to the renderer
	void displayScene();
	float planetPhi = 0.0f;

	float theta;
	float phi;
	float radius;

	void displaySphere();

	SceneNode* stars;
	SceneNode* sun;
	SceneNode* earth;
	SceneNode* moon;
	SceneNode* mars;
	SceneNode* jupiter;
	SceneNode* venus;
	SceneNode* neptune;

	int mode = 0;

	// projection and view matrix
	glm::mat4 p_v;

	float phiAnimate = 0.0f;
	float animateSpeed = 1.0f;

	glm::mat4 projection;

private:
	double previousTime = 0.0f;
	double timeDif = 0.0f;
	RenderingEngine * renderer;
	GLFWwindow* window;
	Parser parseData;

	//list of objects in the scene
	std::vector<Geometry> objects;
};

#endif /* SCENE_H_ */
