#pragma once
#include "Model.h"
#include "Target.h"
#include "crossHair.h"
#include "BulletWorld.h"
#include "Player.h"
#include "Weapon.h"
class Scene
{
protected:
	//////////////////shaders///////////////
	GLuint shader;
	GLuint depthShader;
	GLuint shadowBuffer = 0;
	GLuint depthTexture;
	GLuint textureID;
	GLuint MVPID;
	GLuint viewID;
	GLuint modelID;
	GLuint DepthBiasID;
	GLuint shadowMapID;
	GLuint depthMVPID;
	GLuint lightInvDirID;
	GLuint VertexArrayID;
	/////////////crosshair/////////////
	crossHair CrossHair;
	////////////bullet////////////
	
	std::map < std::string, std::vector<MyVertex>> VerticesOfModels;
	std::map < std::string, std::vector<unsigned short>> IndicesOfModels;
	std::map <std::string, GLuint> LiberyOfTextures;
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
	int removeModels(std::vector <int> destructionQueue);
	int addShader(std::string vertexShader, std::string fragmentShader);
	int addDepthShader(std::string vertexShader, std::string fragmentShader);
	int drawAllModels();
	GLuint getTexture(std::string path);
	std::vector<MyVertex> get3DModel(std::string path);
	std::vector<unsigned short> getIndices(std::string path);
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

