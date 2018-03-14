#include "../headerfiles/EnemigoBasico.h"
#include "../headerfiles/BehaviorTree.h"


/**
CONSTRUCTOR DE ENEMIGO BASICO
Parametros : Irrlicht objetos, vector con posiciones para la patrulla, entero para indicar si melee/distancia, Blackboard con datos necesarios para el arbol
**/
EnemigoBasico::EnemigoBasico(IrrlichtDevice *dev, ISceneManager *smgr, vector<Posicion*> pos, float xlength, float pendValue, int t, const Entorno* e, Blackboard *b, b2World& world):Enemigo(dev, smgr, pos, xlength, pendValue, e), black(nullptr)
{

    //ESTABLECEMOS LAS ESTADISTICAS ENEMIGO BASICO

    this->setEnergia(ENERGIA_MAX);
    this->setHambre(100.f);
    this->setSalud(100.f);
    this->setSed(100.f);
    this->setVelocidad(VELOCIDAD_NORMAL);

    tipo = t;                                             // Tipo de combate que usa (Distancia o Cuerpo a Cuerpo)
    claseEnemigo = 1;                                     // EnemigoBasico


    black = b;                                             // Guardamos la blackboard 

    /* CREAMOS EL ARBOL DE COMPORTAMIENTO DE EL ENEMIGO BASICO PASANDOLE LA BLACKBOARD */

    comportamiento = new BehaviorTree(1, b);              
    

     /* Velocidad a la que bajan las estadisticas del enemigo */
    this->setVelHambre(-0.3);
    this->setVelSed(-0.5);


    this->CreateBox(world, posPatrulla[0]->getPosX()*30, posPatrulla[0]->getPosY()*30);

    velocidad2d = Body->GetLinearVelocity();

    velocidad2d.x = 25.f;


}

void EnemigoBasico::Update(Posicion* prota)
{
	this->update(prota);                                     // Llamamos tambien al update de la clase general del enemigo y actualizamos los valores de sed - hambre del mismo
  this->comprobarEnergia();

  comportamiento->update(this);                           // Empezamos a ejecutar el arbol de comportamiento del enemigo

  EnemigoPosition->setPosX(Body->GetPosition().x);        // Establecemos su velocidad con el body
  EnemigoPosition->setPosY(Body->GetPosition().y);

  
    fachada->setPosicion(enemigo,EnemigoPosition);
}


/*
FUNCION PARA COMPROBAR LA VELOCIDAD DEL ENEMIGOBASICO Y REDUCIR/AUMENTAR LA ENERGIA
*/
void EnemigoBasico::comprobarEnergia()
{
    if(VELOCIDAD_ENEMIGO >VELOCIDAD_NORMAL)  // Si su velcidad es mayor que la velocidad normal de moviemiento, empieza a bajar la energia
    {
        if(energia >0)
        {
            energia+= -20.f * frameDeltaTime;
        }
    }
    else{                       // Si no la supera, entonces la energia se recupera hasta su maximo
            if(energia<=ENERGIA_MAX)
            {
              energia += 10.f * frameDeltaTime;
            }
    }

}


/**
FUNCION PARA crear el objeto dinamico
**/

void EnemigoBasico::CreateBox(b2World& world, float X, float Y)
{

    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
    BodyDef.type = b2_dynamicBody;
    Body = world.CreateBody(&BodyDef);
    Shape.SetAsBox((20.f/2)/SCALE, (20.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.2f;
    FixtureDef.friction = 0.35f;
    FixtureDef.shape = &Shape;
    FixtureDef.filter.groupIndex = GROUP_ENEMIGOS;
    Body->CreateFixture(&FixtureDef);

  
}


EnemigoBasico::~EnemigoBasico()
{
    //dtor
  comportamiento = nullptr;
  black = nullptr;
  //delete comportamiento;
}
