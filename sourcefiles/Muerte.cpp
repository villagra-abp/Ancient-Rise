#include "../headerfiles/Muerte.h"

Muerte::Muerte(Posicion* pos): muerte(nullptr)
{
	
	fachada=fachada->getInstance();


    muerte = fachada->addMalla(pos->getPosX()-1,pos->getPosY(),pos->getPosZ(), "resources/Muerte/muerte_1.obj");
   
    
	if (muerte)
	{
        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(muerte,&escala);
        fachada->rotObj(muerte,1,0,0, 1.5f);
        
	}
	
}

int Muerte::getEstado()
{
    return estado;
}
void Muerte::update(int n)
{
    if(n==1){
        if(estado<2){
            estado++;
        }
    }else{
        if(estado>1)
            estado--;
    }
    if(estado==2)
        fachada->setMalla(muerte, "resources/Muerte/muerte_1.obj");
    if(estado==1)
        fachada->setMalla(muerte, "resources/Muerte/muerte_2.obj");
}

