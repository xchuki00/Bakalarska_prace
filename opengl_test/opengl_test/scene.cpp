#include "scene.h"
#include "includes.h"
#include "Shader.h"
#include "controls.h"
#include "player.h"

void scene::print()
{
	for (int i = 0; i < this->models.size();i++) {
		std::cerr << "model\t" << i << ":" << this->models[i]->textur << std::endl;

	}
	std::cerr << "skybox\t"<< ":" << this->Skybox.textur << std::endl;
	std::cerr << "ground\t" << ":" << this->Ground.textur << std::endl;
}
/////////////////GROUND///////////////////////////////
int scene::addGround(std::string pathOfObj, std::string pathOfTexture)
{
	this->Ground.load_3DModel(pathOfObj);
	this->Ground.load_texture(pathOfTexture.c_str());
	std::cerr << "textura v addground" << this->Ground.textur << "\t" << std::endl;
	this->Ground.buffer();
	glm::mat4 mat(1.0f);
	mat = glm::translate(mat,glm::vec3(0.0f,-0.5f,0.0f));
	//std::cerr << glm::to_string(mat);
	this->Ground.setPosition(mat);
	mat = glm::translate(mat, glm::vec3(0.0f, -0.6f, 0.0f));
	int i = this->bulletWord.addGround(mat,1,1);
	this->Ground.setRigidBodyIndex(i);
	this->Ground.setShader(this->shader,this->textureID,this->MVPID);
	return 0;
}
int scene::drawGround()
{
		this->Ground.draw();
	return 0;
}
////////////////////////////SKYBOX//////////////////////////
int scene::addSkybox(std::string left, std::string front, std::string right, std::string back, std::string top, std::string bottom,std::string vertexShader,std::string fragmentShader)
{
	this->Skybox.init();
	this->Skybox.load_texture(
		left.c_str(),
		front.c_str(),
		right.c_str(),
		back.c_str(),
		top.c_str(),
		bottom.c_str()
	);
	this->Skybox.addShader(vertexShader, fragmentShader);
	this->Skybox.buffer();
	return 0;
}



int scene::drawSkybox()
{
	this->Skybox.draw();
	return 0;
}

//////////////////MODEL//////////////////////////////////





int scene::addModel(std::string pathOfObj, std::string pathOfTexture, glm::mat4 position, glm::vec3 velocity, float mass)
{
	
	model *mod = new model;
	mod->load_3DModel(pathOfObj);
	mod->load_texture(pathOfTexture.c_str());
	mod->setPosition(position);
	mod->setVelocity(velocity);
	mod->setIndex(this->models.size());
	mod->setShader(this->shader, this->textureID, this->MVPID);
	mod->buffer();
	int i = bulletWord.addCollisionObject(position, velocity, mod->getVertices(), mass, this->models.size());
	mod->setRigidBodyIndex(i);
	this->models.push_back(mod);
	return 0;
}

int scene::addPlayer(std::string pathOfObj, std::string pathOfTexture, glm::mat4 position,glm::vec3 velocity,float mass)
{
	player *mod = new player;
	//model *mod = new model;
	mod->load_3DModel(pathOfObj);
	mod->load_texture(pathOfTexture.c_str());
	mod->setPosition(position);
	mod->setVelocity(velocity);
	mod->setIndex(this->models.size());
	mod->setShader(this->shader, this->textureID, this->MVPID);
	mod->buffer();
	int i = bulletWord.addCollisionObject(position, velocity, mod->getVertices(), mass, this->models.size());
	mod->setRigidBodyIndex(i);
	this->models.push_back(mod);
	return 0;
}

int scene::addModel(model * mod,float mass)
{
	//mod->setIndex(this->models.size());
	//btCollisionObject *obj= bulletWord.addCollisionObject(mod->getPosition(), mod->getVelocity(), mod->getVertices(), mass, mod->getIndex());
	//mod->setCollisionObject(obj);
	//this->models.push_back(mod);
	return 0;
}

