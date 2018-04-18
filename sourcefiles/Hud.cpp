#include "../headerfiles/Hud.h"

Hud::Hud(Posicion* pos):Objeto(pos)
{
	
	Fachada* fachada=fachada->getInstance();

    hud1 = fachada->addMalla(pos->getPosX()-6,pos->getPosY()-6,pos->getPosZ(), "resources/cajitaobj.obj");
    hud2 = fachada->addMalla(pos->getPosX()+6,pos->getPosY()-6,pos->getPosZ(), "resources/cajitaobj.obj");
    hud3 = fachada->addMalla(pos->getPosX()-6,pos->getPosY()+8,pos->getPosZ(), "resources/cajitaobj.obj");
    hud4 = fachada->addMalla(pos->getPosX()+6,pos->getPosY()+8,pos->getPosZ(), "resources/cajitaobj.obj");
    
    
	if (hud1)
	{
        Posicion escala(2.f,2.f,0.f);
		fachada->setScala(hud1,&escala);
        fachada->rotObj(hud1,1,0,0, 1.5f);
        
	}
	if (hud2)
	{
        Posicion escala(2.f,2.f,0.f);
		fachada->setScala(hud2,&escala);
        fachada->rotObj(hud2,1,0,0, 1.5f);
        
	}
	if (hud3)
	{
        Posicion escala(2.f,2.f,0.f);
		fachada->setScala(hud3,&escala);
        fachada->rotObj(hud3,1,0,0, 1.5f);
        
	}
	if (hud4)
	{
        Posicion escala(2.f,2.f,0.f);
		fachada->setScala(hud4,&escala);
        fachada->rotObj(hud4,1,0,0, 1.5f);
        
	}

}


void* Hud::getNode()
{
    return objeto;
}

