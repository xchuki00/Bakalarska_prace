#include <stdio.h>
#include <stdlib.h>
#include <ios>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <fstream>
#include <GL\GL.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <glm\ext.hpp>
#include <FreeImage.h>
#include <btBulletDynamicsCommon.h>
#include <map>
#include <iterator>
//#include <bt>
#define HEIGHT 1080
#define WIDTH 1920
/***********CLASS ENUM****************/
#define MODEL 0
#define GROUND 1 
#define SKYBOX 2
#define PLAYER 3
#define TARGET 4
#define PROJECTIL 5
#define WEAPON 6
///////////enum pro navratove hodnoty funkce hitted
#define DESTROY -1;
#define DESTROY_BULLET - 2;
#define NOTHING 0;
///////////proste pi pro pocitani s radiany////////////
const float PI = 3.1415927f;
///////////STRUCT pro vrchol/////////////////

#pragma once
struct MyVertex {
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 normal;

	MyVertex() {}

	MyVertex(glm::vec3 inpos, glm::vec2 inuv, glm::vec3 innormal)
	{
		pos = inpos;
		uv = inuv;
		normal = innormal;
	}
};