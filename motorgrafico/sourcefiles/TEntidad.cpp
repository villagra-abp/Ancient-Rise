#include "../headerfiles/TEntidad.h"

PilaMat* TEntidad::pila;
glm::mat4 TEntidad::mmodelo;


TEntidad::TEntidad()
{
	pila = new PilaMat();
	mmodelo = pila->desapila();
}

TEntidad::~TEntidad(){

}
