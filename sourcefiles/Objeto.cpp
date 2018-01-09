#include "../headerfiles/Objeto.h"


/**
CONSTRUCTOR DE OBJETO para inicializar los valores comunes de todos los objetos consumibles
**/
Objeto::Objeto():objeto(nullptr)
{

	recogido = false;
	activado = false;
}

Objeto::~Objeto()
{

}


// getters y setters 

void Objeto::setRecogido(bool r) {	recogido=r;  }   // Actualiza el valor de recogigo a false/true
void Objeto::setActivado(bool a) { activado = a ;}

core::vector3df Objeto::getVector3df(){	return objeto->getPosition();}
bool Objeto::getActivado(){ return activado; }


scene::ISceneNode* Objeto::getObjeto() { return objeto; }


