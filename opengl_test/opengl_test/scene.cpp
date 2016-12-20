#include "scene.h"
#include "includes.h"
#include "Shader.h"
#include "controls.h"


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
	std::cerr << glm::to_string(mat);
	this->Ground.setPosition(mat);
	mat = glm::translate(mat, glm::vec3(0.0f, -0.6f, 0.0f));
	int i = this->bulletWord.addGround(mat,1,1);
	this->Ground.setRigidBodyIndex(i);
	
	return 0;
}
int scene::drawGround()
{
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	//glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View*this->Ground.getMatrix();
	glUniformMatrix4fv(this->MVPID, 1, GL_FALSE, &MVP[0][0]);
	//nahraju texturu do shaderu
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->Ground.textur);
	glUniform1i(this->textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->Ground.vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->Ground.uvBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//std::cerr << sizeof(this->Skybox.vertexBuffer) << std::endl;
	//std::cerr << sizeof(this->models[i].vertexBuffer) << std::endl;
	glDrawArrays(GL_TRIANGLES, 0, this->Ground.getCountOfVertex());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

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
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	glm::mat4 mat(1.0f);
	glm::mat4 MV = Projection * View*getMyPosition();
	
	glUseProgram(this->Skybox.shader);
	glUniformMatrix4fv(this->Skybox.MVID, 1, GL_FALSE, &MV[0][0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->Skybox.textur);
	glUniform1i(this->Skybox.textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->Skybox.vertexBuffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);

	return 0;
}

//////////////////MODEL//////////////////////////////////

int scene::addModel(std::string pathOfObj, std::string pathOfTexture)
{
	model *mod = new model;
	mod->load_3DModel(pathOfObj);
	mod->load_texture(pathOfTexture.c_str());
	//bulletWord.addShape(glm::mat4(1.0f));
	this->models.push_back(mod);
	
	return 0;
}

int scene::addModel(std::string pathOfObj, std::string pathOfTexture, glm::mat4 position)
{
	model *mod = new model;
	mod->load_3DModel(pathOfObj);
	mod->load_texture(pathOfTexture.c_str());
	mod->setPosition(position);
	//mod.buffer();
	//bulletWord.addShape();
	this->models.push_back(mod);
	return 0;
	return 0;
}


int scene::addModel(std::string pathOfObj, std::string pathOfTexture, glm::mat4 position, GLfloat speed, glm::vec3 direction, btCollisionShape *shape, float mass)
{
	
	model *mod = new model;
	mod->load_3DModel(pathOfObj);
	mod->load_texture(pathOfTexture.c_str());
	mod->setPosition(position);
	mod->setSpeed(speed);
	mod->setDirection(direction);
	
	glm::vec3 velocity = direction*speed;
	mod->setIndex(this->models.size());
	int i=bulletWord.addCollisionObject(position,velocity,shape,mass,mod->getIndex());
	mod->setRigidBodyIndex(i);
	this->models.push_back(mod);
	return 0;
}

int scene::removeModel(int id)
{
	return 0;
}

int scene::addShader(std::string vertexShader, std::string fragmentShader)
{
	this->shader = LoadShaders(vertexShader, fragmentShader);
	this->textureID = glGetUniformLocation(this->shader, "textureSampler");
	this->MVPID = glGetUniformLocation(this->shader, "MVP");
	return 0;
}

int scene::bufferModels()
{
	//potøeba nahrát všechny modely do buffru a zapamatovat si jejich pozice
	for (int i=0; i < this->models.size(); i++) {
		this->models[i]->buffer();
	}
	return 0;
}

int scene::drawAllModels()
{
	
	//pro každý model vypoèítá nahraje do MVP v shaderu jeho mvp a pak zavola gldrwaarrays
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(this->shader);
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(int i=0;i<this->models.size();i++){
		glm::mat4 MVP = Projection * View * this->models[i]->getMatrix();
	//	std::cerr << glm::to_string(MVP) << std::endl;
		//nahraju matice do shaderu
		glUniformMatrix4fv(this->MVPID, 1, GL_FALSE, &MVP[0][0]);
		//nahraju texturu do shaderu
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->models[i]->textur);
		glUniform1i(this->textureID, 0);
		
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, this->models[i]->vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, this->models[i]->uvBuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//std::cerr << sizeof(this->Skybox.vertexBuffer) << std::endl;
		//std::cerr << sizeof(this->models[i].vertexBuffer) << std::endl;
		glDrawArrays(GL_TRIANGLES, 0, this->models[i]->getCountOfVertex());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

	}

	return 0;
}
int scene::drawCrossHair()
{
	return 0;
}

/////////////////INIT///////////////////////////
void scene::calculate()
{
	btTransform t;
	glm::mat4 mat;
	std::vector<int*> *hitted;
	hitted=this->bulletWord.calculate();
	for (int i = 0; i < this->models.size();i++) {
		
		t = this->bulletWord.getTransform(this->models[i]->getRigidBodyIndex());
		
		t.getOpenGLMatrix(glm::value_ptr(mat));
	//	std::cerr << glm::to_string(mat) << std::endl;
		this->models[i]->setPosition(mat);
		//std::cerr << i<<"\t"<<this->bulletWord.world->getNumCollisionObjects() << std::endl;
	}
	t = this->bulletWord.getTransform(this->Ground.getRigidBodyIndex());
	t.getOpenGLMatrix(glm::value_ptr(mat));
	//std::cerr << glm::to_string(mat);
	//this->Ground.setPosition(mat);
	for (int i = 0; i < hitted->size();i++) {
		
		std::cerr << hitted->data()[i][0] << std::endl;
		//this->models[*hitted[i][0]]->hitted();
		//this->models[*hitted[i][1]]->hitted();
		if (hitted->data()[i][0] != -1) {
			this->models[hitted->data()[i][0]]->hitted();

		}
		if (hitted->data()[i][1] != -1) {
			this->models[hitted->data()[i][1]]->hitted();

		}
	}
}

void scene::initCrossHair()
{
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
