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
#include "crossHair.h"
#include "sunMoon.h"
Scene::Scene()
{
}


Scene::~Scene()
{

	////std::cerr << "delete" << std::endl;
	for (int i = 0; i < this->models.size(); i++) {
		delete this->models[i];
	}
	for each (Model* var in this->specialModels)
	{
		delete var;
	}
	Sound::deleteEngine(this->background->getEngine());
	glDeleteProgram(this->shader);
	glDeleteProgram(this->ShadowShader);
	glDeleteVertexArrays(1, &this->VertexArrayID);
	for each (std::pair<std::string, ImportModel*> var in this->importModels)
	{
		delete var.second;
	}
	for each (std::pair<std::string, Hud*> var in this->hud)
	{
		delete var.second;
	}
	for (std::map<std::string, GLuint>::iterator it = this->LiberyOfTextures.begin(); it != this->LiberyOfTextures.end(); it++) {
		glDeleteTextures(1, &it->second);
	}
	delete skybox;
	delete wind;
	this->background->deleteEngine(this->background->getEngine());
	delete background;
	glDeleteFramebuffers(this->directionLights.size(), &this->shadowBuffer[0]);
	glDeleteTextures(this->directionLights.size(), &this->shadowTexture[0]);
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
		m->setShadowShader(this->ShadowShader);
		m->set3DModel(this->getModel(pathOfObj));
		m->setTexture(this->getTexture(pathOfTexture, GL_BGRA));
		m->setPosition(position);
		m->setSoundEngine(this->background->getEngine());
		m->setWind(this->wind);
		m->setObj(this->bulletWorld.addCollisionObject(position, velocity, mass, m));
		this->models.push_back(m);
		////std::cerr << "MODEL " << pathOfObj << " s texturou " << pathOfTexture << " vlozen." << std::endl;
		return m;
	case GROUND:
		m = new Ground();

		m->setShader(this->shader);
		m->setShadowShader(this->ShadowShader);
		m->set3DModel(this->getModel(pathOfObj));
		m->setTexture(this->getTexture(pathOfTexture, GL_BGRA));
		m->setPosition(position);
		m->setSoundEngine(this->background->getEngine());
		m->setObj(this->bulletWorld.addCollisionObject(position, velocity, mass, m));
		position[3].y -= 0.25;
		//((Ground*)m)->setPlane(this->bulletWorld.addCollisionObject(position, velocity, mass, m, new btStaticPlaneShape(btVector3(0, 1, 0), 1)));
		//m->setObj(this->bulletWorld.addCollisionObject(position, velocity, mass, m, new btStaticPlaneShape(btVector3(0, 1, 0), 1)));
		this->models.push_back(m);
		////std::cerr << "MODEL " << pathOfObj << " s texturou " << pathOfTexture << " vlozen." << std::endl;
		return m;
	default:
		////std::cerr << "MODEL " << pathOfObj << " s texturou " << pathOfTexture << " neni vlozen typ" << std::endl;
		return nullptr;
	}
}

Model * Scene::addProjectil(std::string pathOfObj, std::string pathOfTexture,int mass)
{
	Projectil *m = new Projectil();
	m->setShader(this->shader);
	m->setShadowShader(this->ShadowShader);
	m->set3DModel(this->getModel(pathOfObj));
	m->setTexture(this->getTexture(pathOfTexture, GL_BGRA));
	m->setSoundEngine(this->background->getEngine());
	m->init();
	m->setWind(this->wind);
	//m->setObj(this->bulletWorld.addCollisionObject(m->getPosition(), glm::vec3(0,0,0), mass, m));
	//btRigidBody *rb = btRigidBody::upcast(m->getObj());
	//rb->setActivationState(DISABLE_SIMULATION);
	this->models.push_back(m);
	////std::cerr << "PROJECTIL " << pathOfObj << " s texturou " << pathOfTexture << " vlozen."<< std::endl;
	return m;
}

