#version 400
in vec2 uv;
out vec4 color;
uniform sampler2D myTextureSampler;
void main(){
	color = texture2D(myTextureSampler,uv);
	//color = vec4(1,1,0,1);
}