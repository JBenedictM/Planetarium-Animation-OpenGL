/*
* Scene.cpp
*
*  Created on: Sep 10, 2018
*  Author: John Hall
*/

#include "Scene.h"

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SceneNode.h"

#include <string>

Scene::Scene(RenderingEngine* renderer, GLFWwindow* window) : renderer(renderer), window(window) {
	theta = 50.0f;
	phi = 0.0f;
	radius = 38.0f;

	// initialize projection and view matrix
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 15.0f, 400.0f);

	// enable to draw wireframe objects
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glEnable(GL_DEPTH_TEST);
	// Enable depth test

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// center of universe = stars = at the origin (0, 0, 0)
	stars = new SceneNode(SceneNode::SceneObject::Stars, NULL);
	stars->setSize(3.0f);
	// no tilt
	stars->setOrientation(glm::mat4(1.0f));

	//construct buffer data for each planet
	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(*stars->mySphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(*stars->mySphere);


	// sun configurations
	// child of the stars
	sun = new SceneNode(SceneNode::SceneObject::Sun, stars);
	stars->children.push_back(sun);
	// no tilt
	sun->setOrientation(glm::mat4(1.0f));

	//construct buffer data for each planet
	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(*sun->mySphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(*sun->mySphere);

	// jupiter configurations
	// child of the sun
	jupiter = new SceneNode(SceneNode::SceneObject::Jupiter, sun);
	jupiter->setSize(10.0f);
	sun->children.push_back(jupiter);
	// tilted 4 deg from the vertical
	glm::mat4 jupiterTilt = glm::rotate(glm::mat4(1.0f), glm::radians(-4.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	jupiter->setOrientation(jupiterTilt);

	//construct buffer data for each planet
	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(*jupiter->mySphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(*jupiter->mySphere);

	// neptune configurations
	// child of the sun
	neptune = new SceneNode(SceneNode::SceneObject::Neptune, sun);
	neptune->setSize(5.0f);
	sun->children.push_back(neptune);
	// tilted 4 deg from the vertical
	glm::mat4 neptuneTilt = glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	neptune->setOrientation(neptuneTilt);

	//construct buffer data for each planet
	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(*neptune->mySphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(*neptune->mySphere);

	// venus configurations
	// child of the sun
	venus = new SceneNode(SceneNode::SceneObject::Venus, sun);
	venus->setSize(2.0f);
	sun->children.push_back(venus);
	// tilted 4 deg from the vertical
	glm::mat4 venusTilt = glm::rotate(glm::mat4(1.0f), glm::radians(-177.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	venus->setOrientation(venusTilt);

	//construct buffer data for each planet
	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(*venus->mySphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(*venus->mySphere);

	// earth configurations
	// child of the sun
	earth = new SceneNode(SceneNode::SceneObject::Earth, sun);
	sun->children.push_back(earth);
	// tilted 23.4 deg from the vertical
	glm::mat4 earthTilt = glm::rotate(glm::mat4(1.0f), glm::radians(-23.4f), glm::vec3(0.0f, 0.0f, 1.0f));
	earth->setOrientation(earthTilt);


	//construct buffer data for each planet
	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(*earth->mySphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(*earth->mySphere);

	// child of the earth
	moon = new SceneNode(SceneNode::SceneObject::Moon, earth);
	earth->children.push_back(moon);
	glm::mat4 moonTrans = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.0f, 0.0f));
	moon->setTranslation(moonTrans);
	// tilted 1.54* from the vertical
	glm::mat4 moonTilt = glm::rotate(glm::mat4(1.0f), glm::radians(1.54f), glm::vec3(0.0, 0.0f, 1.0f));
	moon->setOrientation(moonTilt);
	//construct buffer data for each planet
	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(*moon->mySphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(*moon->mySphere);

	// mars configurations
	// child of the sun
	mars = new SceneNode(SceneNode::SceneObject::Mars, sun);
	mars->setSize(1.5f);
	sun->children.push_back(mars);
	// no tilt
	mars->setRotation(0.0f);
	// 30 on the x axis away from sun
	glm::mat4 marsTrans = glm::translate(glm::mat4(1.0f), glm::vec3(30.0f, 0.0f, 0.0f));
	mars->setTranslation(marsTrans);
	// orientation
	// tilted 25.0 deg from the vertical
	glm::mat4 marsTilt = glm::rotate(glm::mat4(1.0f), glm::radians(-25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	mars->setOrientation(marsTilt);


	//construct buffer data for each planet
	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(*mars->mySphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(*mars->mySphere);



}

Scene::~Scene() {

}

void Scene::displaySphere() {
	Geometry sphere;

	std::vector<glm::vec3> sphereVerts = parseData.vertices;
	std::vector<std::vector<glm::vec3>> allFaces = parseData.faces;
	std::vector<glm::vec2> sphereUV = parseData.textureUV;
	glm::vec3 colorBlack = glm::vec3(1.0f, 1.0f, 1.0f);


	// takes vertex index from faces to create triangles
	for (std::vector<glm::vec3> aFace : allFaces) {
		for (int i = 0; i < 3; i++) {
			sphere.verts.push_back(sphereVerts[ aFace[i][0] - 1 ]);
			sphere.colors.push_back(colorBlack);

		}
	}

	//sphere.drawMode = GL_TRIANGLES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(sphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(sphere);

	//Add the triangle to the scene objects
	objects.push_back(sphere);
}

void Scene::displayScene() {
	glm::vec3 cameraOrigin;
	glm::vec3 lookDirection;
	if (mode == 0) {
		cameraOrigin = glm::vec3((SceneNode::traverseGraph(sun) * sun->getReferenceFrame()) * glm::vec4( Geometry::getSphereCoords(radius, theta, phi), 1.0f));
		lookDirection = glm::vec3(SceneNode::traverseGraph(sun) * sun->getReferenceFrame() * glm::vec4(1.0f));
	} else if (mode == 2) {
		cameraOrigin = glm::vec3((SceneNode::traverseGraph(earth) * earth->getReferenceFrame()) * glm::vec4( Geometry::getSphereCoords(radius, theta, phi), 1.0f));
		 lookDirection = glm::vec3(SceneNode::traverseGraph(earth) * earth->getReferenceFrame() * glm::vec4(1.0f));
	} else if (mode == 3) {
		 cameraOrigin = glm::vec3((SceneNode::traverseGraph(mars) * mars->getReferenceFrame()) * glm::vec4( Geometry::getSphereCoords(radius, theta, phi), 1.0f));
		lookDirection = glm::vec3(SceneNode::traverseGraph(mars) * mars->getReferenceFrame() * glm::vec4(1.0f));
	} else if (mode == 4) {
		 cameraOrigin = glm::vec3((SceneNode::traverseGraph(jupiter) * jupiter->getReferenceFrame()) * glm::vec4( Geometry::getSphereCoords(radius, theta, phi), 1.0f));
		lookDirection = glm::vec3(SceneNode::traverseGraph(jupiter) * jupiter->getReferenceFrame() * glm::vec4(1.0f));
	} else if (mode == 1) {
		cameraOrigin = glm::vec3((SceneNode::traverseGraph(venus) * venus->getReferenceFrame()) * glm::vec4( Geometry::getSphereCoords(radius, theta, phi), 1.0f));
		lookDirection = glm::vec3(SceneNode::traverseGraph(venus) * venus->getReferenceFrame() * glm::vec4(1.0f));
	} else if (mode == 5) {
		cameraOrigin = glm::vec3((SceneNode::traverseGraph(neptune) * neptune->getReferenceFrame()) * glm::vec4( Geometry::getSphereCoords(radius, theta, phi), 1.0f));
		lookDirection = glm::vec3(SceneNode::traverseGraph(neptune) * neptune->getReferenceFrame() * glm::vec4(1.0f));
	}

	// construct view and projection matrix
	glm::mat4 View = glm::lookAt(
				cameraOrigin, // Camera is at (4,3,3), in World Space
				lookDirection, // and looks at the origin
				glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	p_v = projection * View;

	// animate the scene
	double currentTime = glfwGetTime();

	if (previousTime != 0.0f) {
		timeDif += animateSpeed*(currentTime - previousTime);
		// ensures time dif doesnt exceed 360
	}

	previousTime = currentTime;

	// sun's rotation
	// sun rotates at 14.17 deg/sec
	// no orbit
	sun->setRotation(fmod(14.17f * timeDif, 360.0f));

	// earth's orbit and rotation
	glm::mat4 earthTrans = glm::rotate(glm::mat4(1.0f), glm::radians(7.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// earth orbits at 0.99 deg/sec
	earthTrans = glm::translate(earthTrans, Geometry::getSphereCoords(30.0f, 90.0f, fmod(0.99f * timeDif, 360.0f)));
	earthTrans = glm::rotate(earthTrans, glm::radians(-7.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//earth->setTranslation(earthTrans);
	earth->setTranslation(earthTrans);
	// earth rotates at 360 deg/sec
	earth->setRotation(fmod(360.0f * timeDif, 360.0f));

	// moon's orbit and rotation
	glm::mat4 moonTrans = glm::rotate(glm::mat4(1.0f), glm::radians(6.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// moon orbits at 13.19 deg/sec
	moonTrans = glm::translate(moonTrans, Geometry::getSphereCoords(6.0f, 90.0f, fmod(13.19f * timeDif, 360.0f)));
	moonTrans = glm::rotate(moonTrans, glm::radians(-6.0f), glm::vec3(0.0, 0.0f, 1.0f));
	moon->setTranslation(moonTrans);
	// moon rotates at 13.34 deg/sec
	moon->setRotation(fmod(13.34f * timeDif, 360.0f));

	// mars' orbit and rotation
	glm::mat4 marsTrans = glm::rotate(glm::mat4(1.0f), glm::radians(6.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// mars orbits at 0.52 deg/sec
	marsTrans = glm::translate(marsTrans, Geometry::getSphereCoords(43.0f, 90.0f, fmod(0.52f * timeDif, 360.0f)));
	marsTrans = glm::rotate(marsTrans, glm::radians(-6.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	mars->setTranslation(marsTrans);
	// mars rotates at 338 deg/sec
	mars->setRotation(fmod(338.0f * timeDif, 360.0f));

	// jupiter' orbit and rotation
	glm::mat4 jupiterTrans = glm::rotate(glm::mat4(1.0f), glm::radians(3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// mars orbits at 0.52 deg/sec
	jupiterTrans = glm::translate(jupiterTrans, Geometry::getSphereCoords(64.0f, 90.0f, fmod(0.08f * timeDif, 360.0f)));
	jupiterTrans = glm::rotate(jupiterTrans, glm::radians(-3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	jupiter->setTranslation(jupiterTrans);
	// mars rotates at 338 deg/sec
	jupiter->setRotation(fmod(857.0f * timeDif, 360.0f));


	// neptune' orbit and rotation
	glm::mat4 neptuneTrans = glm::rotate(glm::mat4(1.0f), glm::radians(7.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// neptune orbits at 0.52 deg/sec
	neptuneTrans = glm::translate(neptuneTrans, Geometry::getSphereCoords(83.0f, 90.0f, fmod(0.006f * timeDif, 360.0f)));
	neptuneTrans = glm::rotate(neptuneTrans, glm::radians(-7.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	neptune->setTranslation(neptuneTrans);
	// mars rotates at 338 deg/sec
	neptune->setRotation(fmod(537.0f * timeDif, 360.0f));

	// venus' orbit and rotation
	glm::mat4 venusTrans = glm::rotate(glm::mat4(1.0f), glm::radians(4.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// venus orbits at 0.52 deg/sec
	venusTrans = glm::translate(venusTrans, Geometry::getSphereCoords(18.0f, 90.0f, fmod(1.6f * timeDif, 360.0f)));
	venusTrans = glm::rotate(venusTrans, glm::radians(-4.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	venus->setTranslation(venusTrans);
	// mars rotates at 338 deg/sec
	venus->setRotation(fmod(3.07f * timeDif, 360.0f));

	// ignore error
	renderer->RenderScene(objects, window, p_v, this->stars);
}
