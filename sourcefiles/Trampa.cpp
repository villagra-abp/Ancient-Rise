#include "../headerfiles/Trampa.h"


Trampa::Trampa(Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(TRAMPA);
    fachada=fachada->getInstance();
	FObjeto* obObjeto = fachada->addMalla(pos->getPosX(),pos->getPosY(),pos->getPosZ(),"resources/PinchoBase.obj");
	objeto = obObjeto;

	if (objeto)
	{
        Posicion escala(0.3f,0.3f,0.2f);
		fachada->setScala(objeto,&escala);

	}
}

void Trampa::update()
{
	
}


void* Trampa::getNode()
{
    return objeto;
}

Trampa::~Trampa()
{
	fachada->destruirObjeto(objeto);
}

