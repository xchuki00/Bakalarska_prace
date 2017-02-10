#include "weapon.h"
#include "misc.h"
#include "controls.h"
#include "Shader.h"
int weapon::loadWeapon(std::string model, std::string texture, glm::mat4 position)
{
	this->setPosition(position);
	//this->matrix = glm::scale(this->matrix, glm::vec3(0.03, 0.03, 0.03));
	this->matrix = glm::translate(this->matrix, 3 * getDir());
	//this->matrix = glm::rotate(this->matrix, (glm::mediump_float)90.0, glm::vec3(1,0,0));
	Assimp::Importer imp;
	const aiScene *scen = imp.ReadFile(model.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	if (scen == NULL) {
		std::cerr << "Error:Assimp load\n";
		return -1;
	}
	//std::cerr << "ASSIMP: num mesh:" << scen->mNumMeshes<<std::endl;
	const aiMesh* mesh = scen->mMeshes[0];
	std::cerr << "ASSIMP: num ver:" << mesh->mNumVertices<< std::endl;
	for (int i = 0; i < mesh->mNumVertices;i++) {
		vertex v(
			glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
			glm::vec2(0, 0),
			glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		this->vertices.push_back(v);
	}
	std::cerr << "ASSIMP: out:" <<this->vertices.size() << std::endl;
	std::cerr << "ASSIMP: num ver:" << mesh->mNumFaces << std::endl;
	for (int i = 0; i < mesh->mNumFaces; i++) {
		const aiFace& Face = mesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		this->indices.push_back(Face.mIndices[0]);
		this->indices.push_back(Face.mIndices[1]);
		this->indices.push_back(Face.mIndices[2]);
	}
	this->NumIndices = this->indices.size();
	std::cerr << "ASSIMP: out:" << this->indices.size() << std::endl;
	glGenBuffers(1, &this->VB);
	glBindBuffer(GL_ARRAY_BUFFER, this->VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices) * this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * NumIndices, &this->indices[0], GL_STATIC_DRAW);
	this->shader = LoadShaders("simple.vertexshader","simple.fragmentshader");
	//this->textureID = glGetUniformLocation(this->shader, "myTextureSampler");
	this->MVPID = glGetUniformLocation(this->shader, "MVP");
	//std::cerr << "ASSIMP: pos:" << glm::to_string(this->matrix) << std::endl;
	return 0;
}

void weapon::draw()
{
	//std::cerr << "ASSIMP: pos:" << glm::to_string(this->matrix) << std::endl;
	//std::cerr << "WEAPON DRAW";
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glUseProgram(this->shader);
	glm::mat4 Projection = getProject();
	glm::mat4 View = getView();
	glm::mat4 MVP = Projection * View * this->matrix;
	glUniformMatrix4fv(this->MVPID, 1, GL_FALSE, &MVP[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, this->VB);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*)sizeof(glm::vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*)(sizeof(glm::vec2)+ sizeof(glm::vec3)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IB);

	glDrawElements(GL_TRIANGLES, this->NumIndices, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//std::cerr << "sdaw";
	this->Wposition(glm::mat4(1.0f));
}
void weapon::Wposition(glm::mat4 mat)
{
	//std::cerr << "sdaw";
	this->setPosition(getMyPosition());
	this->matrix = glm::translate(this->matrix, 3 * getDir());
	//this->matrix = glm::translate(this->matrix, getRight());
	this->matrix = glm::scale(this->matrix, glm::vec3(0.1, 0.1, 0.1));
	
	//this->matrix=glm::translate(this->matrix, getChange());
	mat4Rotate(&this->matrix, getDir(), getUp());
	//this->matrix = glm::translate(this->matrix, getDir());
	


}

weapon::weapon()
{
	this->classID = WEAPON;
}


weapon::~weapon()
{
}
