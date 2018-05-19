#include "../headerfiles/Opciones.h"

Opciones::Opciones(Posicion* pos): opcion1(nullptr), opcion2(nullptr)
{
	
	Fachada* fachada=fachada->getInstance();

    opcion1 = fachada->addMalla(pos->getPosX()+1.5,pos->getPosY()*5,pos->getPosZ(), "resources/Opciones/Opcion1.obj");
    opcion2 = fachada->addMalla(pos->getPosX()+1.5,pos->getPosY()*4,pos->getPosZ(), "resources/Opciones/Opcion2.obj");
   
	if (opcion1)
	{
        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(opcion1,&escala);
        fachada->rotObj(opcion1,1,0,0, 1.5f);
        
	}
	if (opcion2)
	{
        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(opcion2,&escala);
        fachada->rotObj(opcion2,1,0,0, 1.5f);
        
	}
	

}

int Opciones::getEstado()
{
    return estado;
}
bool Opciones::getSound()
{
    return sound;
}
bool Opciones::getShadow()
{
    return shadow;
}
bool Opciones::getJuego()
{
    return juego;
}
void Opciones::setJuego(bool jugando)
{
    juego=jugando;
}
void Opciones::update(int n, bool sonido, bool sombra)
{
    if(n==1){
        if(estado<5){
            estado++;
        }
    }else if(n==-1){
        if(estado>4)
            estado--;
    }
    sound=sonido;
    shadow=sombra;
    //std::cout<<estado<<endl;
}

