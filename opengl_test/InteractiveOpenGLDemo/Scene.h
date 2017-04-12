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
class Scene
{
protected:
	//////////////////shaders///////////////
	GLuint shader;
	GLuint ShadowShader;
	GLuint shadowBuffer = 0;
	GLuint shadowTexture;
	GLuint shadowTextureID;
	GLuint VertexArrayID;
	GLuint dirlightID;
	GLuint cameraID;
	/////////////HUD/////////////

	std::map<std::string,Hud*> hud;
	///////////skybox////////////////
	Skybox *skybox;
	////////////bullet////////////
	std::map <std::string,ImportModel *> importModels;
	std::map < std::string, GLuint> LiberyOfTextures;
	////////////Enviroment///////////
	float windSrenght = 0;
	glm::vec3 windDirect = glm::vec3(0,0,10);
	HitsHud* windHud = nullptr;

public:

	std::vector<DirectionLight> directionLights;
	BulletWorld bulletWorld;
	GLFWwindow* window;
	std::vector <Model*> models;
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
	int addSkybox(const char* left,
		const char* front,
		const char* right,
		const char* back,
		const char* top,
		const char* bottom);
	//void CalculatePositionOfAddicted();
	////////////Enviroment/////////
	void addWind(float strength, glm::vec3 dir);
	void addToWindStrength(float increase);
	void addToWindDirection(glm::vec3 dir, float angle);
	////////////INIT///////////
	void calculate();

	int initWindow();
	Scene();
	~Scene();
};

