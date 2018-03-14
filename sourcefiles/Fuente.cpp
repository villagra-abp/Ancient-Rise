#include "../headerfiles/Fuente.h"


/**
CONSTRUCTOR DE OBJETO para inicializar los valores comunes de todos los objetos consumibles
**/
Fuente::Fuente(IrrlichtDevice *dev, ISceneManager* smgr, Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(FUENTE);
	Fachada* fachada=fachada->getInstance();
	objeto = fachada->addCube(pos->getPosX(),pos->getPosY(),pos->getPosZ(),false);
    //posicion = &pos;
    //std::cout<<pos.getPosX()<<endl;
	if (objeto)
	{
        
        Posicion escala(2.5f,1.f,1.f);
		fachada->setScala(objeto,&escala);
		
        fachada->setMaterial(objeto,"resources/gota.jpg");

	}

}
