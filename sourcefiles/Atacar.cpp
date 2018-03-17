#include "../headerfiles/Atacar.h"

Status Atacar::run(Enemigo *e)
{   
	float posProta = board->getProta();

	// DATOS ENEMIGO
	enemigoNode = e->getNode();
    Posicion* EnemigoPosition = e->getPosition(); 
    float enemigoX=EnemigoPosition->getPosX();

    int distanciaProta = posProta - enemigoX;  // Calculamos la distancia hasta el prota

    // Comprobamos el tipo de arma que utiliza
    if(e->getTipo()==1)     // Cuerpo a cuerpo, cerca
    {
        separacionAtaque = 25;
    }
    else  // A distancia, ataque desde mas lejos
    {
        separacionAtaque = 60;
    }

    /* Comprobamos la distancia a la que tiene que estar para atacar */
    if(abs(distanciaProta)>separacionAtaque)                                        // PERSIGUIENDO  
    {
        e->setCombate(false);
        contRec = 0;              // Para resetear el reloj de recargar proyectil y que tarde siempre lo mismo en recargar

        if (distanciaProta<0) // AVANZAMOS HACIA LA IZQUIERDA
         {
            e->getBody()->SetLinearVelocity(-(e->getVelocidad2d()));               // Velocidad Normal
            e->getBody()->ApplyForceToCenter(b2Vec2(-300.f,0.f),true);             // Fuerza para correr
            e->setLastFacedDir(false);   
         }
         else{
                if(distanciaProta>0) // AVANZAMOS HACIA LA DERECHA
                {
                    e->getBody()->SetLinearVelocity(e->getVelocidad2d());
                    e->getBody()->ApplyForceToCenter(b2Vec2(300.f,0.f),true);             // Fuerza para correr

                    e->setLastFacedDir(true);   
                }
            }
    }
    else        // ATACANDO
    {
        if(e->getOrden()==1)        // Ya hemos ejecutado la orden de atacarle mandado por el Elite, la eliminamos
        {
            e->setOrden(0);
        }
        e->setCombate(true);    // COMBATIENDO


        if(e->getTipo()==1)  // Mele
        {
            int pos_combate = rand() % 3 + 1;
             /* RELOJ POS COMBATE */
            startClock(1);                                        // INICIAMOS EL RELOJ (O RESEATEAMOS) DE POS_COMBATE
            int time = relojPos.getElapsedTime().asSeconds();     // OBTENEMOS SU DURACION EN SEGUNDOS

            if(time>3)
            {
                e->setPosCombate(pos_combate);
                contPos = 0;
            }

            /* RELOJ ATAQUE MELE */
            startClock(3);
            int time2 = relojAtq.getElapsedTime().asSeconds();
    
            if(time2>1)
            {
                if(p->getCombate()!=true || p->getPosCombate()!=pos_combate)        // Si el prota no esta en modo combate o no esta en la pos_combate donde ataca el enemigo, le quita vida
                {
                    p->quitarVida(10.f);
                }
                contAtq=0;
            }

        }
        else // A Distancia
        {   
            startClock(2);
            int time = relojRec.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

             if(time>3)
            {  
                e->setDisparo(true);                        // Para saber si hay que crear un proyectil nuevo
                contRec = 0;
                return BH_SUCCESS;
            }

            e->setDisparo(false);  
        }   

    }
    return BH_SUCCESS;
    
}

/*
 Funcion para iniciar el reloj correspondienteen funcion del entero que pasamos
*/
void Atacar::startClock(int t)
{
    switch(t)
    {
        case 1: // Reloj tiempo cambiar pos_combate
        {
             if(contPos==0)
            {
                relojPos.restart();
                contPos = contPos +1;
            }
            break;
        }

        case 2: //Reloj tiempo recarga disparo proyectil
        {
            if(contRec==0)
            {
                relojRec.restart();
                contRec = contRec +1;
            }
            break;
        }

        case 3: // Reloj tiempo atacar protagonista
        {
            if(contAtq==0)
            {
                relojAtq.restart();
                contAtq = contAtq+1;
            }
            break;
        }

    }   
}

void Atacar::onInitialize(Blackboard *b)
{
    Fachada* fachada=fachada->getInstance();
    board = b;
    separacionAtaque = 10;
    p = board->getProtagonista();
    enemigoNode = nullptr;
}

Atacar::~Atacar()
{
    board = nullptr;
    enemigoNode = nullptr;
}
