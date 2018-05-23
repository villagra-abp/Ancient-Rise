#include "../headerfiles/TRecursoAnimacion.h"

//Clase para la gestion de las animaciones. Original.

TRecursoAnimacion::TRecursoAnimacion(double d){
	duracion = d;
}

void TRecursoAnimacion::draw(glm::mat4 mmodelo, TDatosEntidad *datos, int frame){
	mallas[frame]->draw(mmodelo, datos);
}

void TRecursoAnimacion::addMalla(TRecursoMalla* malla){
	mallas.push_back(malla);
//	dMalla = duracion/mallas.size();
}

double TRecursoAnimacion::getDuracion(){
	return duracion;

}  

double TRecursoAnimacion::getDMalla(){
	return (duracion/ mallas.size());
}

void TRecursoAnimacion::setNombre(string name){
	nombre = name;

}
