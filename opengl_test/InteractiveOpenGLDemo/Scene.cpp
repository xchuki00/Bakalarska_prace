#include "Scene.h"
#include "Ground.h"
#include "Skybox.h"
#include "Player.h"
#include "Target.h"
#include "Projectil.h"
#include "Weapon.h"
#include "Shader.h"
#include "texture.h"
#include "loader.h"
#include "controls.h"
Scene::Scene()
{
}


Scene::~Scene()
{

	std::cerr << "delete" << std::endl;
	/*for (int i = 0; i < this->models.size(); i++) {
	delete this->models[i];
	}*/
	glDeleteProgram(this->shader);
	glDeleteVertexArrays(1, &this->VertexArrayID);
	for (std::map<std::string, GLuint>::iterator it = this->LiberyOfTextures.begin(); it != this->LiberyOfTextures.end(); it++) {
		glDeleteTextures(1, &it->second);
	}
	//glDeleteFramebuffers(1, &this->shadowBuffer);
	//glDeleteTextures(1, &this->depthTexture);
	FreeImage_DeInitialise();
	glfwTerminate();
}



Model* Scene::addModel(int clas, std::string pathOfObj, std::string pathOfTexture, glm::mat4 position, glm::vec3 velocity, float mass)
{
	Model *m;
	//glm::mat4 mat(1.0f);
	switch (clas) {
	case MODEL:
		m = new Model();

		m->setShader(this->shader);
		//m->load_3DModel(pathOfObj);
	//	m->load_texture(pathOfTexture.c_str());
		m->set3DModel(this->getModel(pathOfObj));
		m->setTexture(this->getTexture(pathOfTexture));
		m->setPosition(position);
		this->bulletWorld.addCollisionObject(position, velocity, mass, m);
		this->models.push_back(m);
		std::cerr << "MODEL " << pathOfObj << " s texturou " << pathOfTexture << " vlozen." << std::endl;
		return m;
	case GROUND:
		m = new Ground();

		m->setShader(this->shader);
		m->set3DModel(this->getModel(pathOfObj));
		m->setTexture(this->getTexture(pathOfTexture));
		//mat = glm::translate(mat, glm::vec3(0.0f, -2.5f, 0.0f));
		m->setPosition(position);
		//mat = glm::translate(mat, glm::vec3(0.0f, -0.6f, 0.0f));
		//m->setObj(this->bulletWorld.addGround(mat,m));
		//m->setPosition(position);
		this->bulletWorld.addCollisionObject(position,velocity,mass,m);
		this->models.push_back(m);
		std::cerr << "MODEL " << pathOfObj << " s texturou " << pathOfTexture << " vlozen." << std::endl;
		return m;

	default:
		std::cerr << "MODEL " << pathOfObj << " s texturou " << pathOfTexture << " neni vlozen typ" << std::endl;
		return nullptr;
	}
	//m->setShader(this->shader);
}

Model * Scene::addProjectil(std::string pathOfObj, std::string pathOfTexture,int mass)
{
	Projectil *m = new Projectil();
	m->setShader(this->shader);
	m->set3DModel(this->getModel(pathOfObj));
	m->setTexture(this->getTexture(pathOfTexture));
	m->init();
	//m->setObj(this->bulletWorld.addCollisionObject(m->getPosition(), glm::vec3(0,0,0), mass, m));
	//btRigidBody *rb = btRigidBody::upcast(m->getObj());
	//rb->setActivationState(DISABLE_SIMULATION);
	this->models.push_back(m);
	std::cerr << "PROJECTIL " << pathOfObj << " s texturou " << pathOfTexture << " vlozen."<< std::endl;
	return m;
}

Model * Scene::addWeapon(std::string pathOfObj, std::string pathOfTexture, Projectil* pl)
{
	Weapon *w = new Weapon();
	w->setShader(this->shader);
	w->set3DModel(this->getModel(pathOfObj));
	w->setTexture(this->getTexture(pathOfTexture));
	w->init(pl);
	//m->setObj(this->bulletWorld.addCollisionObject(position, velocity, mass, m));
	this->models.push_back(w);
	std::cerr << "WEAPON " << pathOfObj << " s texturou " << pathOfTexture << " vlozen." << std::endl;
	return w;
}

Model * Scene::addPlayer(std::string pathOfObj, std::string pathOfTexture, glm::mat4 position, glm::vec3 velocity, Weapon * w, float mass)
{
	Player* pl = new Player();
	pl->setShader(this->shader);
	pl->set3DModel(this->getModel(pathOfObj));
	pl->setTexture(this->getTexture(pathOfTexture));
	pl->setPosition(position);
	pl->setWeapon(w);
	pl->setObj(this->bulletWorld.addCollisionObject(position, velocity, mass, pl, new btBoxShape(btVector3(1, 1, 1))));
	pl->setBulletWorld(this->bulletWorld.world);
	this->models.push_back(pl);
	this->player = pl;
	std::cerr << "PLAYER " << pathOfObj << " s texturou " << pathOfTexture << " vlozen." << std::endl;

	return pl;
}

int Scene::addSkybox(const char * left, const char * front, const char * right, const char * back, const char * top, const char * bottom)
{
	Skybox *s = new Skybox();
	s->load_texture(left, front, right, back, top, bottom);
	s->addShader("skybox.vertexShader", "skybox.fragmentShader");
	s->load_3DModel("./icons/skybox.obj");
	//s->buffer();
	this->skybox = s;
	return 0;
}
int Scene::addShader(std::string vertexShader, std::string fragmentShader)
{
	this->shader = LoadShaders(vertexShader,fragmentShader);
	this->dirlightID = glGetUniformLocation(this->shader, "dl");
	this->cameraID = glGetUniformLocation(this->shader, "CameraPos");
	return 0;
}

