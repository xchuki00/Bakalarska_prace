#include "scene.h"
#include "includes.h"
#include "Shader.h"
#include "controls.h"
#include "player.h"
#include "projectile.h"
#include "target.h"
#include "weapon.h"
void scene::print()
{
	for (int i = 0; i < this->models.size();i++) {
		std::cerr << "model\t" << i << ":" << this->models[i]->classID << std::endl;

	}
	//std::cerr << "skybox\t"<< ":" << this->Skybox.textur << std::endl;
	//std::cerr << "ground\t" << ":" << this->Ground.textur << std::endl;
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
	btCollisionObject* i = this->bulletWord.addGround(mat,1,1,this->modelsXbullets.size());
	this->Ground.setRigidBodyIndex(this->modelsXbullets.size()); 
	this->Ground.setShader(this->shader, this->textureID, this->MVPID, this->viewID, this->modelID, this->DepthBiasID, this->shadowMapID, this->lightInvDirID, this->depthShader, this->depthMVPID);
	modelXbullet *mb = new modelXbullet();
	mb->setModel(&this->Ground);
	mb->setObj(i);
	this->modelsXbullets.push_back(mb);
	return 0;
}
int scene::drawGround()
{
		this->Ground.draw(this->depthTexture);
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
int scene::addModel(int clas, std::string pathOfObj, std::string pathOfTexture, glm::mat4 position, glm::vec3 velocity, float mass)
{
	if (clas == MODEL) {
		model *mod = new model();
		mod->load_3DModel(pathOfObj);
		mod->load_texture(pathOfTexture.c_str());
		mod->setPosition(position);
		mod->setVelocity(velocity);
		mod->setShader(this->shader, this->textureID, this->MVPID, this->viewID, this->modelID, this->DepthBiasID, this->shadowMapID, this->lightInvDirID, this->depthShader, this->depthMVPID);
		mod->buffer();
		btCollisionObject* i = bulletWord.addCollisionObject(position, velocity, mod->getVertices(), mass, this->models.size());
		mod->setRigidBodyIndex(this->modelsXbullets.size());
		this->models.push_back(mod);
		modelXbullet *mb = new modelXbullet();
		mb->setModel(mod);
		mb->setObj(i);
		this->modelsXbullets.push_back(mb);
		std::cerr << "model" << std::endl;
		return 0;
	}
	else if (clas == GROUND) {
		this->addGround(pathOfObj, pathOfTexture);
		std::cerr << "ground" << std::endl;
		return 0;
	}
	else if (clas == PROJECTIL) {
		projectile *proj = new projectile();
		proj->load_3DModel(pathOfObj);
		proj->load_texture(pathOfTexture.c_str());
		proj->setPosition(position);
		proj->setVelocity(velocity);
		proj->setShader(this->shader, this->textureID, this->MVPID, this->viewID, this->modelID, this->DepthBiasID, this->shadowMapID, this->lightInvDirID, this->depthShader, this->depthMVPID);
		proj->buffer();
		//btCollisionShape *shape = new btSphereShape(1);
		btCollisionObject* ip = bulletWord.addCollisionObject(position, velocity, proj->getVertices(), mass, this->models.size());
		//btCollisionObject* ip = bulletWord.addCollisionObject(position, velocity, shape, mass, this->models.size());

		proj->setRigidBodyIndex(this->modelsXbullets.size());
		this->models.push_back(proj);
		modelXbullet *mbp = new modelXbullet();
		mbp->setModel(proj);
		mbp->setObj(ip);
		this->modelsXbullets.push_back(mbp);
		std::cerr << "projectil" << std::endl;
		return 0;
	}
	else if (clas == PLAYER) {
		player *pl = new player();
		pl->load_3DModel(pathOfObj);
		pl->load_texture(pathOfTexture.c_str());
		pl->setPosition(position);
		pl->setVelocity(velocity);
		pl->setShader(this->shader, this->textureID, this->MVPID, this->viewID, this->modelID, this->DepthBiasID, this->shadowMapID, this->lightInvDirID, this->depthShader, this->depthMVPID);
		pl->buffer();
		btCollisionShape *shape = new btBoxShape(btVector3(1,1,1));
		//btCollisionShape *shape = new btSphereShape(1);
		btCollisionObject* ipl = bulletWord.addCollisionObject(position, velocity,shape, mass, this->models.size());
		//btCollisionObject* ipl = bulletWord.addCollisionObject(position, velocity, pl->getVertices(), mass, this->models.size());
		pl->setRigidBodyIndex(this->modelsXbullets.size());
		this->models.push_back(pl);
		modelXbullet *mbpl = new modelXbullet();
		mbpl->setModel(pl);
		mbpl->setObj(ipl);
		this->Player = pl;
		this->modelsXbullets.push_back(mbpl);
		std::cerr << "player" << std::endl;
		return 0;
	}
	else if (clas == TARGET) {
		target *targ = new target();
		targ->load_3DModel(pathOfObj);
		targ->load_texture(pathOfTexture.c_str());
		targ->setPosition(position);
		targ->setVelocity(velocity);
		targ->setShader(this->shader, this->textureID, this->MVPID, this->viewID, this->modelID, this->DepthBiasID, this->shadowMapID, this->lightInvDirID, this->depthShader, this->depthMVPID);
		targ->buffer();
		btCollisionObject* it = bulletWord.addCollisionObject(position, velocity, targ->getVertices(), mass, this->models.size());
		targ->setRigidBodyIndex(this->modelsXbullets.size());
		this->models.push_back(targ);
		modelXbullet *mbt = new modelXbullet();
		mbt->setModel(targ);
		mbt->setObj(it);
		this->modelsXbullets.push_back(mbt);
		std::cerr << "taget" << std::endl;
		return 0;
	}
	else if (clas == WEAPON) {
		weapon *w = new weapon();
		w->setShader(this->shader, this->textureID, this->MVPID, this->viewID, this->modelID, this->DepthBiasID, this->shadowMapID, this->lightInvDirID, this->depthShader, this->depthMVPID);

		w->loadWeapon(pathOfObj, pathOfTexture, position);
		this->models.push_back(w);
		modelXbullet *wmb = new modelXbullet();
		wmb->setModel(w);
		this->modelsXbullets.push_back(wmb);
	}
	else {
		std::cerr << "error\n";
		return 0;
	}
}

int scene::addModel(model * mod,float mass)
{
	//mod->setIndex(this->models.size());
	//btCollisionObject *obj= bulletWord.addCollisionObject(mod->getPosition(), mod->getVelocity(), mod->getVertices(), mass, mod->getIndex());
	//mod->setCollisionObject(obj);
	//this->models.push_back(mod);
	return 0;
}

int scene::removeModel(std::vector<int> destructionQueue)
{
	while (!destructionQueue.empty()) {
		int mXb = destructionQueue.back();
		destructionQueue.pop_back();
		if (this->modelsXbullets[mXb]->getModel() != NULL &&this->modelsXbullets[mXb]->getObj() != NULL) {
			this->bulletWord.world->removeCollisionObject(this->modelsXbullets[mXb]->getObj());
			this->modelsXbullets[mXb]->setObj(NULL);
			int pos = -1;
			//for (int i = 0; i < this->models.size();i++) {
			std::vector<model*>::iterator it = this->models.begin();
			while (it != this->models.end()) {
				if ((*it)->getRigidBodyIndex() ==mXb) {
					pos = 1;
					break;
				}
				it++;
			}
			if (pos != -1) {
				this->models.erase(it);
			}
			this->modelsXbullets[mXb]->setModel(NULL);
		}
	}
	return 0;
}


int scene::addShader(std::string vertexShader, std::string fragmentShader)
{
	this->shader = LoadShaders(vertexShader, fragmentShader);
	this->textureID = glGetUniformLocation(this->shader, "myTextureSampler");
	this->MVPID = glGetUniformLocation(this->shader, "MVP");
	this->viewID = glGetUniformLocation(this->shader,"V");
	this->modelID = glGetUniformLocation(this->shader, "M");
	this->DepthBiasID = glGetUniformLocation(this->shader, "DepthBiasMVP");
	this->shadowMapID = glGetUniformLocation(this->shader, "shadowMap");
	this->lightInvDirID = glGetUniformLocation(this->shader, "LightInvDirection_worldspace");

	return 0;
}

int scene::addDepthShader(std::string vertexShader, std::string fragmentShader)
{
	this->depthShader = LoadShaders(vertexShader,fragmentShader);
	this->depthMVPID = glGetUniformLocation(this->depthShader,"depthMVP");

	return 0;
}


int scene::drawAllModels()
{
	glBindFramebuffer(GL_FRAMEBUFFER,this->shadowBuffer);
	//glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->Ground.depthDraw();
	for (int i = 0; i < this->models.size(); i++) {
		this->models[i]->depthDraw();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->Ground.draw(this->depthTexture);
	this->Skybox.draw();
	
	for(int i=0;i<this->models.size();i++){
		if (this->models[i]->classID == WEAPON) {
			(static_cast<weapon*>(this->models[i]))->draw();
		}else{
			this->models[i]->draw(this->depthTexture);
		}
	}
	this->drawCrossHair();
	glfwSwapBuffers(this->window);
	glfwPollEvents();
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
	//btCollisionObjectArray objArray = this->bulletWord.world->getCollisionObjectArray();
	for (int i = 0; i<this->models.size(); i++) {
		//btCollisionObject *obj= objArray[this->models[i]->getRigidBodyIndex()];
		btCollisionObject *obj = this->modelsXbullets[this->models[i]->getRigidBodyIndex()]->getObj();
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform t;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(t);
			btVector3 vec = body->getLinearVelocity();
			this->models[i]->setVelocity(glm::vec3(vec[0], vec[1], vec[2]));
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
	std::vector<int> destructionQueue;
	for (int i = 0; i < colisions->size();i++) {
		
		//std::cerr << hitted->data()[i][0] << std::endl;
		//this->models[*hitted[i][0]]->hitted();
		//this->models[*hitted[i][1]]->hitted();
		
		int reaction;
		model *modA = this->modelsXbullets[colisions->data()[i][0]]->getModel();
		model *modB = this->modelsXbullets[colisions->data()[i][1]]->getModel();
		//std::cerr << this->models.size() << std::endl;
		if(modA->classID==PLAYER ||modB->classID==PLAYER)
			//std::cerr << modA->classID << "\t" << modB->classID << std::endl;
		if (modA->classID != GROUND) {
			if(modA->classID==PLAYER){
				//std::cerr << "PLAYER\n";
				reaction = (static_cast<player*>( modA))->hitted(modB);
			}
			else if(modA->classID==PROJECTIL){
				reaction = (static_cast<projectile*>(modA))->hitted(modB);
			}
			else {
				reaction = modA->hitted(modB);
			}
			if (reaction < 0) {
				destructionQueue.push_back(modA->getRigidBodyIndex());
			}
		}
		if (modB->classID != GROUND) {
			if (modB->classID == PLAYER) {
				//std::cerr << "PLAYER\n";
				reaction = (static_cast<player*>(modB))->hitted(modA);
			}
			else if (modB->classID == PROJECTIL) {
				reaction = (static_cast<projectile*>(modB))->hitted(modA);
			}
			else {
				reaction = modB->hitted(modA);
			}
			if (reaction < 0) {
				destructionQueue.push_back(modB->getRigidBodyIndex());
			}
		}
	}
	if (destructionQueue.size() != 0) {
		std::cerr << destructionQueue.size() << std::endl;
	}
	this->removeModel(destructionQueue);

}

int scene::initShadowBuffer()
{
	glGenFramebuffers(1, &this->shadowBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, this->shadowBuffer);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &this->depthTexture);
	glBindTexture(GL_TEXTURE_2D, this->depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, WIDTH, HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->depthTexture, 0);

	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;
	return 0;
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
	this->initShadowBuffer();
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
	glDeleteFramebuffers(1, &this->shadowBuffer);
	glDeleteTextures(1, &this->depthTexture);
	FreeImage_DeInitialise();
	glfwTerminate();
}
