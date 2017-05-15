#pragma once
#include "Model.h"

class Skybox :
	public Model
{
protected:
	std::vector<glm::vec3> ver;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> nor;
	GLuint dayTextur;
	GLuint nightTextur;
	GLuint sunTextur;
	GLuint moonTextur;
	GLuint dayTextureID;
	GLuint nightTextureID;
	GLuint dayID;
	GLuint axisID;
	std::vector<glm::vec3> axis;
	double* time;
	int dayPart = 0;
public:
	int load_3DModel(std::string path);
	int load_DayNighttexture(
		bool day,
		const char* left,
		const char* front,
		const char* right,
		const char* back,
		const char* top,
		const char* bottom
	);
	void calcAxis();
	void draw();
	int buffer();
	int addShader(std::string vertexShader, std::string fragmentShader);
	void setRefToTime(double * t);
	Skybox();
	~Skybox();
};

