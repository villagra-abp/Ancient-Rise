#include "../headerfiles/EnemigoAvanzado.h"


EnemigoAvanzado::EnemigoAvanzado(IrrlichtDevice *dev, ISceneManager *smgr, vector<Posicion*> pos, float xlength, float pendValue, int t, const Entorno* e):Enemigo(dev, smgr, pos, xlength, pendValue, e)
{

    //ESTABLECEMOS LAS ESTADISTICAS ENEMIGO AVANZADO

    this->setEnergia(ENERGIA_MAX);
    this->setHambre(100.f);
    this->setSalud(100.f);
    this->setSed(100.f);
    this->setVelocidad(VELOCIDAD_NORMAL);

    tipo = t;

    //black = b;                                             // Guardamos la blackboard 

    /* CREAMOS EL ARBOL DE COMPORTAMIENTO DE EL ENEMIGO BASICO PASANDOLE LA BLACKBOARD */

    //comportamiento = new BehaviorTree(1, b);              
    

     /* Velocidad a la que bajan las estadisticas del enemigo */
    this->setVelHambre(-0.2);
    this->setVelSed(-0.4);

}

void EnemigoAvanzado::comprobarEnergia()
{
	if(VELOCIDAD_ENEMIGO >VELOCIDAD_NORMAL)  // Si su velcidad es mayor que la velocidad normal de moviemiento, empieza a bajar la energia
    {
        if(energia >0)
        {
            energia+= -10.f * frameDeltaTime;
        }
    }
    else{                       // Si no la supera, entonces la energia se recupera hasta su maximo
            if(energia<=ENERGIA_MAX)
            {
              energia += 15.f * frameDeltaTime;
            }
    }
}

/**
FUNCION PARA crear el objeto dinamico
**/

void EnemigoAvanzado::CreateBox(b2World& world, float X, float Y)
{

    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
    BodyDef.type = b2_dynamicBody;
    Body = world.CreateBody(&BodyDef);
    Shape.SetAsBox((20.f/2)/SCALE, (20.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.2f;
    FixtureDef.friction = 0.35f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);

  
}


EnemigoAvanzado::~EnemigoAvanzado()
{

}


