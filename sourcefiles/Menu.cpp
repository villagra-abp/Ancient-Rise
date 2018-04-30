#include "../headerfiles/Menu.h"

Menu::Menu(Posicion* pos):Objeto(pos)
{
	
	Fachada* fachada=fachada->getInstance();

    menu = fachada->addMalla(pos->getPosX()+1,pos->getPosY()+1,pos->getPosZ(), "resources/Menu/Carajo.obj");
    
    
	if (menu)
	{
        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(menu,&escala);
        fachada->rotObj(menu,1,0,0, 1.5f);
        
	}

}


void* Menu::getNode()
{
    return objeto;
}

