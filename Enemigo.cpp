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

	VELOCIDAD_ENEMIGO=8.f;
	contadorPatrulla=0;
	patrulla=true;
}

/**
FUNCION DONDE EL ENEMIGO REALIZA LA PATRULLA Y ESTA ATENTO A LAS COSAS QUE SUCEDEN ALREDEDOR
PARAMETROS : TIEMPO, ARRAY CON LAS POSICIONES DE LA PATRULLA, POSICION DEL PROTA
**/

void Enemigo::Patrulla(const f32 Time, Posicion *posiciones[], float protaPosition)
{

    VELOCIDAD_ENEMIGO = 8.f;

    core::vector3df EnemigoPosition = enemigo->getPosition(); // VECTOR DE POSICION DEL ENEMIGO

    float enemigoX=EnemigoPosition.X;
    float posPatrullaX = posiciones[contadorPatrulla]->getPosX();

    int distanciaObjetivoX= posPatrullaX - enemigoX;     // DISTANCIA EN X AL OBJETIVO DE LA PATRULLA


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

}


/**
FUNCION PARA PERSEGUIR AL PROTAGONISTA
PARAMETROS : VECTOR3D CON COORDENADAS DEL ENEMIGO, X DEL ENEMIGO, X PROTA, TIEMPO
**/
void Enemigo::Perseguir(vector3df EnemigoPosition, float enemigoX, float protaPosition, const f32 Time)
{
    VELOCIDAD_ENEMIGO = 15.f;

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

scene::ISceneNode* Enemigo::getNode()
{
    return enemigo;
}


bool Enemigo::setPatrulla(bool p)
{
    patrulla=p;
}

Enemigo::~Enemigo()
{
    //dtor
}
