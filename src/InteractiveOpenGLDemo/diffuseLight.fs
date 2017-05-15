#version 400
// in for vertex
in vec2 uv;
in vec3 pos;
in vec3 normal;
in vec4 lightPos[10];
flat in int count;
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
uniform float dl[80];
uniform vec3 CameraPos;

// uniform/vlastnosti modelu

uniform sampler2DShadow ShadowTextureSampler[10];
uniform sampler2D myTextureSampler;
float specPower = 100;
// funkce
DirectionLight getDirLight(float input[80],int i){
	DirectionLight dirl;
	int shift =8 *i;
	dirl.color = vec3(input[shift],input[shift+1],input[shift+2]);
	dirl.Dir = vec3(input[shift+3],input[shift+4],input[shift+5]);
	dirl.AmbInt = input[shift+6];
	dirl.DiffInt = input[shift+7];
	return dirl;
}
float calcShadowFactor(){
    vec4 ProjCoords = lightPos[0];                
	ProjCoords.xyz *= 0.5;          
	ProjCoords.xyz += 0.5;                                                   
                                         
    float Depth = textureProj(ShadowTextureSampler[0], ProjCoords,0.001);                                          
	return Depth;
}
vec4 DirectionColor(DirectionLight dirlight){
	vec3 DDir=normalize(dirlight.Dir);
	vec3 Dcolor=normalize(dirlight.color);
	float factor = dot(normalize(normal),-DDir); 
	vec4 diffuse = vec4(0,0,0,0);
	vec4 spec = vec4(0,0,0,0);
	if(factor>0){
		vec3 CameraVertex = normalize(CameraPos - pos);
		vec3 reflectLight = normalize(reflect(DDir,normal));
		float specFactor = dot(CameraVertex,reflectLight);
		if(specFactor>0){
			specFactor = pow(specFactor,specPower);
			spec=vec4(Dcolor*specFactor,1.f);
		}
		diffuse=vec4(Dcolor * dirlight.DiffInt * factor,1.f);
	}
	vec4 Amb = vec4(Dcolor*dirlight.AmbInt,1.0f);
	float shadowFactor = calcShadowFactor();

	return  (Amb+shadowFactor*(diffuse+spec));
}

void main(){
	vec4 l = vec4(0,0,0,1);
	for(int i=0;i<2;i++	){
		l=l+DirectionColor(getDirLight(dl,i));
		

	}
	if(dl[6]==0){
		l =vec4(1,0,0,1);
	}
	color=texture2D(myTextureSampler,uv)*DirectionColor(getDirLight(dl,0));
	//color= DirectionColor(getDirLight(dl));
}