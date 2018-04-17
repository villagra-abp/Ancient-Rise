#include "../headerfiles/TRecursoMalla.h"


void TRecursoMalla::draw(glm::mat4 mmodelo, TDatosEntidad *datos)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(mmodelo, datos);
}  

void TRecursoMalla::addMesh(rMesh mesh){
	meshes.push_back(mesh);
}

void TRecursoMalla::setNombre(string nombre){
	name = nombre;
}

void TRecursoMalla::setDirectorio(string direct){
	directory = direct;
}

string TRecursoMalla::getNombre(){
	return name;
}

string TRecursoMalla::getDirectorio(){
	return directory;
}

