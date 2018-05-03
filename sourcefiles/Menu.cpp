#include "../headerfiles/Menu.h"

Menu::Menu(Posicion* pos):Objeto(pos)
{
	
	Fachada* fachada=fachada->getInstance();

    menu = fachada->addMalla(pos->getPosX()+1,pos->getPosY()*3+4.8,pos->getPosZ(), "resources/Menu/Menu1.obj");
    menu2 = fachada->addMalla(pos->getPosX()+1,pos->getPosY()*2+2.8,pos->getPosZ(), "resources/Menu/Menu2.obj");
    menu3 = fachada->addMalla(pos->getPosX()+1,pos->getPosY()+1,pos->getPosZ(), "resources/Menu/Menu3.obj");
    
    
	if (menu)
	{
        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(menu,&escala);
        fachada->rotObj(menu,1,0,0, 1.5f);
        
	}
	if (menu2)
	{
        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(menu2,&escala);
        fachada->rotObj(menu2,1,0,0, 1.5f);
        
	}
	if (menu3)
	{
        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(menu3,&escala);
        fachada->rotObj(menu3,1,0,0, 1.5f);
        
	}

}


void* Menu::getNode()
{
    return objeto;
}
int Menu::getEstado()
{
    return estado;
}
void Menu::update(int n)
{
    if(n==1){
        if(estado<3){
            estado++;
        }
    }else{
        if(estado>1)
            estado--;
    }
}

