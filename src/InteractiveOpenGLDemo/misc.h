#pragma once
#include "includes.h"
void mat4Copy(glm::mat4 source, glm::mat4 *destination);
void mat4Copy(const aiMatrix4x4 source, aiMatrix4x4 *destination);
void vec3Copy(glm::vec3 source, glm::vec3* destination);
void printMat4(glm::mat4 source);
void printVec3(glm::vec3 source);
void indexVBOmy(
	std::vector<glm::vec3> in_ver,
	std::vector<glm::vec2> in_uv,
	std::vector<glm::vec3> in_nor,
	
	std::vector<glm::vec3> out_ver,
	std::vector<glm::vec2> out_uv,
	std::vector<glm::vec3> out_nor,
	std::vector<unsigned short> indeces
);
void mat4Rotate(glm::mat4 *mat, glm::vec3 dir,glm::vec3 up);
float AngleBetween(glm::vec3 first, glm::vec3 second);
void printNodeHiearchy(const aiNode *Nodes);
float distance(glm::vec3 x, glm::vec3 y);