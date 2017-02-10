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

void indexVBOmy(std::vector<glm::vec3> in_ver, std::vector<glm::vec2> in_uv, std::vector<glm::vec3> in_nor, std::vector<glm::vec3> out_ver, std::vector<glm::vec2> out_uv, std::vector<glm::vec3> out_nor, std::vector<unsigned short> indeces)
{




}
void mat4Rotate(glm::mat4 *mat, glm::vec3 dir,glm::vec3 up) {
	glm::vec3 left = glm::cross(dir,up);
	left=glm::normalize(left);

	//std::cerr << "LEFT" << glm::to_string(left) << "\n";
	//std::cerr << "UP"<<glm::to_string(up) << "\n";
	//std::cerr << "DIR" << glm::to_string(dir) << "\n";
	
	(*mat)[0][0] = left.x;
	(*mat)[0][1] = left.y;
	(*mat)[0][2] = left.z;
	
	(*mat)[1][0] = up.x;
	(*mat)[1][1] = up.y;
	(*mat)[1][2] = up.z;

	(*mat)[2][0] = dir.x;
	(*mat)[2][1] = dir.y;
	(*mat)[2][2] = dir.z;
	
}