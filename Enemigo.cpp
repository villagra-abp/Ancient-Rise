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

    env = dev->getGUIEnvironment();

	contadorPatrulla=0;
	direccion=0;
    llegadoObjetivo=false;
    encontradoAgua=false;
    encontradoComida=false,
    encontradoDescanso=false;

    //COMPORTAMIENTOS
    patrulla=true;
    avistadoProta=false;
    alarma=false;


    velHambre=-0.2;
    velSed=-0.5;

    estadisticas.resize(3);

    estadisticas[0]=false; // SED = FALSE
    estadisticas[1]=false; // HAMBRE
    estadisticas[2]=false; // ENERGIA


}

/**
FUNCION DONDE EL ENEMIGO REALIZA LA PATRULLA Y ESTA ATENTO A LAS COSAS QUE SUCEDEN ALREDEDOR
PARAMETROS : TIEMPO, ARRAY CON LAS POSICIONES DE LA PATRULLA, POSICION DEL PROTA
**/

void Enemigo::Patrulla(const f32 Time, Posicion *posiciones[], float protaPosition, bool alarm, scene::ISceneNode *fuente)
{
    

        this->actualizarHambre(Time); 
        this->actualizarSed(Time);

        core::vector3df EnemigoPosition = enemigo->getPosition(); // VECTOR DE POSICION DEL ENEMIGO

        float enemigoX=EnemigoPosition.X;
        float posPatrullaX = posiciones[contadorPatrulla]->getPosX();

        int distanciaNodoX= posPatrullaX - enemigoX;     // DISTANCIA EN X AL NODO DE LA PATRULLA


        //** COMPROBACIONES **//

         //1º COMPRUEBA SI PROTAGONISTA CERCA (ESTO SIEMPRE SERA LO MAS IMPORTANTE (SIEMPRE LO HARA PRIMERO ) INDEPENDIENTEMENTE DE LO QUE OCURRA)

        int distanciaProtaX = protaPosition - enemigoX;      // DISTANCIA EN X AL PROTAGONISTA

        if(abs(distanciaProtaX)<20)   // SI PROTA AVISTADO
        {
            avistadoProta=true;

            patrulla=false;
            alarma=false;
            estadisticas[0]=false;
            estadisticas[1]=false;
            estadisticas[2]=false;
            

        }
        else  // 2 º COMPRUEBA SI HAY ALGUNA ALARMA SONANDO 
        {
            avistadoProta=false;

            if(alarm==true) // ALARMA SONANDO 
            {
                alarma=true;

                patrulla = false;
                estadisticas[0]=false;
                estadisticas[1]=false;
                estadisticas[2]=false;
            

            }
            else // 3º COMPRUEBA SI ENERGIA - HAMBRE - SED BAJOS 
            {
                alarma=false;

                if(hambre<=30.f)
                {
                    estadisticas[1]=true;

                    patrulla=false;
                }

                if(sed<=50.f)
                {
                    estadisticas[0]=true;

                    patrulla=false;
                }

                if(energia<=20.f)
                {
                    estadisticas[2]=true;

                    patrulla=false;
                }

                if(estadisticas[0]==false && estadisticas[1]==false && estadisticas[2]==false)
                {
                    patrulla=true;
                }
                
            }
        }

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
        else{

                if(estadisticas[0]==true)
                {
                    this->buscarAgua(fuente, EnemigoPosition, Time);

                    if(encontradoAgua==true)
                    {
                        estadisticas[0]=false; // YA NO TENEMOS SED
                        patrulla=true;
                    }
                }

                if(estadisticas[1]==true)
                {
                    this->buscarComida();
                }

                if(estadisticas[2]==true)
                {
                    this->buscarDescanso();
                }
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
FUNCION PARA ACTUALIZAR EL ESTADO DEL HAMBRE DEL ENEMIGO EN FUNCION DE LA CANTIDAD QUE LE PASEMOS
**/

void Enemigo::actualizarHambre(const f32 Time)
{
    //hambre+=velHambre*Time;

    //cout<<hambre<<endl;
    //int r=round(hambre);
    //core::stringw tmp(L"HAMBRE: ");
    //tmp += r;
    //env->addStaticText(tmp.c_str(),core::rect<s32>(10,10,260,22), false);
}

/**
FUNCION PARA ACTUALIZAR EL ESTADO DE SED DEL ENEMIGO
**/

void Enemigo::actualizarSed(const f32 Time)
{
     sed+=velSed*Time;

     cout<<sed<<endl;

}
/**
FUNCION PARA ACTUALIZAR EL ESTADO DE LA ENERGIA DEL ENEMIGO
**/

void Enemigo::actualizarEnergia()
{

}
/**
FUNCION PARA QUE EL ENEMIGO BUSQUE COMIDA CUANDO SU STAT DE HAMBRE ES BAJO
**/
bool Enemigo::buscarComida()
{
    return false;
}


/**
FUNCION PARA QUE EL ENEMIGO BUSQUE AGUA CUANDO SU STAT DE SED ES BAJO
PARAMETROS : POSICION DE LA FUENTE MAS CERCANA, VECTOR DE POSICION DEL ENEMIGO, TIEMPO
**/
void Enemigo::buscarAgua(scene::ISceneNode *fuente, vector3df EnemigoPosition, const f32 Time)
{
    core::vector3df FuentePosition = fuente->getPosition();

    float FuenteX = FuentePosition.X;
    float EnemigoX = EnemigoPosition.X;

    int distanciaFuente = FuenteX - EnemigoX;  // DISTANCIA HASTA LA FUENTE 

    this->ComprobarDistancia(EnemigoPosition, distanciaFuente, Time);

    if(distanciaFuente==0) // HE LLEGADO A LA FUENTE DE AGUA 
    {
        encontradoAgua=true;
        sed=100.f;   // BEBE AGUA Y RECARGA LA SED
    }

}

/**
FUNCION PARA QUE EL ENEMIGO BUSQUE UN SITIO PARA DESCANSAR CUANDO SU STAT DE ENERGIA ES BAJO
**/
bool Enemigo::buscarDescanso()
{
   return false;
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

bool Enemigo::getEstadoPatrulla()
{
    return patrulla;
}

vector <bool> Enemigo::getEstadoEstadisticas()
{
    return estadisticas;
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
