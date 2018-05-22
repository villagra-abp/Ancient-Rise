#include "../headerfiles/Puerta.h"



Puerta::Puerta(Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(PUERTA);
	fachada=fachada->getInstance();

	objeto = fachada->addMalla(pos->getPosX(),pos->getPosY(),pos->getPosZ(), "resources/Puerta/puerta.obj");
	if (objeto)
	{
        Posicion escala(0.5f,1.f,1.f);
		fachada->setScala(objeto,&escala);

	}

}

void Puerta::update()
{
	

}


void* Puerta::getNode()
{
    return objeto;
}

Puerta::~Puerta()
{
	fachada->destruirObjeto(objeto);
}