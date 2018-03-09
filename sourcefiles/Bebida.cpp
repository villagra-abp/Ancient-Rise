#include "../headerfiles/Bebida.h"



Bebida::Bebida(IrrlichtDevice *dev, ISceneManager* smgr, Posicion pos):Objeto()
{
	GameObject::setTipo(BEBIDA);
	Fachada* fachada=fachada->getInstance();
	objeto = fachada->addCube(pos.getPosX(),pos.getPosY(),pos.getPosZ(),false);
    posicion = &pos;
    //std::cout<<pos.getPosX()<<endl;
	if (objeto)
	{
        
        Posicion escala(0.5f,1.5f,0.5f);
		fachada->setScala(objeto,&escala);
	
        fachada->setMaterial(objeto,"resources/pocion.png");

	}

	
}



void* Bebida::getNode()
{
    return objeto;
}

