#include "../headerfiles/Hud.h"

Hud::Hud(Posicion* pos)
{
	
	Fachada* fachada=fachada->getInstance();

    hud1 = fachada->addMalla(pos->getPosX()-5,pos->getPosY()-7,pos->getPosZ(), "resources/Hud/cajitaobj.obj");
    hud2 = fachada->addMalla(pos->getPosX()+6,pos->getPosY()-7,pos->getPosZ(), "resources/Hud/cajitaobj.obj");
    hud3 = fachada->addMalla(pos->getPosX()+5.2,pos->getPosY()+9.05,pos->getPosZ(), "resources/Hud/energia.obj");
    hud4 = fachada->addMalla(pos->getPosX()-2.28,pos->getPosY()+9.05,pos->getPosZ(), "resources/Hud/vida.obj");
    hud5 = fachada->addMalla(pos->getPosX()-3,pos->getPosY()+9.5,pos->getPosZ(), "resources/Hud/vida0.obj");
    hud6 = fachada->addMalla(pos->getPosX()+4.4,pos->getPosY()+9.5,pos->getPosZ(), "resources/Hud/energiaMarco.obj");
    
	if (hud1)
	{
        Posicion escala(2.f,2.f,0.01f);
		fachada->setScala(hud1,&escala);
        fachada->rotObj(hud1,1,0,0, 1.5f);
        
	}
	if (hud2)
	{
        Posicion escala(2.f,2.f,0.01f);
		fachada->setScala(hud2,&escala);
        fachada->rotObj(hud2,1,0,0, 1.5f);
        
	}
	if (hud3)
	{
        //Posicion escala(2.f,2.f,0.f);
		//fachada->setScala(hud3,&escala);
        fachada->rotObj(hud3,1,0,0, 1.5f);
        
	}
	if (hud4)
	{
        //Posicion escala(2.f,2.f,0.f);
		//fachada->setScala(hud4,&escala);
        fachada->rotObj(hud4,1,0,0, 1.5f);
        
	}
	if (hud5)
	{
        Posicion escala(.11f,.12f,0.001f);
		fachada->setScala(hud5,&escala);
        fachada->rotObj(hud5,1,0,0, 1.5f);
        
	}
	if (hud6)
	{
        Posicion escala(.1f,.12f,0.001f);
		fachada->setScala(hud6,&escala);
        fachada->rotObj(hud6,1,0,0, 1.5f);
        
	}

}

void Hud::update(float vida,float energia){
    Fachada* fachada=fachada->getInstance();
    
    Posicion escalaEnergy(energia/2050,.088f,0.001f);
    Posicion escalaLife(vida/3000,.085f,0.001f);
    //fachada->setScala(hud1,&escalaEnergy);
    //fachada->setScala(hud2,&escalaLife);
    fachada->setScala(hud3,&escalaEnergy);
    fachada->setScala(hud4,&escalaLife);
    
}

