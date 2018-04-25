#include "../headerfiles/Fuente.h"


/**
CONSTRUCTOR DE OBJETO para inicializar los valores comunes de todos los objetos consumibles
**/
Fuente::Fuente(Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(FUENTE);
	Fachada* fachada=fachada->getInstance();
	FObjeto* obObeto = fachada->addMalla(pos->getPosX()-10,pos->getPosY(),pos->getPosZ(),"resources/Pozo.obj");
    objeto = obObeto;
    //posicion = &pos;
    //std::cout<<pos->getPosX()<<endl;
	if (objeto)
	{
        
        Posicion escala(0.2f,0.2f,0.2f);
		fachada->setScala(objeto,&escala);
		fachada->rotObj(obObeto, 0, 1, 0, 90);
		fachada->movObj(obObeto, 0, -2, 0);
		
        //fachada->setMaterial(objeto,"resources/gota.jpg");

	}

}
