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
out vec4 lightPos;
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 LVP;
uniform mat4 gBones[50];
void main(){
	mat4 boneT ;
		boneT[0][0]=1;boneT[0][1]=0;boneT[0][2]=0;boneT[0][3]=0;
		boneT[1][0]=0;boneT[1][1]=1;boneT[1][2]=0;boneT[1][3]=0;
		boneT[2][0]=0;boneT[2][1]=0;boneT[2][2]=1;boneT[2][3]=0;
		boneT[3][0]=0;boneT[3][1]=0;boneT[3][2]=0;boneT[3][3]=1;
	
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
	lightPos = LVP *vec4(p.xyz,1.0);
	

}
