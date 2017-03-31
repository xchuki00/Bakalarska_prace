#pragma once
#include "includes.h"
#include "misc.h"
struct bone {
	aiMatrix4x4 matrix = aiMatrix4x4();
	aiMatrix4x4 offset = aiMatrix4x4();
	bone(aiMatrix4x4 off) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				offset[i][j] = off[i][j];
			}
		}
	}
};
struct VertexBone {
	unsigned int IDs[MAX_VERTEX_BONES];
	float Weights[MAX_VERTEX_BONES];
	VertexBone() {
		clear();
	};
	void clear() {
		for (int i = 0; i < MAX_VERTEX_BONES; i++) {
			IDs[i] = 0;
			Weights[i] = 0.0f;
		}
	}
	void addBone(unsigned int id, float w) {
		float pomW = 1;
		int j = 0;
		for (int i = 0; i < MAX_VERTEX_BONES; i++) {
			if (Weights[i] < w && Weights[i]<pomW) {
				j = i;
				pomW = Weights[i];
			}
		}
		if (Weights[j] != 0) {
			std::cerr << "vic jak 4 "<< std::endl;
		}
		Weights[j] = w;
		IDs[j] = id;
	}

};
#pragma once
struct MyVertex {
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 normal;
	//VertexBone bonesWeights;
	glm::vec4 ids;
	glm::vec4 weights;
	MyVertex() {}

	MyVertex(glm::vec3 inpos, glm::vec2 inuv, glm::vec3 innormal)
	{
		pos = inpos;
		uv = inuv;
		normal = innormal;
		ids = glm::vec4(0.0f);
		weights = glm::vec4(0.0f);
	}
	void addBone(int id, float w) {
		float pomW = 1;
		float j = 0;
		for (int i = 0; i < 4; i++) {
			if (weights[i] < w && weights[i]<pomW) {
				j = i;
				pomW = weights[i];
			}
		}
		weights[j] = w;
		ids[j] = float(id);
	}
};