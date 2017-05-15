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
#define MAX_VERTEX_BONES 4
/***********MODEL CLASS ENUM****************/
#define MODEL 0
#define GROUND 1 
#define SKYBOX 2
#define PLAYER 3
#define TARGET 4
#define PROJECTIL 5
#define WEAPON 6
#define SUNMOON 7
///////////HUD CLASS ENUM///////////
#define HUD 30
#define ARROWSTACK 31
#define HITSHUD 32
///////////enum pro navratove hodnoty funkce hitted
#define DESTROY -1;
#define DESTROY_BULLET - 2;
#define NOTHING 0;
/////////////PATH/////////////////
#pragma once
const std::string OBJ = "./../../3rd_parties/icons/obj/";
const std::string TEXT = "./../../3rd_parties/icons/texture/";
const std::string DAE = "./../../3rd_parties/icons/dae/";

///////////proste pi pro pocitani s radiany////////////
#pragma once
const float PI = 3.1415927f;
const double timeSpeed = 15;
const int dayLenght = 1440;