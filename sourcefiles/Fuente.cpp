#include "../headerfiles/Fuente.h"


/**
CONSTRUCTOR DE OBJETO para inicializar los valores comunes de todos los objetos consumibles
**/
Fuente::Fuente(Posicion* pos):Objeto(pos)
{
	GameObject::setTipo(FUENTE);
	fachada=fachada->getInstance();
	FObjeto* obObeto = fachada->addMalla(pos->getPosX(),pos->getPosY()+3,pos->getPosZ(),"resources/Pozo/Pozo.obj");
    objeto = obObeto;
    //posicion = &pos;
    //std::cout<<pos->getPosX()<<endl;
	if (objeto)
	{
        
        Posicion escala(0.2f,0.4f,0.2f);
		fachada->setScala(objeto,&escala);
		fachada->rotObj(obObeto, 0, 1, 0, 90);
		fachada->movObj(obObeto, 0, -2, 0);
		
        //fachada->setMaterial(objeto,"resources/gota.jpg");

	}

}

void Fuente::update()
{
	fachada->destruirObjeto(objeto);
}

Fuente::~Fuente()
{
	fachada->destruirObjeto(objeto);
}

