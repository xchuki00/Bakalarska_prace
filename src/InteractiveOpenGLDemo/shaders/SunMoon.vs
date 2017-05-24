#version 400
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;
out vec2 uv;
uniform mat4 MV;
void main(){
	gl_Position =  MV * vec4(vertexPosition_modelspace,1);
	uv=vertexUV;
}