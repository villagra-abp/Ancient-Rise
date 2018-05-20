#include "../headerfiles/Opciones.h"

Opciones::Opciones(Posicion* pos)
{
	posicion=pos;
	fachada=fachada->getInstance();

    opcion1 = fachada->addMalla(posicion->getPosX()+1.5,posicion->getPosY()*5,posicion->getPosZ(), "resources/Opciones/Opcion1.obj");
    opcion2 = fachada->addMalla(posicion->getPosX()+1.5,posicion->getPosY()*4,posicion->getPosZ(), "resources/Opciones/Opcion2.obj");
   

        Posicion escala(.1f,.12f,0.1f);
		fachada->setScala(opcion1,&escala);
        fachada->setRotObj(opcion1,1,0,0, 1.5f);

		fachada->setScala(opcion2,&escala);
        fachada->setRotObj(opcion2,1,0,0, 1.5f);
        
	

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
    
    sound=sonido;
    shadow=sombra;
    
    if(!sound){
        fachada->setVolumen(0);
    }
    else
        fachada->setVolumen(0.2f);
    
    
    
    if(n==1){
        if(estado<5){
            estado++;
        }
    }else if(n==-1){
        if(estado>4)
            estado--;
    }
    
    if(estado==5)
    {
        if(!sound&&shadow)
        {
            //std::cout<<estado<<endl;
            fachada->setMalla(opcion1, "resources/Opciones/Opcion3.obj");
            
        }else if(!sound&&!shadow)
        {
            fachada->setMalla(opcion1, "resources/Opciones/Opcion4.obj");
            
        }else
            fachada->setMalla(opcion1, "resources/Opciones/Opcion1.obj");
        
        
    }
    if(estado==4)
    {
        if(sound&&!shadow)
        {
            fachada->setMalla(opcion2, "resources/Opciones/Opcion5.obj");
            
        }else if(!sound&&!shadow)
        {
            fachada->setMalla(opcion2, "resources/Opciones/Opcion6.obj");
        }else
            fachada->setMalla(opcion2, "resources/Opciones/Opcion2.obj");
        
        
        
    }
    //std::cout<<estado<<endl;
    //std::cout<<sound<<endl;
    //std::cout<<shadow<<endl;
}

