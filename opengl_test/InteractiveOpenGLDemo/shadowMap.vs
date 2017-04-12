#version 400
layout(location = 0) in vec3 vertexPosition_modelspace;


uniform mat4 MVP;
void main(){

		int id = gl_VertexID%3;
		//gl_Position = vec4(id%2,id/2,0,1);
		gl_Position = MVP*vec4(vertexPosition_modelspace,1.0);	

}