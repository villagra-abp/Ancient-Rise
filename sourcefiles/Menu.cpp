#include "../headerfiles/Menu.h"

Menu::Menu(Posicion* pos):Objeto(pos)
{
	
	Fachada* fachada=fachada->getInstance();

    menu = fachada->addMalla(pos->getPosX(),pos->getPosY(),pos->getPosZ(), "resources/menu_bueno.obj");
    
    
	if (menu)
	{
        Posicion escala(.1f,.1f,0.1f);
		fachada->setScala(menu,&escala);
        fachada->rotObj(menu,1,0,0, 1.5f);
        
	}

}


void* Menu::getNode()
{
    return objeto;
}

