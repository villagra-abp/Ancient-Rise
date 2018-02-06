#include "../headerfiles/Huir.h"

Status Huir::run(Enemigo *e)
{   
    /* INFO DEL ENEMIGO */
    enemigoNode = e->getNode();
    core::vector3df EnemigoPosition = enemigoNode->getPosition(); // VOLVEMOS A OBTENER EL VECTOR DE POSICION DEL ENEMIGO POR SI HA CAMBIADO
    float enemigoX=EnemigoPosition.X;


    frameDeltaTime = board->getTime();
    e->setVelocidad(25.f);

     /* RELOJ HUIR */
    this->startClock();                             // INICIAMOS EL RELOJ (O RESEATEAMOS)

    int time = reloj.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

    //cout<<time<<endl;
    
    if(time>=4)
    {
        contador = 0;                               // RESETEAMOS EL CONTADOR
        return BH_SUCCESS;
    }
    else
    {
        if(e->getUltDirecVisto()==true)   // Visto Prota a la derecha, enemigo huye hacia la izquierda
        {

            EnemigoPosition.X-= e->getVelocidad() * frameDeltaTime;

            e->setLastFacedDir(false);                                     // AHORA ESTA MIRANDO A LA IZQUIERDA

             //e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
            // e->getBody()->ApplyForceToCenter(b2Vec2(-150.f,0.f),true);             // Fuerza para correr

            e->setPosition(EnemigoPosition);
        }
        else{   // Visto a la izquierda, se mueve hacia la derecha

                 EnemigoPosition.X+= e->getVelocidad() * frameDeltaTime;
                 e->setLastFacedDir(true); 

                 //e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                 //e->getBody()->ApplyForceToCenter(b2Vec2(150.f,0.f),true);             // Fuerza para correr

                 e->setPosition(EnemigoPosition); // CAMBIAMOS LA POSICION
        }
    }

   return BH_RUNNING;
}

void Huir::startClock()
{
    if(contador==0)
    {
        reloj.restart();
        contador = contador +1;
    }
}

void Huir::onInitialize(Blackboard *b)
{
	board = b;
    contador = 0;
}

Huir::~Huir()
{
    board = nullptr;
    enemigoNode = nullptr;


    //delete board;
}