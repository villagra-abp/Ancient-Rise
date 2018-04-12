#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  


in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 luzPos;
uniform vec3 camPos;
uniform vec4 color;
uniform float lightIntensity;
uniform Material material;

							
void main(){

		//ambiente
		float ambienteInten = 0.1;
		//vec3 ambient = ambienteInten * vec3(color);
		vec3 ambient = ambienteInten* vec3(color) * material.ambient;

		//diffuse

		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(luzPos - FragPos);  

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = vec3(color) * (diff * material.diffuse);
		
		//specular
		vec3 viewDir = normalize(camPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  

		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = vec3(color) * (spec * material.specular);

		//result
		vec3 result = ambient + diffuse + specular;
		//vec3 result = diffuse;
		//vec3 result = ambient + specular;
		//vec3 result = specular;
		//vec3 result = ambient;
		FragColor = vec4(result, 1.0f);
		//FragColor = vec4(0, 1.0f, 1.0f, 1.0f) * 0.25f;

}