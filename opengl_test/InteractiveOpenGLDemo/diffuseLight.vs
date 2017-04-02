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
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 gBones[200];
void main(){
	if(boneWeight[0]>0){		
		mat4 boneT = gBones[int(boneID[0])] * boneWeight[0];
		boneT     += gBones[int(boneID[1])] * boneWeight[1];
		boneT     += gBones[int(boneID[2])] * boneWeight[2];
		boneT     += gBones[int(boneID[3])] * boneWeight[3];
		mat4 identy;
		identy[0][0]=0.5;identy[0][1]=0.75;identy[0][2]=0;identy[0][3]=1;
		identy[1][0]=0.75;identy[1][1]=0.5;identy[1][2]=0;identy[1][3]=1;
		identy[2][0]=0;identy[2][1]=0;identy[2][2]=0.5;identy[2][3]=1;
		identy[3][0]=0;identy[3][1]=0;identy[3][2]=0;identy[3][3]=1;
		vec4 p=boneT*vec4(vertexPosition_modelspace,1.0);
		pos=(M * p).xyz;
		normal=(M * boneT * vec4(vertexNormal_modelspace,0.0)).xyz;
		gl_Position = MVP*vec4(p.xyz,1.0);
	}else{
		gl_Position = MVP*vec4(vertexPosition_modelspace,1.0);	
		pos=(M * vec4(vertexPosition_modelspace,1.0)).xyz;
		normal=(M * vec4(vertexNormal_modelspace,0.0)).xyz;
	}
	uv=vertexUV;

}