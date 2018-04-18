#version 330 core

#define AMBIENT 0.1
#define PI 3.1415926535897

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct PointLight{
	vec3 position;

	float linear;
	float quadratic;

	vec3 color;
};
#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct DirLight{
	vec3 direction;

	vec3 color;
};
uniform DirLight dirLight;
  
 struct FlashLight{
 	vec3 position;
 	vec3 direction;
 	vec3 color;

 	float linear;
 	float quadratic;
 	float cutOff;
 	float extCutOff;
 };
 uniform FlashLight flashLight;


in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 camPos;
uniform Material material;
uniform sampler2D diffTexture;
uniform sampler2D specTexture;

//funciones
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcFlashLight(FlashLight light, vec3 normal, vec3 viewDir, vec3 fragPos);

void main(){

	

		vec3 norm = normalize(Normal);
//		vec3 viewDir = normalize(camPos - FragPos);
		vec3 viewDir = normalize(-FragPos);

		vec3 ambient = vec3(1,1,1) * vec3(texture(diffTexture, TexCoords)) * material.ambient * AMBIENT;
		vec3 result = ambient;
//		vec3 result = vec3(0,0,0);

		result += CalcDirLight(dirLight,norm, viewDir);

		for(int i = 0; i< NR_POINT_LIGHTS; i++)
			result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

		result += CalcFlashLight(flashLight, norm, viewDir, FragPos);

		FragColor = vec4(result, 1.0);


}

vec3 CalcFlashLight(FlashLight light, vec3 normal, vec3 viewDir, vec3 fragPos){

	vec3 lightDir = normalize(light.position - FragPos);

	float diff = max(dot(normal,lightDir), 0.0);
	vec3 diffuse = light.color * diff * vec3(texture(diffTexture, TexCoords)) * material.diffuse;

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular  = light.color * spec * vec3(texture(specTexture, TexCoords)) * material.specular;

	//spotlight (extremo suaves)
	float theta = dot(lightDir, normalize(light.direction));
	light.cutOff = cos(light.cutOff * (PI / 180));
	light.extCutOff = cos(light.extCutOff * (PI/180));
	float epsilon = (light.extCutOff - light.cutOff);
	float intensity = clamp((light.extCutOff - theta) / epsilon, 0.0, 1.0);
//	float intensity = pow(theta, 10.0f);
	diffuse *= intensity;
	specular *= intensity;

	//atenuacion
	float distance = length(light.position - FragPos);
	float attenuation = 5.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));

	diffuse *= attenuation;
	specular *= attenuation;

	return(diffuse + specular);
//	return(specular);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 diffuse = light.color * diff * vec3(texture(diffTexture, TexCoords)) * material.diffuse;
	vec3 specular = light.color * spec * vec3(texture(specTexture, TexCoords)) * material.specular;

	return(diffuse + specular);
//	return(ambient);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	
	vec3 lightDir = normalize(light.position - fragPos);

	//difusa
	float diff = max(dot(normal, lightDir), 0.0);
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
//	float spec = max(dot(reflectDir, viewDir), 0.0);
	//atenuacion
	float distance = length(light.position - fragPos);
	float attenuation = 5.0 /  (1.0f + light.linear * distance + light.quadratic * (distance * distance));


	//combinacion de resultados
	vec3 diffuse = light.color  * vec3(texture(diffTexture, TexCoords)) * material.diffuse * diff;
	vec3 specular = light.color  * spec * vec3(texture(specTexture, TexCoords)) * material.specular ;

	diffuse *= attenuation;
	specular *= attenuation;

	return(diffuse + specular);
//	return (specular);
}