int scene::removeModel(std::vector<model*> destructionQueue)
{
	//destructionQueue
	return 0;
}


int scene::addShader(std::string vertexShader, std::string fragmentShader)
{
	this->shader = LoadShaders(vertexShader, fragmentShader);
	this->textureID = glGetUniformLocation(this->shader, "textureSampler");
	this->MVPID = glGetUniformLocation(this->shader, "MVP");
	return 0;
}


int scene::drawAllModels()
{
	for(int i=0;i<this->models.size();i++){
	
		this->models[i]->draw();
	}

	return 0;
}
//////////////////////////CROSSHAIR/////////////////
int scene::bufferCrossHair(std::string path) {
	this->CrossHair.init(path);
	this->CrossHair.buffer();

	return 0;
}
int scene::drawCrossHair()
{
	this->CrossHair.draw();
	return 0;
}

int scene::getModelsSize()
{
	return this->models.size();
}

/////////////////INIT///////////////////////////
void scene::calculate()
{
	btTransform t;
	glm::mat4 mat;
	std::vector<int*> *colisions;
	colisions=this->bulletWord.calculate();
	btCollisionObjectArray objArray = this->bulletWord.world->getCollisionObjectArray();
	for (int i = 0; i<this->models.size(); i++) {
		btCollisionObject *obj= objArray[this->models[i]->getRigidBodyIndex()];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform t;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(t);

		}
		else
		{
			t = obj->getWorldTransform();
		}
		t.getOpenGLMatrix(glm::value_ptr(mat));
		this->models[i]->setPosition(mat);
	}
	//std::cerr << glm::to_string(mat);
	//this->Ground.setPosition(mat);
	std::vector<model*> destructionQueue;
	for (int i = 0; i < colisions->size();i++) {
		
		//std::cerr << hitted->data()[i][0] << std::endl;
		//this->models[*hitted[i][0]]->hitted();
		//this->models[*hitted[i][1]]->hitted();
		/*
		int reaction;
		if (colisions->data()[i][0] != -1) {
			reaction= this->models[colisions->data()[i][0]]->hitted(this->models[colisions->data()[i][1]]);
			if (reaction < 0) {
				destructionQueue.push_back(this->models[colisions->data()[i][0]]);
			}
		}
		if (colisions->data()[i][1] != -1) {
			reaction= this->models[colisions->data()[i][1]]->hitted(this->models[colisions->data()[i][0]]);
			if (reaction < 0) {
				destructionQueue.push_back(this->models[colisions->data()[i][1]]);
			}
		}*/
	}
	this->removeModel(destructionQueue);

}


int scene::initWindow()
{
	if (!glfwInit()) {
		fprintf(stderr, "Error: glfwInit fail\n");
		return 1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(HEIGHT, WIDTH, "window", NULL, NULL);
	if (this->window == NULL) {
		fprintf(stderr, "Error:glfwCreateWindow fail\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(this->window);
	//glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Error: glewInit fail\n");
		return 1;
	}
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE); //vstup klavesnice

	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //vstup mys

																 //vychozi pozice mysi
	glfwPollEvents();
	glfwSetCursorPos(this->window, 1024 / 2, 768 / 2);

	//pozadi
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	FreeImage_Initialise(true);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glGenVertexArrays(1, &this->VertexArrayID);
	glBindVertexArray(this->VertexArrayID);
	this->bulletWord.initBullet();
	return 0;
}

scene::scene()
{
}


scene::~scene()
{

	std::cerr << "delete" << std::endl;
	/*for (int i = 0; i < this->models.size(); i++) {
		delete this->models[i];
	}*/
	glDeleteProgram(this->shader);
	glDeleteTextures(1, &this->textureID);
	glDeleteVertexArrays(1, &this->VertexArrayID);
	FreeImage_DeInitialise();
	glfwTerminate();
}
