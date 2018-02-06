#include "../headerfiles/Huir.h"

Status Huir::run(Enemigo *e)
{   
    /* INFO DEL ENEMIGO */
    enemigoNode = e->getNode();

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
        if(e->getLastFaceDir()==true)   // Visto Prota a la derecha, enemigo huye hacia la izquierda
        {
            //e->setLastFacedDir(false);                                     // AHORA ESTA MIRANDO A LA IZQUIERDA

             e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
             e->getBody()->ApplyForceToCenter(b2Vec2(-300.f,0.f),true);             // Fuerza para correr

        }
        else{   // Visto a la izquierda, se mueve hacia la derecha

                 //e->setLastFacedDir(true); 

                 e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                 e->getBody()->ApplyForceToCenter(b2Vec2(300.f,0.f),true);             // Fuerza para correr
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

}