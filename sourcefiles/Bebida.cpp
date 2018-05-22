#include "../headerfiles/Bebida.h"

Bebida::Bebida(Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(BEBIDA);

	fachada=fachada->getInstance();
    objeto = fachada->addMalla(pos->getPosX(),pos->getPosY(),pos->getPosZ(), "resources/Bebida/Pocion.obj");

	if (objeto)
	{
        Posicion escala(0.9f,1.7f,0.5f);
		fachada->setScala(objeto,&escala);
	}

}


void Bebida::update()
{
	if(recogido==true) // Si hemos recogido la bebida 
	{
		fachada->destruirObjeto(objeto);
		//delete objeto;
		objeto = nullptr;
	}

}
void* Bebida::getNode()
{
    return objeto;
}

Bebida::~Bebida()
{
	fachada->destruirObjeto(objeto);
}

