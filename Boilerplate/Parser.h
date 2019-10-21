/*
 * Parser.h
 *
 *  Created on: Nov. 18, 2018
 *      Author: bille
 */

#ifndef PARSER_H_
#define PARSER_H_


#include <vector>
#include <string>

#include <iostream>
#include <fstream>
#include <vector>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>


using namespace std;


class Parser {
public:
	Parser();
	virtual ~Parser();

	//void parseScene(std::string source, std::vector<Geometry*>* spaceItems, std::vector<Light>* lights);

	void removeWhiteSpaces(std::string* str);
	float toFloat(std::string str);
	glm::vec3 parseVec(std::string str);
	void getNextLine(std::ifstream* myfile, std::string line);
	//void parseAnObj(std::string source, std::vector<Geometry*>* spaceItems, int pExp, glm::vec3 color, glm::vec3 sp, glm::vec3 km);
	void printAllData();

	void parseObjFile(std::string fn);
	void toLowerCase(std::string* str);
	std::vector<std::string> split(std::string str, char delimiter);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureUV;
	std::vector<std::vector<glm::vec3>> faces;


private:
	std::string filename;

};

#endif /* PARSER_H_ */
