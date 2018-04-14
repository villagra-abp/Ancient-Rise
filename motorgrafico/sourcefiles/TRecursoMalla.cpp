#include "../headerfiles/TRecursoMalla.h"


void TRecursoMalla::draw(glm::mat4 mmodelo, glm::mat4 view, glm::mat4 projection, vector<float> intensidad, vector<glm::vec4> color, 
		vector<glm::vec3> luzPosicion, glm::vec3 camPosicion)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(mmodelo, view, projection, intensidad, color, luzPosicion, camPosicion);
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

string TRecursoMalla::getPath(string name){
	
	string path;
	/*
	switch (name){
		case "caja":
			path = mCaja;
			break;
		case "ironMan":
			path = mIronMan;
			break;
		default:
			path = mCaja;
			break;
	}
*/
	if (name == "caja")
		path = mCaja;
	else if(name == "ironMan")
		path = mIronMan;
	else
		path = mCaja;

	return path;
}

