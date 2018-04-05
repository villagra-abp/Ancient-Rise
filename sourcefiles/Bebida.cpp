#include "../headerfiles/Bebida.h"

Bebida::Bebida(Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(BEBIDA);
	Fachada* fachada=fachada->getInstance();
	//objeto = fachada->addCube(pos->getPosX(),pos->getPosY(),pos->getPosZ(),false);
    objeto = fachada->addMalla(pos->getPosX(),pos->getPosY(),pos->getPosZ(), "resources/Pocion.obj");
    //posicion = &pos;
    //std::cout<<pos.getPosX()<<endl;
	if (objeto)
	{
        
        Posicion escala(1.0f,1.0f,0.5f);
		fachada->setScala(objeto,&escala);
	
        //fachada->setMaterial(objeto,"resources/pocion.png");

	}

}


void* Bebida::getNode()
{
    return objeto;
}

