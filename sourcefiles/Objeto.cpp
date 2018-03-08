#include "../headerfiles/Objeto.h"


/**
CONSTRUCTOR DE OBJETO para inicializar los valores comunes de todos los objetos consumibles
**/
Objeto::Objeto():objeto(nullptr)
{

	recogido = false;
	activado = false;
	activando = false;
}

Objeto::~Objeto()
{

}


// getters y setters 

void Objeto::setRecogido(bool r) {	recogido=r;  }   // Actualiza el valor de recogigo a false/true
void Objeto::setActivado(bool a) { activado = a ;}
void Objeto::setActivando(bool a) { activando = a; }

Posicion* Objeto::getVector3df(){return posicion;}
bool Objeto::getActivado(){ return activado; }
bool Objeto::getActivando(){ return activando; }


scene::ISceneNode* Objeto::getObjeto() { return objeto; }