int Scene::addDepthShader(std::string vertexShader, std::string fragmentShader)
{
	return 0;
}

int Scene::drawAllModels()
{

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glUseProgram(this->shader);
	glUniform3f(this->cameraID,getVectorOfPosition().x, getVectorOfPosition().y, getVectorOfPosition().z);
	glUniform1fv(this->dirlightID,8,&this->directionLights[0].color[0]);
	for (int i = 0; i<this->models.size(); i++) {
		this->models[i]->draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	this->skybox->draw();
	this->drawCrossHair();
	glfwSwapBuffers(this->window);
	glfwPollEvents();
	return 0;
}

GLuint Scene::getTexture(std::string path)
{

	try {
		this->LiberyOfTextures.at(path);
	}
	catch (const std::out_of_range& oor) {
		int h, w;

		this->LiberyOfTextures.emplace(path, loadTexture2d(path.c_str(), &h, &w));
	}
	return this->LiberyOfTextures.at(path);;
}

ImportModel * Scene::getModel(std::string path)
{
	try {
		this->importModels.at(path);
	}
	catch (const std::out_of_range& oor) {
		ImportModel *imodel = new ImportModel(path);
		this->importModels.emplace(path, imodel);
	}
	return this->importModels.at(path);
}
void Scene::addDirectionLight(glm::vec3 color, glm::vec3 direction, float AmbientIntensity, float diffuseIntensity)
{
	this->directionLights.push_back(DirectionLight(color, direction, AmbientIntensity, diffuseIntensity));
}
int Scene::addCrossHair(std::string path)
{
	this->CrossHair.init(path);
	this->CrossHair.buffer();
	return 0;
}

int Scene::drawCrossHair()
{
	this->CrossHair.draw();
	return 0;
}


void Scene::CalculatePositionOfAddicted() {
	for (auto &m : this->models) {
		m->calc();
	}
}
void Scene::calculate()
{

	btTransform t;
	glm::mat4 mat;
	std::vector<Model*> *colisions;
	colisions = this->bulletWorld.calculate();
	//btCollisionObjectArray objArray = this->bulletWord.world->getCollisionObjectArray();
	for (int i = 0; i<this->models.size(); i++) {
		//btCollisionObject *obj= objArray[this->models[i]->getRigidBodyIndex()];
		if (this->models[i]->getObj() != NULL) {

			btCollisionObject *obj = this->models[i]->getObj();
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform t;
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(t);
				//t = obj->getWorldTransform();
			}
			else
			{
				t = obj->getWorldTransform();
			}
			t.getOpenGLMatrix(glm::value_ptr(mat));
			this->models[i]->setPosition(mat);
		}
	}

	//std::cerr << glm::to_string(mat);
	//this->Ground.setPosition(mat);
	std::vector<std::pair<Model *, int>> destructionQueue;// = new std::vector<std::pair<Model *, int>>();
	for (int i = 0; i < colisions->size(); i+=2) {
		int reaction;
		if (colisions->data()[i] != NULL) {
			//std::cerr << modA->classID << std::endl;
			if (colisions->data()[i]->classID != GROUND) {
					reaction = colisions->data()[i]->hitted(colisions->data()[i+1]);
				if (reaction < 0) {
					destructionQueue.push_back(std::pair<Model*,int>(colisions->data()[i],reaction));
				}
			}
		}
		if (colisions->data()[i+1] != NULL) {
			if (colisions->data()[i + 1]->classID != GROUND) {
					reaction = colisions->data()[i + 1]->hitted(colisions->data()[i]);
				if (reaction < 0) {
					destructionQueue.push_back(std::pair<Model*, int>(colisions->data()[i+1], reaction));

				}
			}
		}
	}
//	if (destructionQueue.size() != 0) {
	//	std::cerr << "DESTRO" << destructionQueue.size() << std::endl;
	//}
	this->removeModels(destructionQueue);
}

int Scene::removeModels(std::vector<std::pair<Model *, int>>destructionQueue)
{
	for each (std::pair<Model *, int> var in destructionQueue)
	{
		switch (var.second)
		{
		case -1:	//DESTROY 
			break;
		case -2:	//DESTROY_BULLET :
		{
			if (var.first->getObj() != nullptr) {
				btRigidBody* body = btRigidBody::upcast(var.first->getObj());
				if (body && body->getMotionState())
				{
					delete body->getMotionState();
				}
				this->bulletWorld.world->removeCollisionObject(var.first->getObj());
				delete var.first->getObj();
				var.first->setObj(nullptr);
			}
			break; 
		}
		default:
			break;
		}
	}
	return 0;
}
int Scene::initShadowBuffer()
{
	return 0;
}

int Scene::initWindow()
{
	if (!glfwInit()) {
		fprintf(stderr, "Error: glfwInit fail\n");
		return 1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(WIDTH, HEIGHT, "window", NULL, NULL);
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
	glfwSetCursorPos(this->window, WIDTH / 2, HEIGHT / 2);

	//pozadi
	glClearColor(0.0f, 0.0f, 0.64f, 0.0f);
	FreeImage_Initialise(true);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glGenVertexArrays(1, &this->VertexArrayID);
	glBindVertexArray(this->VertexArrayID);
	this->bulletWorld.init();
	return 0;
}
