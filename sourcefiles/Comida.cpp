#include "../headerfiles/Comida.h"



Comida::Comida(Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(COMIDA);
	Fachada* fachada=fachada->getInstance();
	//objeto = fachada->addSphere(pos->getPosX(),pos->getPosY(),pos->getPosZ(),false);
	objeto = fachada->addMalla(pos->getPosX(),pos->getPosY(),pos->getPosZ(), "resources/manzana.obj");
    //posicion = &pos;
    //std::cout<<pos.getPosX()<<endl;
	if (objeto)
	{
        
		//driver = fachada->getDriver();
		//objeto ->setPosition(core::vector3df(pos.getPosX(),pos.getPosY(),pos.getPosZ()));
        Posicion escala(1.25f,1.25f,1.25f);
		fachada->setScala(objeto,&escala);
		//objeto ->setMaterialFlag(video::EMF_LIGHTING, false);
		//objeto ->setMaterialTexture(0,driver->getTexture("resources/pinchos.jpeg"));
        //fachada->setMaterial(objeto,"resources/elon.jpeg");

	}

}


void* Comida::getNode()
{
    return objeto;
}

