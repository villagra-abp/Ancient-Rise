#include "../headerfiles/EnemigoAvanzado.h"
#include "../headerfiles/BehaviorTree.h"

EnemigoAvanzado::EnemigoAvanzado(IrrlichtDevice *dev, ISceneManager *smgr, vector<Posicion*> pos, float xlength, float pendValue, int t, const Entorno* e, Blackboard *b, b2World& world):Enemigo(dev, smgr, pos, xlength, pendValue, e, b)
{

    //ESTABLECEMOS LAS ESTADISTICAS ENEMIGO AVANZADO

    setEnergia(ENERGIA_MAX);
    setHambre(100.f);
    salud = 100.f;
    setSed(100.f);
    setVelocidad(VELOCIDAD_NORMAL);

    tipo = t;                                                   // Tipo de combate que usa (Distancia o Cuerpo a Cuerpo)
    claseEnemigo = 2;                                           // EnemigoBasico

    /* CREAMOS EL ARBOL DE COMPORTAMIENTO DE EL ENEMIGO BASICO PASANDOLE LA BLACKBOARD */
    comportamiento = new BehaviorTree(3, b);              
    

     /* Velocidad a la que bajan las estadisticas del enemigo */
    setVelHambre(-0.2);
    setVelSed(-0.4);

    /* BOX2D */
    nodoPosition = patrulla[0]->getPosition();
    CreateBox(world, nodoPosition->getPosX()*30, nodoPosition->getPosY()*30);

    velocidad2d = Body->GetLinearVelocity();

    velocidad2d.x = 25.f;

}

void EnemigoAvanzado::Update(Posicion* prota)
{
    update(prota);                                     // Llamamos tambien al update de la clase general del enemigo y actualizamos los valores de sed - hambre del mismo
    if(enemigo!=nullptr)
    {
        comprobarEnergia();

        comportamiento->update(this);                           // Empezamos a ejecutar el arbol de comportamiento del enemigo

        EnemigoPosition->setPosX(Body->GetPosition().x);        // Establecemos su velocidad con el body
        EnemigoPosition->setPosY(Body->GetPosition().y);

       fachada->setPosicion(enemigo,EnemigoPosition);
    }
    
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
    FixtureDef.filter.groupIndex = GROUP_ENEMIGOS;
    Body->CreateFixture(&FixtureDef);

  
}


EnemigoAvanzado::~EnemigoAvanzado()
{

}


