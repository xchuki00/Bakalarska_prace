#version 400
// in for vertex
in vec2 uv;
in vec3 pos;
in vec3 normal;

// out color
out vec4 color;
// struct pro svetelne zdroje
struct DirectionLight{
	vec3 color;
	vec3 Dir;
	float AmbInt;
	float DiffInt;
};
//uniform pro svetelene zdroje/vlastnosti sceny
//uniform DirectionLight dirlight;
uniform float dl[8];
uniform vec3 CameraPos;
// uniform/vlastnosti modelu
uniform sampler2D myTextureSampler;
float specPower = 1;
// funkce
DirectionLight getDirLight(float input[8]){
	DirectionLight dl;
	dl.color = vec3(input[0],input[1],input[2]);
	dl.Dir = vec3(input[3],input[4],input[5]);
	dl.AmbInt = input[6];
	dl.DiffInt = input[7];
	return dl;
}
vec4 DirectionColor(DirectionLight dirlight){
	vec3 DDir=normalize(dirlight.Dir);
	vec3 Dcolor=normalize(dirlight.color);
	float factor = dot(normalize(normal),-DDir); 
	if(factor>0){
		vec3 CameraVertex = normalize(CameraPos - pos);
		vec3 reflectLight = normalize(reflect(DDir,normal));
		float specFactor = dot(CameraVertex,reflectLight);
		if(specFactor>0){
			specFactor = pow(specFactor,specPower);
			return vec4(Dcolor*dirlight.AmbInt,1.0f) + vec4(Dcolor*dirlight.DiffInt*factor,1.f) + vec4(Dcolor*specFactor,1.f); 
		}else{
			return vec4(Dcolor*dirlight.AmbInt,1.0f) + vec4(Dcolor*dirlight.DiffInt*factor,1.f);
		}
	}else{
		return vec4(Dcolor*dirlight.AmbInt,1.0f);;
	}
}

void main(){
	color=texture2D(myTextureSampler,uv)*(DirectionColor(getDirLight(dl)));

}