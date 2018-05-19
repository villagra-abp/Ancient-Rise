#include "../headerfiles/PantallaCarga.h"

PantallaCarga::PantallaCarga(Posicion* pos): cargaLevel1(nullptr)
{
	
	Fachada* fachada=fachada->getInstance();

    cargaLevel1 = fachada->addMalla(pos->getPosX()-1,pos->getPosY()*3,pos->getPosZ(), "resources/PantallaCarga/level1.obj");
 
    
    
	if (cargaLevel1)
	{
        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(cargaLevel1,&escala);
        fachada->rotObj(cargaLevel1,1,0,0, 1.5f);
        
	}

    estado = 4;

}

int PantallaCarga::getEstado()
{
    return estado;
}
void PantallaCarga::update(int n)
{
  
}

