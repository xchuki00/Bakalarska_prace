#include "Sound.h"





ISoundEngine * Sound::getEngine()
{
	return this->engine;
}

Sound * Sound::createEngine()
{
	Sound *s = new Sound();
	s->setEngine(createIrrKlangDevice());
	return s;
}

void Sound::deleteEngine(ISoundEngine * engine)
{
	engine->drop();
}

void Sound::setEngine(ISoundEngine * e)
{
	this->engine = e;
}

void Sound::play2D(std::string path, bool looped)
{

}

void Sound::play3D(std::string path, glm::vec3 position, bool loop)
{

	this->music = engine->play3D(path.c_str(),
	vec3df(position.x, position.y, position.z), loop, false, true);
}

Sound::Sound()
{
}

Sound::~Sound()
{
	if (music != NULL) {
		this->music->drop();
	}
}
