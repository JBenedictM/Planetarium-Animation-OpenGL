/*
 * SceneNode.cpp
 *
 *  Created on: Dec. 5, 2018
 *      Author: bille
 */

#include "SceneNode.h"
#include <string>
SceneNode::SceneNode(enum SceneObject so, SceneNode* pr) {
	this->parent = pr;
	this->nodeObject = so;

	if (nodeObject == SceneNode::SceneObject::Earth) {
		mySphere = new Sphere("earthSphere.obj", "earthTexture.jpg", true);
	} else if (nodeObject == SceneNode::SceneObject::Sun) {
		mySphere = new Sphere("sunSphere.obj", "sunTexture.jpg", false);

	} else if (nodeObject == SceneNode::SceneObject::Moon) {
		mySphere = new Sphere("moonSphere.obj", "moonTexture.jpg", true);

	} else if (nodeObject == SceneNode::SceneObject::Mars) {
		mySphere = new Sphere("marsSphere.obj", "marsTexture.jpg", true);

	} else if (nodeObject == SceneNode::SceneObject::Stars) {
		mySphere = new Sphere("starsSphere2.obj", "starsTexture.jpg", false);

	} else if (nodeObject == SceneNode::SceneObject::Jupiter) {
		mySphere = new Sphere("jupiter.obj", "jupiter.jpg", true);

	} else if (nodeObject == SceneNode::SceneObject::Venus) {
		mySphere = new Sphere("venusObj.obj", "venusTexture.jpg", true);

	} else if (nodeObject == SceneNode::SceneObject::Neptune) {
		mySphere = new Sphere("neptuneObj.obj", "2k_neptune.jpg", true);

	}

	else {
		std::cout << "Scene object unknown\n ";
		std::cout << "Terminating program.\n";
		exit(-1);
	}


	// initialize matrices and vectors to their identity
	setSize(1.0f);
	setRotation(0.0f);
	setTranslation(glm::mat4(1.0f));
	setOrientation(glm::mat4(1.0f));


}

SceneNode::~SceneNode() {
	// TODO Auto-generated destructor stub
}

void SceneNode::setSize(float s) {
	this->sizeMod = s;
}

void SceneNode::setRotation(float deg) {
	this->rotationDeg = deg;
	updateCoordinates();
}

void SceneNode::setTranslation(glm::mat4 trans) {
	this->translation = trans;
	updateCoordinates();
}

glm::mat4 SceneNode::getLocalTransformation() {
	return this->localTransformation;
}

void SceneNode::setOrientation(glm::mat4 orient) {
	this->orientation = orient;
	updateCoordinates();
}

void SceneNode::updateCoordinates() {
	// transformation with respect to global coordinates
	// (world) M (SceneObject)
	this->localTransformation = this->translation * glm::rotate(this->orientation, glm::radians(rotationDeg), glm::vec3(0.0f, 1.0f, 0.0f));
	this->localTransformation = glm::scale(this->localTransformation, glm::vec3(sizeMod));

	// set reference frame as the displacement
	this->referenceFrame = this->translation;

}

glm::mat4 SceneNode::getOrientation() {
	return this->orientation;
}

glm::mat4 SceneNode::getReferenceFrame() {
	return this->referenceFrame;
}

// return the transformation matrix of specified node
glm::mat4 SceneNode::traverseGraph(SceneNode* node) {
	// root
	if (node->parent == NULL) {
		return node->getReferenceFrame();
	} else {
		return traverseGraph(node->parent) * node->parent->getReferenceFrame();
	}

}










