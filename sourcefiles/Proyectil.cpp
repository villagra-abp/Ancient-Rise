#include "../headerfiles/Proyectil.h"


Proyectil::Proyectil(Enemigo *e):proyectil(nullptr), enemigoPosition(nullptr), proyectilPos(nullptr), tam(nullptr),fachada(nullptr)
{
	GameObject::setTipo(PROYECTIL);
    fachada=fachada->getInstance();

    // Datos Enemigo
    enemigoPosition = e->getPosition();
	
    if(e->getLastFaceDir()==true) // Mirando derecha
    {
        proyectil = fachada->addSphere(enemigoPosition->getPosX()+10,enemigoPosition->getPosY(),enemigoPosition->getPosZ(),false);
    }
    else // Mirando izquierda
    {
        proyectil = fachada->addSphere(enemigoPosition->getPosX()-10,enemigoPosition->getPosY(),enemigoPosition->getPosZ(),false);
    }

    if (proyectil) /** SI HEMOS CREADO EL CUBO **/
    {  
        //driver = fachada->getDriver();
        //tam = new Posicion(0.5f,0.5f,0.5f);
        //fachada ->setScala(proyectil, tam);
        proyectilPos = fachada->getPosicion(proyectil);

    }

    enTrayectoria = false;
}

void Proyectil::update(Enemigo *e, Blackboard *b)
{   
	if(e->getCombate()==true  && e->getProyectil()!=nullptr)
	{
		disparoProyectil(e,b);
	}
    
}

/*
FUNCION PARA DESTRUIR EL PROYECTIL DEL ENEMIGO
*/
void Proyectil::destroyProyectil()
{	
	//fachada->destruirObjeto(proyectil);
}
/*
FUNCION PARA LANZAR EL PROYECTIL EN LA DIRECCION QUE ESTA MIRANDO EL ENEMIGO
*/
void Proyectil::disparoProyectil(Enemigo *e, Blackboard *b)
{   
    float posX;
	enTrayectoria = true;

	if(e->getLastFaceDir()==true)
    {  
        posX = proyectilPos->getPosX();
        posX += 80.f *b->getTime();
        proyectilPos->setPosX(posX);
        fachada->setPosicion(proyectil, proyectilPos);
        
    }
    else
    {
        posX = proyectilPos->getPosX();
        posX -= 80.f *b->getTime();
        proyectilPos->setPosX(posX);
        fachada->setPosicion(proyectil, proyectilPos);
       
    }
    
}



/* GETTERS Y SETTERS */

bool Proyectil::getEnTrayectoria()
{
	return enTrayectoria;
}


void Proyectil::setEnTrayectoria(bool b)
{
	
	enTrayectoria = b;
}

void Proyectil::setPosition(Posicion* v)
{
	fachada->setPosicion(proyectil,v);
}

Proyectil::~Proyectil()
{
    //proyectil = nullptr;

    //delete tam;
}
