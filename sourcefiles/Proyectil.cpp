#include "../headerfiles/Proyectil.h"


Proyectil::Proyectil(IrrlichtDevice* device, ISceneManager* smgr, Enemigo *e):driver(nullptr),proyectil(nullptr), enemigoPosition(nullptr), proyectilPos(nullptr), tam(nullptr)
{
	GameObject::setTipo(PROYECTIL);
    Fachada* fachada=fachada->getInstance();

    // Datos Enemigo
    enemigoPosition = e->getPosition();
	
    if(e->getLastFaceDir()==true) // Mirando derecha
    {
        proyectil = fachada->addCube(enemigoPosition->getPosX()+10,enemigoPosition->getPosY(),enemigoPosition->getPosZ(),false);
    }
    else // Mirando izquierda
    {
        proyectil = fachada->addCube(enemigoPosition->getPosX()-10,enemigoPosition->getPosY(),enemigoPosition->getPosZ(),false);
    }

    if (proyectil) /** SI HEMOS CREADO EL CUBO **/
    {  
        driver = fachada->getDriver();
        tam = new Posicion(0.5f,0.5f,0.5f);
        fachada ->setScala(proyectil, tam);
        proyectilPos = fachada->getPosicion(proyectil);

    }

    enTrayectoria = false;
}

void Proyectil::update(Enemigo *e, Blackboard *b)
{   /*
	if(e->getCombate()==true  && e->getProyectil()!=nullptr)
	{
		disparoProyectil(e,b);
	}
    */
}

/*
FUNCION PARA DESTRUIR EL PROYECTIL DEL ENEMIGO
*/
void Proyectil::destroyProyectil()
{	
	//proyectil->remove();
}

/*
FUNCION PARA LANZAR EL PROYECTIL EN LA DIRECCION QUE ESTA MIRANDO EL ENEMIGO
*/
void Proyectil::disparoProyectil(Enemigo *e, Blackboard *b)
{   /*
	enTrayectoria = true;
	if(e->getLastFaceDir()==true)
    {  
        proyectilPos.X += 80.f *b->getTime();
        proyectil->setPosition(proyectilPos);
       
        
    }
    else
    {
        proyectilPos.X -= 80.f *b->getTime();
        proyectil->setPosition(proyectilPos);
       
    }
    */
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
	proyectilPos = v;
}

Proyectil::~Proyectil()
{
    //proyectil = nullptr;
    driver = nullptr; 

    delete tam;
}