Projectil *p;
Model * Scene::addWeapon(std::string pathOfObj, std::string pathOfTexture, Projectil* pl)
{
	Weapon *w = new Weapon();
	p = pl;
	w->setShader(this->shader);
	w->setShadowShader(this->ShadowShader);
	w->set3DModel(this->getModel(pathOfObj));
	w->setTexture(this->getTexture(pathOfTexture, GL_RGBA));
	w->init(pl);
	w->setSoundEngine(this->background->getEngine());
	//m->setObj(this->bulletWorld.addCollisionObject(position, velocity, mass, m));
	this->models.push_back(w);

	////std::cerr << "WEAPON " << pathOfObj << " s texturou " << pathOfTexture << " vlozen." << std::endl;
	return w;
}
Model * Scene::addPlayer(std::string pathOfObj, std::string pathOfTexture, glm::mat4 position, glm::vec3 velocity, Weapon * w, float mass)
{

	Player* pl = new Player();
	pl->setShader(this->shader);
	pl->setShadowShader(this->ShadowShader);
	pl->set3DModel(this->getModel(pathOfObj));
	pl->setTexture(this->getTexture(pathOfTexture, GL_RGBA));
	pl->setPosition(position);
	pl->setWeapon(w);
	pl->setSoundEngine(this->background->getEngine());
	pl->setObj(this->bulletWorld.addCollisionObject(position, velocity, mass, pl, new btBoxShape(btVector3(1, 1, 1))));
	pl->setWind(this->wind);
	pl->setBulletWorld(this->bulletWorld.world);
	this->models.push_back(pl);
	this->player = pl;
	////std::cerr << "PLAYER " << pathOfObj << " s texturou " << pathOfTexture << " vlozen." << std::endl;

	return pl;
}



int Scene::addSkybox(std::string left, std::string front, std::string right, std::string back, std::string top, std::string bottom)
{
	Skybox *s = new Skybox();
	s->load_DayNighttexture(true,left.c_str(), front.c_str(), right.c_str(), back.c_str(), top.c_str(), bottom.c_str());

	s->load_DayNighttexture(
		false,
		(TEXT+"skyboxes/night/starfield_lf.tga").c_str(),
		(TEXT + "skyboxes/night/starfield_ft.tga").c_str(),
		(TEXT + "skyboxes/night/starfield_rt.tga").c_str(),
		(TEXT + "skyboxes/night/starfield_bk.tga").c_str(),
		(TEXT + "skyboxes/night/starfield_up.tga").c_str(),
		(TEXT+"skyboxes/night/starfield_dn.tga").c_str());
	s->addShader("./shaders/skybox.vertexShader", "./shaders/skybox.fragmentShader");
	s->load_3DModel(OBJ+"skybox.obj");
	s->setRefToTime(&GameTime);
	//s->buffer();
	this->skybox = s;
	return 0;
}
void Scene::addSunMoon(std::string path, std::string texture, float offset, float period, float r,float angle,DirectionLight* l)
{
	SunMoon* sm = new SunMoon();
	sm->set3DModel(this->getModel(path));
	sm->setTexture(this->getTexture(texture, GL_BGRA));
	
	sm->setPeriod(period);
	sm->setLightSource(l);
	sm->setRefToTime(&this->GameTime);
	sm->setCircle(r,angle);
	sm->setOffset(offset);
	this->specialModels.push_back(sm);

	//
	////std::cerr << "SUNMOON " << path << " s texturou " << texture << " vlozen." << std::endl;

}
void Scene::drawSpecialModels()
{
	for each (Model* var in this->specialModels)
	{
		var->draw(this->directionLights);
	}
}
int Scene::addShader(std::string vertexShader, std::string fragmentShader)
{
	this->shader = LoadShaders(vertexShader,fragmentShader);
	this->dirlightID = glGetUniformLocation(this->shader, "dl");
	this->cameraID = glGetUniformLocation(this->shader, "CameraPos");
	this->shadowTextureID = glGetUniformLocation(this->shader, "ShadowTextureSampler");

	this->countOfLightID = glGetUniformLocation(this->shader, "countOfLight");
	return 0;
}

