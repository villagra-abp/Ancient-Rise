#include "../headerfiles/PantallaCarga.h"

PantallaCarga::PantallaCarga(Posicion* pos): cargaLevel1(nullptr), cargaLevel2(nullptr), cargaLevel3(nullptr), fachada(nullptr)
{
	
	fachada=fachada->getInstance();

    cargaLevel1 = fachada->addMalla(pos->getPosX()*1.5,pos->getPosY()*5,pos->getPosZ(), "resources/PantallaCarga/level1.obj");
    cargaLevel2 = fachada->addMalla(pos->getPosX()*1.5,pos->getPosY()*5,pos->getPosZ(), "resources/PantallaCarga/level2.obj");
    cargaLevel3 = fachada->addMalla(pos->getPosX()*1.5,pos->getPosY()*5,pos->getPosZ(), "resources/PantallaCarga/level3.obj");
 
    
    
	if (cargaLevel1)
	{
        Posicion escala(0.13f,.24f,0.1f);
		fachada->setScala(cargaLevel1,&escala);
        fachada->rotObj(cargaLevel1,1,0,0, 1.5f);
        
	}

    estado = 4;
    pantallaCarga = 1;

}

int PantallaCarga::getEstado()
{
    return estado;
}

void PantallaCarga::setPantallaCarga(int p)
{
	pantallaCarga = p;
}
void PantallaCarga::update()
{
	switch(pantallaCarga)
	{

		case 1: // Pantallo Carga level 1
		{
			fachada->setMalla(cargaLevel1, "resources/PantallaCarga/level1.obj");
			break;
		}

		case 2: // Pantallo Carga level 2
		{
			fachada->setMalla(cargaLevel2, "resources/PantallaCarga/level2.obj");
			break;
		}

		case 3: // Pantallo Carga level 3
		{
			fachada->setMalla(cargaLevel3, "resources/PantallaCarga/level3.obj");
			break;
		}

	}
  
}

