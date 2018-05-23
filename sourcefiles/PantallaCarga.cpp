#include "../headerfiles/PantallaCarga.h"

PantallaCarga::PantallaCarga(Posicion* pos): cargaLevel1(nullptr), cargaLevel2(nullptr), cargaLevel3(nullptr), fachada(nullptr), p(nullptr)
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
    p = pos;
    cargadoLvl2 = false;
    cargadoLvl3 = false;

}

int PantallaCarga::getEstado()
{
    return estado;
}

void PantallaCarga::setPantallaCarga(int p)
{
	pantallaCarga = p;
}

int PantallaCarga::getPantallaCarga()
{
	return pantallaCarga;
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
			/* Eliminamos la pantalla anterior */
			fachada->destruirObjeto(cargaLevel1);
			cargaLevel1 = nullptr;

			if (cargaLevel2 && cargadoLvl2==false)
			{
		        Posicion escala(0.17f,.295f,0.1f);
				fachada->setScala(cargaLevel2,&escala);
		        fachada->rotObj(cargaLevel2,1,0,0, 1.5f);
		        cargadoLvl2 = true;
			}

			/* Cargamos la nueva pantalla de carga */
			fachada->setMalla(cargaLevel2, "resources/PantallaCarga/level2.obj");

			break;
		}

		case 3: // Pantallo Carga level 3
		{
			/* Eliminamos la pantalla anterior */
			fachada->destruirObjeto(cargaLevel2);
			cargaLevel2 = nullptr;

			if (cargaLevel3 && cargadoLvl3==false)
			{
		        Posicion escala(0.16f,.24f,0.1f);
				fachada->setScala(cargaLevel3,&escala);
		        fachada->rotObj(cargaLevel3,1,0,0, 1.5f);
		        cargadoLvl3 = true; // Para que no se haga mas de una vez
		        
			}

			/* Cargamos la nueva pantalla de carga */
			fachada->setMalla(cargaLevel3, "resources/PantallaCarga/level3.obj");
			
			break;
		}

	}
  
}