int Scene::addDepthShader(std::string vertexShader, std::string fragmentShader)
{
	this->ShadowShader = LoadShaders(vertexShader, fragmentShader);

	return 0;
}

int Scene::drawAllModels()
{
	GameTime = fmod((glfwGetTime()*timeSpeed), dayLenght);

	static float fps = 0;
	static double lastTime = 0;
	if (GameTime > lastTime + 1) {
		((HitsHud*)this->hud.at("fps"))->setContains((float)(fps/(GameTime-lastTime)));
		fps = 0;
		lastTime = GameTime;
	}
	fps+=1;
	this->addToWindDirection(this->wind->getLocalWind(this->player->getPosition()[3]), 1);
	glm::vec3 pos=this->player->getPosition()[3];
	glm::vec3 dir = getDir();
	this->background->getEngine()->setListenerPosition(vec3df(pos.x, pos.y, pos.z) ,
		vec3df(dir.x, dir.y, dir.z));
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0, 0, WIDTH, HEIGHT);
	glDisable(GL_CULL_FACE);
	/*glCullFace(GL_BACK);*/
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glUseProgram(this->shader);
	glUniform3f(this->cameraID,getVectorOfPosition().x, getVectorOfPosition().y, getVectorOfPosition().z);
	glUniform1i(this->countOfLightID, this->directionLights.size());
	glUniform1fv(this->dirlightID, 8 * this->directionLights.size(), &this->directionLights[0].color[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *this->shadowTexture);
	glUniform1i(this->shadowTextureID, 0);
	for (int i = 0; i<this->models.size(); i++) {
		//this->models[i]->draw(this->directionLights[0].dir);
		this->models[i]->draw(this->directionLights);
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	this->drawSpecialModels();
	this->skybox->draw();
	this->drawHud();
	glfwSwapBuffers(this->window);
	glfwPollEvents();
	return 0;
}

int Scene::drawAllModelsToShadowMap()
{
	for (int j = 0; j < this->directionLights.size(); j++) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->shadowBuffer[j]);
		glClear(GL_DEPTH_BUFFER_BIT);
		//glDisable(GL_CULL_FACE);
		glViewport(0, 0, WIDTH * 5, HEIGHT * 5);
		glEnableVertexAttribArray(0);
		glUseProgram(this->ShadowShader);
		for (int i = 0; i < this->models.size(); i++) {
			this->models[i]->DrawToShadowMap(this->directionLights[j].dir);
		}
		glViewport(0, 0, WIDTH, HEIGHT);
		glDisableVertexAttribArray(0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		/*glEnable(GL_CULL_FACE);*/
	}
	return 0;
}

GLuint Scene::getTexture(std::string path,GLuint code)
{
	try {
		this->LiberyOfTextures.at(path);
	}
	catch (const std::out_of_range& oor) {
		int h, w;

		this->LiberyOfTextures.emplace(path, loadTexture2d(path.c_str(), &h, &w,code));
	}
	return this->LiberyOfTextures.at(path);;
}

