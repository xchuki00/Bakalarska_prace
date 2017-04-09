#version 400
// in for vertex
in vec2 uv;
in vec3 pos;
in vec3 normal;
in vec4 lightPos;
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

uniform sampler2D ShadowTextureSampler;
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
float calcShadowFactor(){
    vec3 ProjCoords = lightPos.xyz / lightPos.w;                                  
    vec2 UVCoords;                                                                          
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;                                                  
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;                                                  
    float z = 0.5 * ProjCoords.z + 0.5;                                                     
    float Depth = texture(ShadowTextureSampler, UVCoords).x;                                          
    if (Depth < z + 0.00001)                                                                 
        return 0.5;                                                                         
    else                                                                                    
       return 1.0;
	//return Depth;   
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
	float shadowFactor = calcShadowFactor();
	if(shadowFactor<=1){
	//	return vec4(shadowFactor,shadowFactor,shadowFactor,1);
	}else{
	//	return vec4(1,0,0,1);
	}
	vec4 Amb = vec4(Dcolor*dirlight.AmbInt,1.0f);
	return Amb+shadowFactor*(diffuse+spec); 

}

void main(){
	color=texture2D(myTextureSampler,uv)*(DirectionColor(getDirLight(dl)));
	//color= DirectionColor(getDirLight(dl));
}