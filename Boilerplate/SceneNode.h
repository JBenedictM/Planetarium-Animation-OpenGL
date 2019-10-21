/*
 * SceneNode.h
 *
 *  Created on: Dec. 5, 2018
 *      Author: bille
 */

#ifndef SCENENODE_H_
#define SCENENODE_H_

#include <vector>
#include "Sphere.h"
#include "Geometry.h"
#include "Sphere.h"

class SceneNode {
public:
	enum SceneObject { Earth, Moon, Sun, Mars, Stars, Jupiter, Venus, Neptune};

	SceneNode(enum SceneObject so, SceneNode* pr);
	virtual ~SceneNode();

	enum SceneObject nodeObject;

	// pointer to parent
	SceneNode* parent;
	// pointer to children
	std::vector<SceneNode*> children;

	Sphere* mySphere = NULL;

	glm::mat4 getLocalTransformation();
	void setRotation(float deg);
	void setTranslation(glm::mat4 trans);
	void setOrientation(glm::mat4 orient);
	glm::mat4 getOrientation();

	void setSize(float s);

	glm::mat4 getReferenceFrame();

	// traverses the scene graph and outputs the appropriate transformation matrix
	static glm::mat4 traverseGraph(SceneNode* so);

private:
	void updateCoordinates();
	float sizeMod = 1.0f;
	glm::mat4 localTransformation;
	float rotationDeg;
	glm::mat4 translation;
	glm::mat4 orientation;
	glm::mat4 referenceFrame;

};

#endif /* SCENENODE_H_ */
