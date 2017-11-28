#include "Enemigo.h"



/**
 CONSTRUCTOR
*/
Enemigo::Enemigo(IrrlichtDevice *dev, ISceneManager* smgr, Posicion *posiciones[])
{
    enemigo=smgr->addCubeSceneNode();

    if (enemigo) /** SI HEMOS CREADO EL CUBO **/
	{
		enemigo->setPosition(core::vector3df(posiciones[0]->getPosX(),posiciones[0]->getPosY(),posiciones[0]->getPosZ())); // INDICAMOS SU POS INICIAL ( QUE VIENE INDICADA EN EL ARRAY TAMBIEN)
		enemigo->setMaterialFlag(video::EMF_LIGHTING, false);
	}

	contadorPatrulla=0;
	direccion=0;

    //COMPORTAMIENTOS
    patrulla=true;
    avistadoProta=false;
    alarma=false;

    estadisticas[0]=false; // SED = FALSE
    estadisticas[1]=false; // HAMBRE
    estadisticas[2]=false; // ENERGIA


}

/**
FUNCION DONDE EL ENEMIGO REALIZA LA PATRULLA Y ESTA ATENTO A LAS COSAS QUE SUCEDEN ALREDEDOR
PARAMETROS : TIEMPO, ARRAY CON LAS POSICIONES DE LA PATRULLA, POSICION DEL PROTA
**/

void Enemigo::Patrulla(const f32 Time, Posicion *posiciones[], float protaPosition)
{
    /*
    VELOCIDAD_ENEMIGO = 8.f;

    core::vector3df EnemigoPosition = enemigo->getPosition(); // VECTOR DE POSICION DEL ENEMIGO

    float enemigoX=EnemigoPosition.X;
    float posPatrullaX = posiciones[contadorPatrulla]->getPosX();

    int distanciaObjetivoX= posPatrullaX - enemigoX;     // DISTANCIA EN X AL OBJETIVO DE LA PATRULLA
    int distanciaProtaX = protaPosition - enemigoX;      // DISTANCIA EN X AL PROTAGONISTA


    // EL ENEMIGO COMPRUEBA TODO EN TODO MOMENTO( SI PROTAGONISTA CERCA - SI ESTADISTICAS BAJAS - SI ALARMA SONANDO )

    if(energia<30.f || sed>50.f || hambre >50.f)  // 1º ESTADISTICAS
    {

    }
    else {  // 2º PROTA CERCA

           //if(abs(distanciaProtaX)<40)
            //{
               // patrulla=false;
            //}

    }

        if(patrulla!=false)  // SOLAMENTE SI NO HA SUCEDIDO NADA ( AVISTADO OBJETIVO, ESTADISTICAS BAJAS O ALARMA) ESTAMOS EN COMPORTAMIENTO DE PATRULLA
        {
            if(distanciaObjetivoX==0) // SI ESTAMOS EN LA POS DE LA PATRULLA AVANZAMOS A LA SIGUIENTE POS
            {
                if(contadorPatrulla==4)
                {
                    contadorPatrulla=0;
                }
                else {
                    contadorPatrulla++;
                }
            }
            else{

                    this->ComprobarDistancia(EnemigoPosition, distanciaObjetivoX, Time);
            }
        }
        else{ // CAMBIAMOS DE COMPORTAMIENTO --> PERSEGUIR


                this->Perseguir(EnemigoPosition, enemigoX, protaPosition, Time);

        }
        */

        core::vector3df EnemigoPosition = enemigo->getPosition(); // VECTOR DE POSICION DEL ENEMIGO

        float enemigoX=EnemigoPosition.X;
        float posPatrullaX = posiciones[contadorPatrulla]->getPosX();

        int distanciaNodoX= posPatrullaX - enemigoX;     // DISTANCIA EN X AL NODO DE LA PATRULLA


        if(patrulla==true) // COMPORTAMIENTO DE PATRULLA
        {
            if(distanciaNodoX==0) // SI ESTAMOS EN UNO DE LOS NODOS DE LA PATRULLA BUSCAMOS EL SIGUIENTE NODO
            {
                if(contadorPatrulla==4)
                {
                    contadorPatrulla=0;
                }
                else {
                    contadorPatrulla++;
                }
            }
            else{  // AUN NO HEMOS LLEGADO A NINGUN NODO DE LA PATRULLA

                    this->ComprobarDistancia(EnemigoPosition, distanciaNodoX, Time);
            }
        }
        else
        {

        }

}


/**
FUNCION PARA PERSEGUIR AL PROTAGONISTA
PARAMETROS : VECTOR3D CON COORDENADAS DEL ENEMIGO, X DEL ENEMIGO, X PROTA, TIEMPO
**/
void Enemigo::Perseguir(vector3df EnemigoPosition, float enemigoX, float protaPosition, const f32 Time)
{
    VELOCIDAD_ENEMIGO = 15.f;       //AUMENTAMOS SU VELOCIDAD
    int distanciaProtaX = protaPosition - enemigoX;

    this->ComprobarDistancia(EnemigoPosition, distanciaProtaX, Time);


}

/**
FUNCION PARA COMPROBAR LA DISTANCIA QUE HAY DESDE EL ENEMIGO AL OBJETIVO Y VER EN QUE DIRECCION MOVERSE
PARAMETROS : VECTOR3D CON COORDENADAS DEL ENEMIGO, DISTANCIA AL OBJETIVO, TIEMPO
**/
void Enemigo::ComprobarDistancia(vector3df EnemigoPosition, int distanciaObjetivoX, const f32 Time)
{

     if (distanciaObjetivoX<0) // AVANZAMOS HACIA LA IZQUIERDA
     {
                EnemigoPosition.X-= VELOCIDAD_ENEMIGO * Time*3;
                enemigo->setPosition(EnemigoPosition); // CAMBIAMOS LA POSICION
     }
     else{
            if(distanciaObjetivoX>0) // AVANZAMOS HACIA LA DERECHA
            {
                EnemigoPosition.X+= VELOCIDAD_ENEMIGO * Time*3;
                enemigo->setPosition(EnemigoPosition);
            }
        }

}



/**
A PARTIR DE AQUI VAN TODOS LOS GETS Y LOS SETS
**/
scene::ISceneNode* Enemigo::getNode()
{
    return enemigo;
}

bool Enemigo::getEstadoAlarma()
{
    return alarma;
}

bool Enemigo::getEstadoAvistadoProta()
{
    return avistadoProta;
}


void Enemigo::setPatrulla(bool p)
{
    patrulla=p;
}

void Enemigo::setSalud(f32 s)
{
    salud=s;
}

void Enemigo::setEnergia(f32 e)
{
    energia=e;
}

void Enemigo::setHambre(f32 h)
{
    hambre=h;
}

void Enemigo::setVelocidad(f32 v)
{
    VELOCIDAD_ENEMIGO=v;
}

void Enemigo::setSed(f32 se)
{
    sed=se;
}

Enemigo::~Enemigo()
{
    //dtor
}
