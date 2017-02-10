#pragma once
#include "model.h"
struct vertex {
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 normal;

	vertex() {}

	vertex(glm::vec3 inpos, glm::vec2 inuv, glm::vec3 innormal)
	{
		pos = inpos;
		uv = inuv;
		normal = innormal;
	}
};
class weapon :
	public model
{
	private:
		std::vector<vertex> vertices;
		//std::vector<unsigned int> indecies;

		GLuint VB;
		GLuint IB;
		unsigned int NumIndices;
		unsigned int MaterialIndex;
	public:
		int loadWeapon(std::string model, std::string texture, glm::mat4 position);
		void draw();
		void Wposition(glm::mat4 mat);
		weapon();
		~weapon();
};

