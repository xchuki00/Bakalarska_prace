#version 400
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;
layout(location = 3) in vec4 boneID;
layout(location = 4) in vec4 boneWeight;

//array of bone's final matrixs
out vec2 uv;
out vec3 pos;
out vec3 normal;
out vec4 lightPos[10];
flat out int count;
uniform int countOfLight;
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 LVP[10];
uniform mat4 gBones[50];

void main(){
mat4 boneT = mat4(1.0f);
	if(boneWeight[0]>0){		
		boneT	   = gBones[int(boneID[0])] * boneWeight[0];
		boneT     += gBones[int(boneID[1])] * boneWeight[1];
		boneT     += gBones[int(boneID[2])] * boneWeight[2];
		boneT     += gBones[int(boneID[3])] * boneWeight[3];
	}
	vec4 p=boneT*vec4(vertexPosition_modelspace,1.0);
	gl_Position = MVP*vec4(p.xyz,1.0);	
	uv=vertexUV;
	normal=(M * boneT *vec4(vertexNormal_modelspace,0.0)).xyz;
	
	pos=(M * p).xyz;
	count = countOfLight;
	for(int i =0;i<countOfLight;i++){
		lightPos[i] = LVP[i] *vec4(p.xyz,1.0);
	}
	//lightPos[1] = LVP[1] *vec4(p.xyz,1.0);
	

}
