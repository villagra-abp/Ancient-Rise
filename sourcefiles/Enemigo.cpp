#include "../headerfiles/Enemigo.h"



/**

 CONSTRUCTOR DE ENEMIGO
*/
Enemigo::Enemigo(IrrlichtDevice *dev, ISceneManager* smgr, Posicion *posiciones[]):enemigo(nullptr), env(nullptr)

{
    enemigo=smgr->addCubeSceneNode();

    if (enemigo) /** SI HEMOS CREADO EL CUBO **/
	{
		enemigo->setPosition(core::vector3df(posiciones[0]->getPosX(),posiciones[0]->getPosY(),posiciones[0]->getPosZ())); // INDICAMOS SU POS INICIAL ( QUE VIENE INDICADA EN EL ARRAY TAMBIEN)
		enemigo->setMaterialFlag(video::EMF_LIGHTING, false);

        EnemigoPosition = enemigo->getPosition();
	}

    env = dev->getGUIEnvironment();

	contadorPatrulla=0;
	direccion=0;

    encontradoAgua=false;
    encontradoComida=false,
    encontradoDescanso=false;


    //COMPORTAMIENTOS
    patrulla=true;
    avistadoProta=false;
    alarma=false;



    velHambre=-0.3;
    velSed=-0.5;

    estadisticas.resize(3);


    estadisticas[0]=false; // SED = FALSE
    estadisticas[1]=false; // HAMBRE
    estadisticas[2]=false; // ENERGIA


}

/**

FUNCION DONDE EL ENEMIGO REALIZA LA PATRULLA Y ESTA ATENTO A LAS COSAS QUE SUCEDEN ALREDEDOR (UPDATE)
PARAMETROS : TIEMPO, ARRAY CON LAS POSICIONES DE LA PATRULLA, POSICION DEL PROTA
**/

void Enemigo::Patrulla(const f32 Time, Posicion *posiciones[], float protaPosition, scene::ISceneNode *fuente, scene::ISceneNode *comida)
{
    
        this->setVelocidad(8.f);
        this->actualizarHambre(); 
        this->actualizarSed();
        this->updateTiempo(Time);

        EnemigoPosition = enemigo->getPosition(); // VOLVEMOS A OBTENER EL VECTOR DE POSICION DEL ENEMIGO POR SI HA CAMBIADO

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

            if(alarma==true) // ALARMA SONANDO 
            {
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


                    this->ComprobarDistancia(distanciaNodoX);
            }
        }
        else{  // COMPORTAMIENTO BUSCAR AGUA/COMIDA

                if(estadisticas[0]==true)  // NECESITA AGUA 
                {
                    this->buscarAgua(fuente);

                    if(encontradoAgua==true)
                    {
                        estadisticas[0]=false; // YA NO TENEMOS SED
                        patrulla=true;
                    }
                }

                if(estadisticas[1]==true) // NECESITA COMIDA
                {
                    this->buscarComida(comida);

                    if(encontradoComida==true)
                    {
                        estadisticas[1]=false; // YA NO TENEMOS HAMBRE
                        patrulla=true;
                    }
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

void Enemigo::Perseguir(float enemigoX, float protaPosition)

{
    VELOCIDAD_ENEMIGO = 15.f;       //AUMENTAMOS SU VELOCIDAD
    int distanciaProtaX = protaPosition - enemigoX;


    this->ComprobarDistancia(distanciaProtaX);



}

/**
FUNCION PARA COMPROBAR LA DISTANCIA QUE HAY DESDE EL ENEMIGO AL OBJETIVO Y VER EN QUE DIRECCION MOVERSE
PARAMETROS : VECTOR3D CON COORDENADAS DEL ENEMIGO, DISTANCIA AL OBJETIVO, TIEMPO
**/

void Enemigo::ComprobarDistancia(int distanciaObjetivoX)

{

     if (distanciaObjetivoX<0) // AVANZAMOS HACIA LA IZQUIERDA
     {

                EnemigoPosition.X-= VELOCIDAD_ENEMIGO * frameDeltaTime*3;

                enemigo->setPosition(EnemigoPosition); // CAMBIAMOS LA POSICION
     }
     else{
            if(distanciaObjetivoX>0) // AVANZAMOS HACIA LA DERECHA
            {

                EnemigoPosition.X+= VELOCIDAD_ENEMIGO * frameDeltaTime*3;

                enemigo->setPosition(EnemigoPosition);
            }
        }

}



/**
FUNCION PARA ACTUALIZAR EL ESTADO DEL HAMBRE DEL ENEMIGO EN FUNCION DE LA CANTIDAD QUE LE PASEMOS
**/

void Enemigo::actualizarHambre()
{
    hambre+=velHambre*frameDeltaTime;

    //cout<<round(hambre)<<endl;

}

/**
FUNCION PARA ACTUALIZAR EL ESTADO DE SED DEL ENEMIGO
**/

void Enemigo::actualizarSed()
{
     sed+=velSed*frameDeltaTime;

     //cout<<round(sed)<<endl;

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
void Enemigo::buscarComida(scene::ISceneNode *comida)
{

    this->setVelocidad(15.f);

    core::vector3df comidaPosition = comida->getPosition();

    float ComidaX = comidaPosition.X;
    float EnemigoX = EnemigoPosition.X;

    int distanciaComida = ComidaX - EnemigoX;  // DISTANCIA HASTA LA COMIDA

    this->ComprobarDistancia(distanciaComida);

    if(distanciaComida==0) // HA LLEGADO HASTA LA COMIDA
    {
        encontradoComida=true;
        hambre=100.f;   // RECARGA EL HAMBRE
    }
}


/**
FUNCION PARA QUE EL ENEMIGO BUSQUE AGUA CUANDO SU STAT DE SED ES BAJO
PARAMETROS : POSICION DE LA FUENTE MAS CERCANA, VECTOR DE POSICION DEL ENEMIGO, TIEMPO
**/
void Enemigo::buscarAgua(scene::ISceneNode *fuente)
{
    this -> setVelocidad(15.f);

    core::vector3df FuentePosition = fuente->getPosition();

    float FuenteX = FuentePosition.X;
    float EnemigoX = EnemigoPosition.X;

    int distanciaFuente = FuenteX - EnemigoX;  // DISTANCIA HASTA LA FUENTE 

    this->ComprobarDistancia(distanciaFuente);

    if(distanciaFuente==0) // HA LLEGADO A LA FUENTE DE AGUA 
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

void Enemigo::updateTiempo(const f32 Time)
{
    frameDeltaTime = Time;
}

/**
==============================================
A PARTIR DE AQUI VAN TODOS LOS GETS Y LOS SETS
==============================================
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


void Enemigo::setPosition(vector3df position)
{
    enemigo->setPosition(position);
}

void Enemigo::setAlarma(bool a)
{
    alarma=a;
    
}


Enemigo::~Enemigo()
{
    //dtor
}
