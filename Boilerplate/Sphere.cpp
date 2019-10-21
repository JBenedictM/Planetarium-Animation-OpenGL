/*
 * Sphere.cpp
 *
 *  Created on: Dec. 5, 2018
 *      Author: bille
 */

#include "Sphere.h"
#include "Parser.h"
#include <string>

Sphere::Sphere(std::string objPath, std::string imagePath, bool diffuse) {
	// initialize object file
	Geometry::pr.parseObjFile(objPath);

	// initialize texture associated with texture file
	InitializeTexture(&this->my_texture, imagePath.c_str(), GL_TEXTURE_2D);

	// store all data into objects vectors
	std::vector<glm::vec3> parsedVerts = Geometry::pr.vertices;
	std::vector<glm::vec3> parsedNormals = Geometry::pr.normals;
	std::vector<glm::vec2> parsedTextureUV = Geometry::pr.textureUV;
	std::vector<std::vector<glm::vec3>> parsedFaces = Geometry::pr.faces;

	// takes vertex index from faces to create triangles with corresponding normals and texture UV
	for (std::vector<glm::vec3> aFace : parsedFaces) {
		for (glm::vec3 aVec : aFace) {
			// first index corresponds to a vertex index
			this->verts.push_back(parsedVerts[aVec[0]-1]);		// -1 since .obj files start indexing at 1
			// second index corresponds to texture index
			this->uvs.push_back(parsedTextureUV[aVec[1]-1]);
			// this index corresponds to normal index
			this->normals.push_back(parsedNormals[aVec[2]-1]);

			// color place holder in place of textures
			this->colors.push_back(glm::vec3(0.0f));
		}
	}

	this->drawMode = GL_TRIANGLES;
	this->diffuse = diffuse;

}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}


