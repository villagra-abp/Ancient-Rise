#include "../headerfiles/Pausa.h"

Pausa::Pausa(Posicion* pos):Objeto(pos)
{
	
	Fachada* fachada=fachada->getInstance();

    pausa = fachada->addMalla(pos->getPosX(),pos->getPosY(),pos->getPosZ(), "resources/continue.obj");
    
    
	if (pausa)
	{
        Posicion escala(.1f,.1f,0.1f);
		fachada->setScala(pausa,&escala);
        fachada->rotObj(pausa,1,0,0, 1.5f);
        
	}

}


void* Pausa::getNode()
{
    return objeto;
}
int Pausa::getEstado()
{
    return estado;
}
void Pausa::update(int n)
{
    if(n==1){
        if(estado<3){
            estado++;
        }
    }else{
        if(estado>1)
            estado--;
    }
    //std::cout<<estado<<endl;
}

