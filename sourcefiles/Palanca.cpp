#include "../headerfiles/Palanca.h"



Palanca::Palanca(Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(PALANCA);
	fachada=fachada->getInstance();

	objeto = fachada->addMalla(pos->getPosX(),pos->getPosY(),pos->getPosZ(), "resources/Palanca/Palanca5.obj");
	if (objeto)
	{
        Posicion escala(0.2f,0.3f,0.3f);
        fachada->rotObj(objeto, 0, 1, 0, -90);
		fachada->setScala(objeto,&escala);

	}

}

void Palanca::update()
{
	

}


void* Palanca::getNode()
{
    return objeto;
}

Palanca::~Palanca()
{
	fachada->destruirObjeto(objeto);
}
