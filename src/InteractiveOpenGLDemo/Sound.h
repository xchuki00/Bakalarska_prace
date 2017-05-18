#pragma once
#include <iostream>
#include <irrKlang.h>
#include "includes.h"
using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib")
class Sound
{
public:
	ISoundEngine* engine;
	ISound* music = NULL;
	ISoundEngine* getEngine();
	static Sound* createEngine();
	static void deleteEngine(ISoundEngine* engine);
	void setEngine(ISoundEngine* e);
	void play2D(std::string path, bool looped);
	void play3D(std::string path, glm::vec3 position, bool loop);
	Sound();
	virtual~Sound();
};

