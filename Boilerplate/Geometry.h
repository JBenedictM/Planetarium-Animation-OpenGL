/*
 * Geometry.h
 *	Class for storing geometry
 *  Created on: Sep 10, 2018
 *      Author: John Hall
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <vector>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Parser.h"
#include "texture.h"

class Geometry {
public:
	Geometry();
	virtual ~Geometry();

	//Data structures for storing vertices, normals colors and uvs
	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec2> uvs;

	//Pointers to the vao and vbos associated with the geometry
	GLuint vao;
	GLuint vertexBuffer;
	GLuint normalBuffer;
	GLuint uvBuffer;
	GLuint colorBuffer;

	//Draw mode for how OpenGL interprets primitives
	GLuint drawMode;

	// texture
	MyTexture my_texture;

	// helper functions for calculating sphere coordinates
	static glm::vec3 getSphereCoords(float r, float theta, float phi);
	static float degToRad(float deg);
	static Parser pr;

};


#endif /* GEOMETRY_H_ */