ImportModel * Scene::getModel(std::string path)
{
	try {
		this->importModels.at(path);
	}
	catch (const std::out_of_range& oor) {
		////std::cerr <<"PATH: " <<path<<std::endl;
		ImportModel *imodel = new ImportModel(path);
		this->importModels.emplace(path, imodel);
	}
	return this->importModels.at(path);
}
void Scene::addDirectionLight(glm::vec3 color, glm::vec3 direction, float AmbientIntensity, float diffuseIntensity)
{
	this->directionLights.push_back(DirectionLight(color, direction, AmbientIntensity, diffuseIntensity));
	glGenFramebuffers(1, &this->shadowBuffer[this->directionLights.size() - 1]);

	glGenTextures(1, &this->shadowTexture[this->directionLights.size()-1]);
	glBindTexture(GL_TEXTURE_2D, this->shadowTexture[this->directionLights.size() - 1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, WIDTH * 5, HEIGHT * 5, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, this->shadowBuffer[this->directionLights.size()- 1]);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->shadowTexture[this->directionLights.size() - 1], 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
}
///add element to hud, path of texture, position = x,y position of left corner on screen and x,y size
///uv = column and row in texture and number of column and row


int Scene::addHudElement(int classID, std::string key, std::string path, glm::vec4 position, glm::vec4 uv)
{
	Hud *h;
	switch (classID)
	{
	case HUD:
		h = new Hud();
		break;
	case ARROWSTACK:
		h = new ArrowStack();
		break;
	case HITSHUD:
		h = new HitsHud();
		break;
	default:
		h = new Hud();
		break;
	}
	h->init(path);
	h->setPosition(position.x, position.y, position.z, position.w);
	h->setRowAColumn(uv.x, uv.y, uv.z, uv.w);
	//h->buffer();
	this->hud.emplace(key, h);
	return 0;
}

int Scene::addHudElement(std::string path, Hud * hud)
{
	if (hud != NULL) {
		this->hud.emplace(path, hud);
	}
	else {
		return -1;
	}
	return 0;
}

int Scene::drawHud()
{
	
	for(std::map<std::string,Hud*>::iterator it=this->hud.begin();it!=this->hud.end();++it){
		it->second->draw();
	}
	return 0;
}

Hud * Scene::getHud(std::string path)
{
	return this->hud.at(path);
}

void Scene::setHudShaders(std::string vectorPath, std::string fragmentPath)
{
	Hud::setShader(vectorPath, fragmentPath);
}

void Scene::setWindHud(HitsHud * hh)
{
	this->windHud = hh;

}

void Scene::addWind(float strength, glm::vec3 dir)
{
	this->wind = new Wind();
	this->wind->init(dir,strength);
}

void Scene::addToWindStrength(float increase)
{
	//this->windSrenght += increase;
	//std::ostringstream ss;
	//ss << this->windDirect.x*this->windSrenght << "," << this->windDirect.y*this->windSrenght << "," << this->windDirect.z*this->windSrenght;
	//this->windHud->setContains(ss.str());

}

void Scene::addToWindDirection(glm::vec3 dir, float angle)
{
	//this->windDirect=glm::rotate(this->windDirect,angle, dir);

	std::ostringstream ss;
	ss << roundf(dir.x* 100) / 100 << "," << roundf(dir.y * 100) / 100 << "," << roundf(dir.z * 100) / 100;
	this->windHud->setContains(ss.str());

}

void Scene::drawAllModelToWindMap()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->wind->shadowBuffer);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, WIDTH * 5, HEIGHT * 5);
	glEnableVertexAttribArray(0);
	glUseProgram(this->ShadowShader);
	for (int i = 0; i<this->models.size(); i++) {
		this->models[i]->DrawToShadowMap(this->wind->getDir());
	}
	glViewport(0, 0, WIDTH, HEIGHT);
	glDisableVertexAttribArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//void Scene::CalculatePositionOfAddicted() {
//	for (auto &m : this->models) {
//		m->calc();
//	}
//}
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

	////std::cerr << glm::to_string(mat);
	//this->Ground.setPosition(mat);
	std::vector<std::pair<Model *, int>> destructionQueue;// = new std::vector<std::pair<Model *, int>>();
	for (int i = 0; i < colisions->size(); i+=2) {
		int reaction;
		if (colisions->data()[i] != NULL) {
			////std::cerr << modA->classID << std::endl;
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
	//	//std::cerr << "DESTRO" << destructionQueue.size() << std::endl;
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
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.5f,10);
	this->bulletWorld.init();
	this->background = Sound::createEngine();
	return 0;
}
