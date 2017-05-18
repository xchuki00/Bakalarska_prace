#pragma once
#include "Model.h"
#include "Target.h"
#include "Skybox.h"
#include "crossHair.h"
#include "BulletWorld.h"
#include "Player.h"
#include "Weapon.h"
#include "animation.h"
#include "ImportModel.h"
#include "Hud.h"
#include "Wind.h"
class Scene
{
protected:
	//////////////////shaders///////////////
	GLuint shader;
	GLuint ShadowShader;
	GLuint shadowBuffer[10];
	GLuint shadowTexture[10];
	GLuint shadowTextureID;
	GLuint VertexArrayID;
	GLuint dirlightID;
	GLuint cameraID;
	GLuint countOfLightID;
	/////////////HUD/////////////

	std::map<std::string,Hud*> hud;
	///////////skybox////////////////
	Skybox *skybox;
	////////////bullet////////////
	std::map <std::string,ImportModel *> importModels;
	std::map < std::string, GLuint> LiberyOfTextures;
	////////////Enviroment///////////
	Wind *wind;
	HitsHud* windHud = nullptr;
	Sound* background;

public:
	double GameTime = 0;
	std::vector<DirectionLight> directionLights;
	BulletWorld bulletWorld;
	GLFWwindow* window;
	std::vector <Model*> models;
	std::vector <Model*> specialModels;
	Player *player;

	Model* addModel(
		int clas,
		std::string pathOfObj,
		std::string pathOfTexture,
		glm::mat4 position,
		glm::vec3 velocity, 
		float mass
	);
	Model* addProjectil(std::string pathOfObj,std::string pathOfTexture, int mass);
	Model* addWeapon(std::string pathOfObj,
		std::string pathOfTexture, Projectil *pl);
	Model* addPlayer(
		std::string pathOfObj,
		std::string pathOfTexture,
		glm::mat4 position,
		glm::vec3 velocity,
		Weapon *w,
		float mass);
	int removeModels(std::vector <std::pair<Model *, int>>destructionQueue);
	int addShader(std::string vertexShader, std::string fragmentShader);
	int addDepthShader(std::string vertexShader, std::string fragmentShader);
	int drawAllModels();
	int drawAllModelsToShadowMap();
	GLuint getTexture(std::string path,GLuint code);
	ImportModel* getModel(std::string path);
	void addDirectionLight(glm::vec3 color, glm::vec3 direction, float AmbientIntensity, float diffuseIntensity);
	//////////////////////HUD///////////
	int addHudElement(int classID,std::string key,std::string path,glm::vec4 position, glm::vec4 uv);
	int addHudElement(std::string path, Hud* hud);
	int drawHud();
	Hud *getHud(std::string path);
	void setHudShaders(std::string vectorPath, std::string fragmentPath);
	void setWindHud(HitsHud* hh);
	///////////////skybox////////
	int addSkybox(std::string left,
		std::string front,
		std::string right,
		std::string back,
		std::string top,
		std::string bottom);
	void addSunMoon(std::string path, std::string texture, float offset, float period,float r, float angle, DirectionLight* l);
	void drawSpecialModels();
	//void CalculatePositionOfAddicted();
	////////////Enviroment/////////
	void addWind(float strength, glm::vec3 dir);
	void addToWindStrength(float increase);
	void addToWindDirection(glm::vec3 dir, float angle);
	void drawAllModelToWindMap();
	////////////INIT///////////
	void calculate();

	int initWindow();
	Scene();
	virtual~Scene();
};

