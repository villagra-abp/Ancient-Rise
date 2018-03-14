#include "../headerfiles/TEntidad.h"

PilaMat* TEntidad::pila = new PilaMat();
glm::mat4 TEntidad::mmodelo = pila->desapila();


TEntidad::TEntidad()
{
	//pila = new PilaMat();
	//mmodelo = pila->desapila();
}

TEntidad::~TEntidad(){

}
