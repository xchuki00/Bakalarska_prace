#include "misc.h"

void mat4Copy(glm::mat4 source, glm::mat4 *destination)
{
	for (int i = 0; i < 4; i++) {
		for(int j=0;j<4;j++){
			//std::cerr << (*destination)[i][j] << " kop " << source[i][j] << std::endl;
			(*destination)[i][j] = source[i][j];
		}
	}
}

void vec3Copy(glm::vec3 source, glm::vec3* destination)
{
	for (int i = 0; i < 3; i++) {
		(*destination)[i] = source[i];
	}
}

void printMat4(glm::mat4 source)
{
	for (int i = 0; i < 4; i++) {
		std::cerr<<"line"<<i<<"\t" << glm::to_string(source[i]) << std::endl;
	}
}

void printVec3(glm::vec3 source)
{
	std::cerr << glm::to_string(source) << std::endl;
}
