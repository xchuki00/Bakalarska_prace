#include "includes.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
int loadObj(
	std::string path,
	std::vector < glm::vec3 > & out_vertices,
	std::vector < glm::vec2 > & out_uvs,
	std::vector < glm::vec3 > & out_normals
);

int loadObjAss(
	std::string path,
	std::vector < glm::vec3 > & out_vertices,
	std::vector < glm::vec2 > & out_uvs,
	std::vector < glm::vec3 > & out_normals
);