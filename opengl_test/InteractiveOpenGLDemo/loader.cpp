#include "loader.h"
#include "misc.h"
int loadObj(std::string path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>&out_normals) {
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;
	
	std::ifstream obj(path);
	if (!(obj.is_open())) {

		std::cerr << "ERROR:soubor " << path << " se nepodarilo otevrit!" << std::endl;
		return -1;
	}

	std::string word;
	while (!obj.eof()) {
		obj >> word;
			if (strcmp(word.c_str(), "v") == 0) {
				glm::vec3 vertex;
				obj >> vertex.x;
				obj >> vertex.y;
				obj >> vertex.z;
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(word.c_str(), "vt") == 0) {
				glm::vec2 uv;
				obj >> uv.x;
				obj >> uv.y;
				temp_uvs.push_back(uv);
			}
			else if (strcmp(word.c_str(), "vn") == 0) {
				glm::vec3 norm;
				obj >> norm.x;
				obj >> norm.y;
				obj >> norm.z;
				temp_normals.push_back(norm);
			}
			else if (strcmp(word.c_str(), "f") == 0) {
					std::vector< int > vertex;
				
				for (int j = 0; j < 3; j++) {
					obj >> word;
					
					std::stringstream in(word);
					for (int i = 0; i < 3; i++) {
						std::string s;
						std::getline(in, s, '/');
						vertex.push_back(atoi(s.c_str()));
					}
				}
				
				vertexIndices.push_back(vertex[0]);
				vertexIndices.push_back(vertex[3]);
				vertexIndices.push_back(vertex[6]);
				uvIndices.push_back(vertex[1]);
				uvIndices.push_back(vertex[4]);
				uvIndices.push_back(vertex[7]);
				normalIndices.push_back(vertex[2]);
				normalIndices.push_back(vertex[5]);
				normalIndices.push_back(vertex[8]);
			}
	}
	obj.close();
		if (vertexIndices.size() <= 0 || temp_vertices.size() <= 0) {
		std::cerr << "Error: NEnacten 3D modle " << path << std::endl;
		return 1;
	}
	for (int i = 0; i < vertexIndices.size(); i++) {
		out_vertices.push_back(temp_vertices[vertexIndices[i] - 1]);
	}
	for (int i = 0; i < uvIndices.size(); i++) {
		out_uvs.push_back(temp_uvs[uvIndices[i] - 1]);
	}
	for (int i = 0; i < normalIndices.size(); i++) {
		out_normals.push_back(temp_normals[normalIndices[i]-1]);
	}
	std::cout << "nacten 3D modle " << path << uvIndices.size() << "\t" << temp_uvs.size() << std::endl;

	return 0;
}

int loadObjAss(std::string path, std::vector<MyVertex>& out_vertices, std::vector<unsigned short>& indices)
{

	Assimp::Importer imp;
	const aiScene *scen = imp.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	if (scen == NULL) {
		std::cerr << "Error:Assimp load\n";
		return -1;
	}
	//std::cerr << "ASSIMP: num mesh:" << scen->mNumMeshes<<std::endl;
	const aiMesh* mesh = scen->mMeshes[0];
	std::cerr << "ASSIMP: num ver:" << mesh->mNumVertices << std::endl;
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < mesh->mNumVertices; i++) {
		const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
		MyVertex v(
			glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
			//glm::vec2(pTexCoord->x, pTexCoord->y),
			glm::vec2(0, 0),
			glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		out_vertices.push_back(v);
	}
	std::cerr << "ASSIMP: out:" << out_vertices.size() << std::endl;
	std::cerr << "ASSIMP: num face:" << mesh->mNumFaces << std::endl;
	for (int i = 0; i < mesh->mNumFaces; i++) {
		const aiFace& Face = mesh->mFaces[i];
		//assert(Face.mNumIndices == 3);
		for (int j = 0; j < Face.mNumIndices; j++) {
			indices.push_back(Face.mIndices[j]);
		}/*
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	*/
	}

	std::cout << "nacten 3D modle " << path << std::endl;
	return indices.size();
}

int loadAnimated(std::string path,Model *model)
{
	model->animation = new animation();
	const aiScene *scen = model->animation->imp->ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	if (scen == NULL) {
		std::cerr << "Error:Assimp load\n";
		return -1;
	}
	//std::cerr << "ASSIMP: num mesh:" << scen->mNumMeshes<<std::endl;
	const aiMesh* mesh = scen->mMeshes[0];
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < mesh->mNumVertices; i++) {
		const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
		MyVertex v(
			glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
			//glm::vec2(pTexCoord->x, pTexCoord->y),
			glm::vec2(0, 0),
			glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		model->vertices.push_back(v);
	}
	for (int i = 0; i < mesh->mNumFaces; i++) {
		const aiFace& Face = mesh->mFaces[i];
		//assert(Face.mNumIndices == 3);
		for (int j = 0; j < Face.mNumIndices; j++) {
			model->indices.push_back(Face.mIndices[j]);
		}/*
		 indices.push_back(Face.mIndices[0]);
		 indices.push_back(Face.mIndices[1]);
		 indices.push_back(Face.mIndices[2]);
		 */
	}
	if (mesh->HasBones()) {
		aiBone **b = mesh->mBones;
		int count = mesh->mNumBones;
		int boneID=0;
		//pridat kost do boneMap
		for (int i = 0; i < count; i++) {
			std::string boneName = b[i]->mName.data;
			if (model->animation->bonesMap.find(boneName) == model->animation->bonesMap.end()) {
				boneID = model->animation->bonesMap.size();
				model->animation->bonesMap.emplace(boneName, boneID);
				model->animation->bones.push_back(b[i]->mOffsetMatrix);
				model->finalTransform.push_back(aiMatrix4x4());
			}
			else {
				boneID = model->animation->bonesMap[boneName];
			}

			for (int j = 0; j < b[i]->mNumWeights; j++) {
				model->vertices[b[i]->mWeights[j].mVertexId].addBone(boneID, b[i]->mWeights[j].mWeight);
			}
		}
	}
	if (scen->HasAnimations()) {
		model->animation->setRootNode(scen->mRootNode);
		model->animation->setAnimation(scen->mAnimations[0]);
		model->setAnimatonShaderID();
		}
	else {
		delete model->animation;
		model->animation = nullptr;
	}
	return model->indices.size();
}

int loadAnimated(std::string path, ImportModel * imodel)
{
	return 0;
}






