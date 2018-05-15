#include "../headerfiles/Comida.h"



Comida::Comida(Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(COMIDA);
	fachada=fachada->getInstance();

	objeto = fachada->addMalla(pos->getPosX(),pos->getPosY(),pos->getPosZ(), "resources/manzana.obj");

	if (objeto)
	{
        Posicion escala(1.25f,1.25f,1.25f);
		fachada->setScala(objeto,&escala);

	}

}

void Comida::update()
{
	if(recogido==true) // Si hemos recogido la comida 
	{
		fachada->destruirObjeto(objeto);
		objeto = nullptr;
	}

}


void* Comida::getNode()
{
    return objeto;
}

Comida::~Comida()
{
	fachada->destruirObjeto(objeto);
}

