#pragma once
#include "Model.h"

class Skybox :
	public Model
{
protected:
	std::vector<glm::vec3> ver;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> nor;
public:
	int load_3DModel(std::string path);
	int load_texture(
		const char* left,
		const char* front,
		const char* right,
		const char* back,
		const char* top,
		const char* bottom
	);
	void draw();
	int buffer();
	int addShader(std::string vertexShader, std::string fragmentShader);
	Skybox();
	~Skybox();
};

