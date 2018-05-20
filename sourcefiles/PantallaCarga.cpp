#include "../headerfiles/PantallaCarga.h"

PantallaCarga::PantallaCarga(Posicion* pos): cargaLevel1(nullptr)
{
	
	Fachada* fachada=fachada->getInstance();

    cargaLevel1 = fachada->addMalla(pos->getPosX()*1.5,pos->getPosY()*5,pos->getPosZ(), "resources/PantallaCarga/level1.obj");
 
    
    
	if (cargaLevel1)
	{
        Posicion escala(0.13f,.24f,0.1f);
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

