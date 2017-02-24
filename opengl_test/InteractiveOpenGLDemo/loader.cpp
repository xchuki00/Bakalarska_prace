#include "loader.h"


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
		assert(Face.mNumIndices == 3);
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}

	std::cout << "nacten 3D modle " << path << std::endl;
	return indices.size();
}




