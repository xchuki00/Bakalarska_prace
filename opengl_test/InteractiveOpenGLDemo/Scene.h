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
class Scene
{
protected:
	//////////////////shaders///////////////
	GLuint shader;
	GLuint depthShader;
	GLuint shadowBuffer = 0;
	GLuint depthTexture;
	GLuint VertexArrayID;
	GLuint dirlightID;
	GLuint cameraID;
	/////////////crosshair/////////////
	crossHair CrossHair;
	///////////skybox////////////////
	Skybox *skybox;
	////////////bullet////////////
	std::map <std::string,ImportModel *> importModels;
	std::map < std::string, GLuint> LiberyOfTextures;
	std::vector<DirectionLight> directionLights;
public:
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
	GLuint getTexture(std::string path);
	ImportModel* getModel(std::string path);
	void addDirectionLight(glm::vec3 color, glm::vec3 direction, float AmbientIntensity, float diffuseIntensity);
	//////////////////////crosshair///////////
	int addCrossHair(std::string path);
	int drawCrossHair();
	///////////////skybox////////
	int addSkybox(const char* left,
		const char* front,
		const char* right,
		const char* back,
		const char* top,
		const char* bottom);
	void CalculatePositionOfAddicted();
	////////////INIT///////////
	void calculate();
	int initShadowBuffer();

	int initWindow();
	Scene();
	~Scene();
};

