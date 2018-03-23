#include "../headerfiles/Trampa.h"


Trampa::Trampa(IrrlichtDevice *dev, ISceneManager* smgr, Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(TRAMPA);
    Fachada* fachada=fachada->getInstance();
	objeto = fachada->addCube(pos->getPosX(),pos->getPosY(),pos->getPosZ(),false);
    //posicion = &pos;
    std::cout<<this->getPosition()->getPosX()<<endl;
	if (objeto)
	{
        
		//driver = fachada->getDriver();
		//objeto ->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
        Posicion escala(2.5f,1.5f,2.5f);
		fachada->setScala(objeto,&escala);
		//objeto ->setMaterialFlag(video::EMF_LIGHTING, false);
		//objeto ->setMaterialTexture(0,driver->getTexture("resources/pinchos.jpeg"));
        //fachada->setMaterial(objeto,"resources/pinchos.jpeg");

	}
}



void* Trampa::getNode()
{
    return objeto;
}

