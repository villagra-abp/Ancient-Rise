#include "../headerfiles/TRecursoMaterial.h"


TRecursoMaterial::TRecursoMaterial(){

}



TRecursoMaterial::~TRecursoMaterial(){

}



string TRecursoMaterial::getNombre(){
	return nombre;
}

float TRecursoMaterial::getBrillo(){
	return shininess;
}

glm::vec3 TRecursoMaterial::getAmbiente(){
	return ambient;
}

glm::vec3 TRecursoMaterial::getDifusa(){
	return diffuse;
}

glm::vec3 TRecursoMaterial::getEspecular(){
	return specular;
}


void TRecursoMaterial::setNombre(string name){
	//cout<<name<<endl;
	nombre = name;
}


//AQui hay que leer con xml, queda pospuesto y para hacer pruebas introduzco materiales a mano
void TRecursoMaterial::cargarFichero(string nombre){
	if(nombre == "mat_naranja"){
		ambient = glm::vec3(1.0f, 	0.5f, 	0);
		diffuse = glm::vec3(1.0f,	0.5f,	0);
		specular = glm::vec3(1.0f, 1.0f, 1.0f);
		shininess = 32.0f;
	} else if(nombre == "mat_rosa"){
		ambient = glm::vec3(0.073f,	0.056f,	0.056f);
		diffuse = glm::vec3(1.0f,	0.56f,	0.56f);
		specular = glm::vec3(1.0f, 0.7f, 0.7f);
		shininess = 64.0f;
	} else if (nombre == "mat_negro"){
		ambient = glm::vec3(0.01f, 	0.01f, 	0.01f);
		diffuse = glm::vec3(0.1f,	0.1f,	0.1f);
		specular = glm::vec3(1.0f, 1.0f, 1.0f);
		shininess = 8.0f;
	}
		

}