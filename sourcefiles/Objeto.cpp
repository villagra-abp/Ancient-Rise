#include "../headerfiles/Objeto.h"


/**
CONSTRUCTOR DE OBJETO para inicializar los valores comunes de todos los objetos consumibles
**/
Objeto::Objeto():objeto(nullptr)
{

	recogido = false;
}

Objeto::~Objeto()
{

}


// getters y setters 

void Objeto::setRecogido(bool r) {	recogido=r;  }   // Actualiza el valor de recogigo a false/true



scene::ISceneNode* Objeto::getObjeto() { return objeto; }


