#include "../headerfiles/Hud.h"

Hud::Hud(Posicion* pos): hud1(nullptr), hud2(nullptr), hud3(nullptr), hud4(nullptr), hud5(nullptr), hud6(nullptr)
{
	
	Fachada* fachada=fachada->getInstance();

    hud1 = fachada->addMalla(pos->getPosX()-5,pos->getPosY()-70,pos->getPosZ(), "resources/Hud/cajitaobj.obj");//izq abajo
    hud2 = fachada->addMalla(pos->getPosX()+6,pos->getPosY()-70,pos->getPosZ(), "resources/Hud/cajitaobj.obj");//der abajo
    hud3 = fachada->addMalla(pos->getPosX()+5.2,pos->getPosY()+9.44,pos->getPosZ(), "resources/Hud/energia.obj");
    hud4 = fachada->addMalla(pos->getPosX()-2.28,pos->getPosY()+9.42,pos->getPosZ(), "resources/Hud/vida.obj");
    hud5 = fachada->addMalla(pos->getPosX()-3,pos->getPosY()+9.5,pos->getPosZ(), "resources/Hud/vida0.obj");
    hud6 = fachada->addMalla(pos->getPosX()+4.4,pos->getPosY()+9.5,pos->getPosZ(), "resources/Hud/energiaMarco.obj");
    
	
        Posicion escala(2.f,2.f,0.01f);
		fachada->setScala(hud1,&escala);
        fachada->rotObj(hud1,1,0,0, 1.5f);
		fachada->setScala(hud2,&escala);
        fachada->rotObj(hud2,1,0,0, 1.5f);
        fachada->rotObj(hud3,1,0,0, 1.5f);
        fachada->rotObj(hud4,1,0,0, 1.5f);

        Posicion escala2(.11f,.12f,0.001f);
		fachada->setScala(hud5,&escala2);
        fachada->rotObj(hud5,1,0,0, 1.5f);

        Posicion escala3(.1f,.12f,0.001f);
		fachada->setScala(hud6,&escala3);
        fachada->rotObj(hud6,1,0,0, 1.5f);
        

}

void Hud::update(float vida,float energia){
    Fachada* fachada=fachada->getInstance();
    
    Posicion escalaEnergy(energia/2050,.046f,0.001f);
    Posicion escalaLife(vida/3000,.043f,0.001f);
    //fachada->setScala(hud1,&escalaEnergy);
    //fachada->setScala(hud2,&escalaLife);
    fachada->setScala(hud3,&escalaEnergy);
    fachada->setScala(hud4,&escalaLife);
    
}

