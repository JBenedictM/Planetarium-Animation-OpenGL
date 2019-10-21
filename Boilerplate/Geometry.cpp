/*
 * Geometry.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: John Hall
 */

#include "Geometry.h"
#include "math.h"
#include "Parser.h"

const float PI = 3.14159265358979323846264f;

Geometry::Geometry() : vao(0), vertexBuffer(0), normalBuffer(0), uvBuffer(0), colorBuffer(0) {
	//vectors are initially empty
	//Pointers are initially null
	//Call RenderingEngine::assignBuffers and RenderingEngine::setBufferData to fully initialize the geometry
	//Overload the constructor for more functionality or create subclasses for specific objects
}

Parser Geometry::pr;

Geometry::~Geometry() {

}

float Geometry::degToRad(float deg) {
	return deg*PI/180.0f;
}


/*
 * SphericalCoordinates(Radius, Theta, Phi) = (x, y, z)
 * angles must be in degrees (easier that way)
 */
glm::vec3 Geometry::getSphereCoords(float r, float theta, float phi) {
	float thetaRad = degToRad(theta);
	float phiRad = degToRad(phi);
	float x = r * sin(phiRad) * sin(thetaRad);
	float y = r * cos(thetaRad);
	float z = r * cos(phiRad) * sin(thetaRad);

	return glm::vec3(x, y, z);
}
