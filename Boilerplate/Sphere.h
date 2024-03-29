/*
 * Sphere.h
 *
 *  Created on: Dec. 5, 2018
 *      Author: bille
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Geometry.h"
#include <string>

class Sphere: public Geometry {

public:
	Sphere(std::string sourcePath, std::string imagePath, bool diffuse);

	virtual ~Sphere();

	void setOrientation(glm::mat4 orient);
	bool diffuse;

private:
	glm::mat4 orientation;
};

#endif /* SPHERE_H_ */
