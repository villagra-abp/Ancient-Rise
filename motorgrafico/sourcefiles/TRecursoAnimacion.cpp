#include "../headerfiles/TRecursoAnimacion.h"




void TRecursoAnimacion::draw(glm::mat4 mmodelo, TDatosEntidad *datos, int frame){
	mallas[frame]->draw(mmodelo, datos);
}

void addMalla(TRecursoMalla* malla){
	mallas.push_back(malla);
}

float TRecursoAnimacion::getDuracion(){
	return duracion;

}

void TRecursoAnimacion::setNombre(string name){
	nombre = name;

}
