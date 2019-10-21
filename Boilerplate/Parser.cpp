/*
 * Parser.cpp
 *
 *  Created on: Nov. 18, 2018
 *      Author: bille
 */

#include "Parser.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include <stdio.h>
#include <glm/vec3.hpp>

Parser::Parser() {
	//this->filename = fn;
	//parser function
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

/*
void Parser::parseAnObj(std::string source, std::vector<Geometry*>* spaceItems, int pExp, glm::vec3 color, glm::vec3 sp, glm::vec3 km) {
	std::string currentLine;
		std::ifstream myfile(source);
		std::cout << source << "is " << myfile.is_open() << "\n";
		std::vector<glm::vec3> points;
		if (myfile.is_open()) {
			while (getline(myfile, currentLine)) {
				removeWhiteSpaces(&currentLine);
				if (currentLine[0] == '#' || currentLine.empty() || currentLine[0] == '}' || currentLine[0] == '{') continue;
				// else create a triangle object

				if (currentLine[0] == 'v') {
					// remove v
					currentLine = currentLine.substr(1, std::string::npos);
					removeWhiteSpaces(&currentLine);
					// parse point
					glm::vec3 aPoint = parseVec(currentLine);
					points.push_back(aPoint);
				} else if (currentLine[0] == 'f') {
					// remove v
					currentLine = currentLine.substr(1, std::string::npos);
					removeWhiteSpaces(&currentLine);
					// parse triangle object
					glm::vec3 pointsToUse = parseVec(currentLine);

					// create triangle
					Triangle* aNewTri = new Triangle(points[pointsToUse.x - 1], points[pointsToUse.y - 1], points[pointsToUse.z - 1], pExp, color, sp, km);
					spaceItems->push_back(aNewTri);

				} else {
					std::cout << "Unidentified line: " << currentLine << "\n";
					exit(-1);
				}
			}
		}

}
*/

// shitty to lower case function
void Parser::toLowerCase(std::string* str) {
	std::transform(str->begin(), str->end(), str->begin(), ::tolower);

}

std::vector<std::string> Parser::split(std::string str, char delimiter) {
	std::vector<std::string> strVec;
	std::istringstream stream(str);
	std::string token;

	while (getline(stream, token, delimiter)) {
		strVec.push_back(token);
	}

	return strVec;

}

void Parser::parseObjFile(std::string fn) {
	// clear vectors for new data to be stored
	vertices.clear();
	normals.clear();
	textureUV.clear();
	faces.clear();

	std::string currentLine;
	std::ifstream myFile(fn);
	std::cout << fn << " " << "file status: " << myFile.is_open() << "\n";

	if (myFile.is_open()) {
		while (getline(myFile, currentLine)) {
			// remove leading and trailing white spaces
			removeWhiteSpaces(&currentLine);

			// split current line by spaces
			// ensures that blank lines are skipped
			std::vector<std::string> tokens;
			if (!currentLine.empty()) {
				tokens = split(currentLine, ' ');

			} else {
				continue;
			}
			std::string identifier = tokens[0];

			// lower case for consistent comparison
			toLowerCase(&identifier);

			/*
			for (int i = 1; i < tokens.size(); i++) {
				if (identifier == "f") {
					std::cout << "token " << i+1 << " " << tokens[i] << "\n";
				} else {
					break;
				}
			}
			*/


			if (currentLine[0] == '#' || currentLine[0] == '{' || currentLine[0] == '{') {
				continue;
			} else if (identifier == "f") {
				//face contains format
				// 1/2/3 4/5/6 7/8/9
				// FORMAT: VERTEX INDEX/TEXTURE INDEX/NORMAL INDEX
				std::vector<glm::vec3> container;
				if (tokens.size() == 4) {
					// start 1 since index 0 contains identifier
					for (int i = 1; i < 4; i++) {
						glm::vec3 aVec(0);
						std::vector<std::string> coords = split(tokens[i], '/');
						// convert each values into float and save them into vectors
						for (int j = 0; j < 3; j++) {
							aVec[j] = toFloat(coords[j]);
							//std::cout << "vec " << j << " = " << aVec[j] << " ";
						}
						container.push_back(aVec);
					}
					faces.push_back(container);
				} else {
					std::cout << "Parsing error with 'f' tokens size = " << tokens.size() << "\n";
				}
			} else if (identifier == "v" || identifier == "vn") {
				// vertices and vertex normals have format
				// 1.0 2.0 3.0
				if (tokens.size() == 4) {
					glm::vec3 aVec(0);
					// start 1 since index 0 contains identifier
					for (int i = 1; i < 4; i++) {
						// index of aVec still starts at 0
						aVec[i-1] = toFloat(tokens[i]);
					}
					if (identifier == "v") {
						vertices.push_back(aVec);
					} else {
						normals.push_back(aVec);
					}
				} else {
					std::cout << "Parsing error with " << identifier << " tokens size = " << tokens.size() << "\n";
				}

			} else if (identifier == "vt") {
				// texture coordinates has format
				// 1.0 2.0
				if (tokens.size() == 3) {
					glm::vec2 aVec(0);
					// start 1 since index 0 contains identifier
					for (int i = 1; i < 3; i++) {
						aVec[i-1] = toFloat(tokens[i]);
					}
					textureUV.push_back(aVec);

				} else {
					std::cout << "Parsing error with " << identifier << " tokens size = " << tokens.size() << "\n";
				}

			} else {
				std::cout << "Unaccounted identifier: ";
				std::cout << identifier << "\n";
				std::cout << "Skipping line.\n";
			}

		}
	}
}

void Parser::printAllData() {
	std::cout << "vertices parsed: " << "\n";
	for (unsigned int i = 0; i < vertices.size(); i++) {
		glm::vec3 currentVer = vertices[i];
		std::cout << "Vertex " << i+1 << ": ";
		for (unsigned int j = 0; j < 3; j++) {
			std::cout << currentVer[j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "Faces parsed: " << "\n";
	for (unsigned int i = 0; i < faces.size(); i++) {
		std::vector<glm::vec3> currentFace = faces[i];
		std::cout << "Face " << i + 1 << ": ";
		for (int j = 0; j < 3; j++) {
			glm::vec3 currentCoords = currentFace[j];
			for (int k = 0; k < 3; k++) {
				std::cout<< currentCoords[k] << "/";
			}
			std::cout << " ";
		}
		std::cout << "\n";
	}

	std::cout << "textureUVs parsed: " << "\n";
	for (unsigned int i = 0; i < textureUV.size(); i++) {
		glm::vec2 currentVer = textureUV[i];
		std::cout << "TextureUv " << i+1 << ": ";
		for (unsigned int j = 0; j < 2; j++) {
			std::cout << currentVer[j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "Normals parsed: " << "\n";
	for (unsigned int i = 0; i <  normals.size(); i++) {
		glm::vec3 currentVer = normals[i];
		std::cout << "Normal " << i+1 << ": ";
		for (unsigned int j = 0; j < 3; j++) {
			std::cout << currentVer[j] << " ";
		}
		std::cout << "\n";
	}

}

/*
void Parser::parseScene(std::string source, std::vector<Geometry*>* spaceItems, std::vector<Light>* lights) {
	std::string currentLine;
	std::ifstream myfile(source);
	std::cout << source << "is " << myfile.is_open() << "\n";
	if (myfile.is_open()) {
		while (getline(myfile, currentLine)) {
			// remove leading and trailing white spaces
			removeWhiteSpaces(&currentLine);
			//std::cout << currentLine << "\n";
			// skips irrelevant lines
			if (currentLine[0] == '#' || currentLine.empty() || currentLine[0] == '}' || currentLine[0] == '{') continue;

			if (currentLine == ("light {") || currentLine == ("light")) {
				//std::cout <<currentLine <<"light triggered \n";
				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);

				glm::vec3 pos = parseVec(currentLine);
				Light aNewLight(pos);
				lights->push_back(aNewLight);

			} else if (currentLine == ("triangle {") || currentLine == ("triangle")) {
				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 p0 = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 p1 = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 p2 = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				float pExp = parseFloat(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 color = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 specularC = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 mirrorC = parseVec(currentLine);

				Triangle* aNewTri = new Triangle(p0, p1, p2, pExp, color, specularC, mirrorC);
				spaceItems->push_back(aNewTri);
			} else if (currentLine == ("plane {") || currentLine == ("plane")) {
				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 normal = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 point = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				float pExp = parseFloat(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 color = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 specularC = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 mirrorC = parseVec(currentLine);

				Plane* aNewPlane = new Plane(normal, point, pExp, color, specularC, mirrorC);
				spaceItems->push_back(aNewPlane);
			} else if(currentLine == ("sphere {") || currentLine == ("sphere")) {
				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 center = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				//std::cout <<currentLine << "\n";
				float radius = parseFloat(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				float pExp = parseFloat(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 color = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 specularC = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 mirrorC = parseVec(currentLine);

				Sphere* aNewSphere = new Sphere(center, radius, pExp, color, specularC, mirrorC);
				spaceItems->push_back(aNewSphere);

			} else {
				std::cout << "Encountered Unknown line " << currentLine << "\n";
				std::cout <<"Terminating Program\n";
				exit(-1);
			}


		}
	}
	myfile.close();

}

*/

void Parser::removeWhiteSpaces(std::string* str) {
	std::size_t ind = str->find_first_not_of(" \t");
	str->erase(0, ind);

	ind = str->find_last_not_of(" \t");
	if (std::string::npos != ind) {
		str->erase(ind+1);
	}

}


float Parser::toFloat(std::string line) {
	//std::string::size_type sz;
	float output = std::stof(line);
	return output;
}

/*
glm::vec3 Parser::parseVec(std::string str) {
	std::cout << str << "\n";
	std::string::size_type sz;

	float x = std::stof(str, &sz);
	std::string subS = str.substr(sz);
	float y = std::stof(subS, &sz);
	subS = subS.substr(sz);
	float z = std::stof(subS, &sz);

	std::cout << "x value = " << x << "\n";
	std::cout << "y value = " << y << "\n";
	std::cout << "z value = " << z << "\n";

	return glm::vec3(x, y ,z);

}

*/



