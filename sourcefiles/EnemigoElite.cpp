#include "../headerfiles/EnemigoElite.h"


EnemigoElite::EnemigoElite(vector<Posicion*> pos, float xlength, float pendValue, int t, const Entorno* e, Blackboard *b, b2World& world):Enemigo( pos, xlength, pendValue, e, b)
{

    //ESTABLECEMOS LAS ESTADISTICAS ENEMIGO AVANZADO

    setEnergia(ENERGIA_MAX);
    salud = 100.f;
    setSed(100.f);
    setVelocidad(VELOCIDAD_NORMAL);

    tipo = t;                                             // Tipo de combate que usa (Distancia o Cuerpo a Cuerpo)
    claseEnemigo = 3;                                     // EnemigoElite

    fachada->setMaterialFlag(enemigo, true);


    /* CREAMOS EL ARBOL DE COMPORTAMIENTO DEL ENEMIGO ELITE PASANDOLE LA BLACKBOARD */

    comportamiento = new BehaviorTree(2, b);  

     /* Velocidad a la que bajan las estadisticas del enemigo */
    setVelSed(-0.2);

    /* BOX2D */
    /*nodoPosition = patrulla[0]->getPosition();
    CreateBox(world, nodoPosition->getPosX()*30, nodoPosition->getPosY()*30);
*/
    CreateBox(world, patrulla[0]->getPosX()*30, patrulla[0]->getPosY()*30);
    velocidad2d = Body->GetLinearVelocity();

    velocidad2d.x = 25.f;

}

void EnemigoElite::Update(Posicion* prota)
{
  update(prota);                                              // Llamamos tambien al update de la clase general del enemigo y actualizamos los valores de sed - hambre del mismo
  if(enemigo!=nullptr)
  {
      comprobarEnergia();

      comportamiento->update(this);                           // Empezamos a ejecutar el arbol de comportamiento del enemigo

      EnemigoPosition->setPosX(Body->GetPosition().x);
      EnemigoPosition->setPosY(Body->GetPosition().y);

      fachada->setPosicion(enemigo,EnemigoPosition);
  }

}


void EnemigoElite::comprobarEnergia()
{
	if(VELOCIDAD_ENEMIGO >VELOCIDAD_NORMAL)  // Si su velcidad es mayor que la velocidad normal de moviemiento, empieza a bajar la energia
    {
        if(energia >0)
        {
            energia+= -5.f * frameDeltaTime;
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

void EnemigoElite::CreateBox(b2World& world, float X, float Y)
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


EnemigoElite::~EnemigoElite()
{
    comportamiento = nullptr;
}
