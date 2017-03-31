#include "includes.h"
#include "structures.h"
#include "Model.h"
int loadObj(
	std::string path,
	std::vector < glm::vec3 > & out_vertices,
	std::vector < glm::vec2 > & out_uvs,
	std::vector < glm::vec3 > & out_normals
);

int loadObjAss(
	std::string path,
	std::vector <MyVertex> & out_vertices,
	std::vector <unsigned short>& indices
);

int loadAnimated(
	std::string path,
	Model *model
);
