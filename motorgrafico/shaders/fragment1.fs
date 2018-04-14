#version 330 core

#define AMBIENT 0.1

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct PointLight{
	vec3 position;

//	float constant;
//	float linear;
//	float quadratic;

//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
	vec3 color;
};
#define NR_POINT_LIGHTS 3
uniform PointLight pointLights[NR_POINT_LIGHTS];
  


in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

//uniform vec3 luzPos;
uniform vec3 camPos;
//uniform vec4 color;
//uniform float lightIntensity;
uniform Material material;
uniform sampler2D diffTexture;
uniform sampler2D specTexture;

//funciones
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
							
void main(){

//		//ambiente
//		float ambienteInten = 0.1;
//		//vec3 ambient = ambienteInten * vec3(color);
//		vec3 ambient = vec3(texture(diffTexture, TexCoords)) * ambienteInten * vec3(color) * material.ambient;
//
//		//diffuse
//
//		vec3 norm = normalize(Normal);
//		vec3 lightDir = normalize(luzPos - FragPos);  
//
//		float diff = max(dot(norm, lightDir), 0.0);
//		vec3 diffuse = vec3(texture(diffTexture, TexCoords)) *  vec3(color) * (diff * material.diffuse);
//		
//		//specular
//		vec3 viewDir = normalize(camPos - FragPos);
//		vec3 reflectDir = reflect(-lightDir, norm);  
//
//		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//		vec3 specular = vec3(texture(specTexture, TexCoords)) * vec3(color) * (spec * material.specular);
//
//		//result
//		vec3 result = ambient + diffuse + specular;
//		//vec3 result = diffuse;
//		//vec3 result = ambient + specular;
//		//vec3 result = specular;
//		//vec3 result = ambient;
//		FragColor = vec4(result, 1.0f);
//		//FragColor = vec4(0, 1.0f, 1.0f, 1.0f) * 0.25f;
//
//		FragColor = texture(diffTexture, TexCoords);
//		FragColor = vec4(0.5f, 0.5f, 0, 1.0f);


		vec3 norm = normalize(Normal);
		vec3 viewDir = normalize(camPos - FragPos);

		vec3 result = vec3(0,0,0);

		for(int i = 0; i< NR_POINT_LIGHTS; i++)
			result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

		FragColor = vec4(result, 1.0);


}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	
	vec3 lightDir = normalize(light.position - fragPos);

	//difusa
	float diff = max(dot(normal, lightDir), 0.0);
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//atenuacion
//	float distance = length(light.position - fragPos);
//	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


	//combinacion de resultados
	vec3 ambient = light.color * vec3(texture(diffTexture, TexCoords)) * material.ambient * AMBIENT;
	vec3 diffuse = light.color * diff * vec3(texture(diffTexture, TexCoords)) * material.diffuse;
	vec3 specular = light.color * spec * vec3(texture(specTexture, TexCoords)) * material.specular;
//	ambient *= attenuation;
//	diffuse *= attenuation;
//	specular *= attenuation;
	return (ambient + diffuse + specular);
}

