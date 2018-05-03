#include "../headerfiles/Pausa.h"

Pausa::Pausa(Posicion* pos):Objeto(pos)
{
	
	Fachada* fachada=fachada->getInstance();

    pausa = fachada->addMalla(pos->getPosX()+1,pos->getPosY()*3+4.8,pos->getPosZ(), "resources/Pausa/Menu1.obj");
    pausa2 = fachada->addMalla(pos->getPosX()+1,pos->getPosY()*2+2.8,pos->getPosZ(), "resources/Pausa/Menu2.obj");
    pausa3 = fachada->addMalla(pos->getPosX()+1,pos->getPosY(),pos->getPosZ(), "resources/Pausa/Menu3.obj");
	if (pausa)
	{
        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(pausa,&escala);
        fachada->rotObj(pausa,1,0,0, 1.5f);
        
	}
	if (pausa2)
	{
        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(pausa2,&escala);
        fachada->rotObj(pausa2,1,0,0, 1.5f);
        
	}
	if (pausa3)
	{
        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(pausa3,&escala);
        fachada->rotObj(pausa3,1,0,0, 1.5f);
        
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

