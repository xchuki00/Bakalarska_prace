#include "ImportModel.h"



std::vector<MyVertex> ImportModel::getVertices()
{
	return this->vertices;
}

std::vector<unsigned short> ImportModel::getIndices()
{
	return this->indices;
}

bool ImportModel::hasAnimation()
{
	return (this->Animation!=nullptr)?true:false;
}

animation * ImportModel::getAnimation()
{
	return this->Animation;
}

ImportModel::ImportModel(std::string path)
{
		this->Animation = new animation();
		const aiScene *scen = this->Animation->imp->ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
		if (scen == NULL) {
			std::cerr << "Error:Assimp load\n";
			throw;
		}
		const aiMesh* mesh = scen->mMeshes[0];
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < mesh->mNumVertices; i++) {
			const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
			float x = pTexCoord->x;
			MyVertex v(
				glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),

				glm::vec2(pTexCoord->x, pTexCoord->y),
				glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
			this->vertices.push_back(v);
		}
		for (int i = 0; i < mesh->mNumFaces; i++) {
			const aiFace& Face = mesh->mFaces[i];
					for (int j = 0; j < Face.mNumIndices; j++) {
				this->indices.push_back(Face.mIndices[j]);
			}
		}
		if (mesh->HasBones()) {
			aiBone **b = mesh->mBones;
			int count = mesh->mNumBones;
			int boneID = 0;
			//pridat kost do boneMap
			for (int i = 0; i < count; i++) {
				std::string boneName = b[i]->mName.data;
				if (this->Animation->bonesMap.find(boneName) == this->Animation->bonesMap.end()) {
					boneID = this->Animation->bonesMap.size();
					this->Animation->bonesMap.emplace(boneName, boneID);
					this->Animation->bones.push_back(b[i]->mOffsetMatrix);
				}
				else {
					boneID = this->Animation->bonesMap[boneName];
				}

				for (int j = 0; j < b[i]->mNumWeights; j++) {
					this->vertices[b[i]->mWeights[j].mVertexId].addBone(boneID, b[i]->mWeights[j].mWeight);
				}
			}
		}

		if (scen->HasAnimations()) {
			this->Animation->setRootNode(scen->mRootNode);
			this->Animation->setAnimation(scen->mAnimations[0]);
		}
		else
		{
			delete this->Animation;
			this->Animation = nullptr;
		}

}


ImportModel::~ImportModel()
{
}
