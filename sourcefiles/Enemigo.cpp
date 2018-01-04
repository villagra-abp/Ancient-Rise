#include "../headerfiles/Enemigo.h"



/**

 CONSTRUCTOR DE ENEMIGO
 Parametros : Objetos Irrlicht, vector con posiciones de la patrulla
*/
Enemigo::Enemigo(IrrlichtDevice *dev, ISceneManager* smgr, vector<Posicion*> pos, float xlength, float pendValue):enemigo(nullptr), env(nullptr)

{
    enemigo=smgr->addCubeSceneNode();

    if (enemigo) /** SI HEMOS CREADO EL CUBO **/
	{
		enemigo->setPosition(core::vector3df(pos[0]->getPosX(),pos[0]->getPosY(),pos[0]->getPosZ())); // INDICAMOS SU POS INICIAL ( QUE VIENE INDICADA EN EL ARRAY TAMBIEN)
		enemigo->setMaterialFlag(video::EMF_LIGHTING, false);

        EnemigoPosition = enemigo->getPosition();


	}

    env = dev->getGUIEnvironment();

    encontradoComida=false,
    avistadoProta = false;

     //Parametros para el rango de vision del personaje.
    lastFacedDir = true;
    visionXmax = xlength;
    valorPendiente = pendValue;
    visto = false;


    posPatrulla = pos;                  // Guardamos el vector con las posiciones de la patrulla del enemigo

}

/* Update para todos los enemigos para actualizar los valores del hambre y la sed */
void Enemigo::update(core::vector3df prota)
{
        this->actualizarHambre(); 
        this->actualizarSed();

        if(this->checkInSight(prota)){
            visto = true;
        }else{
            visto = false;

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
FUNCION PARA QUE EL ENEMIGO BUSQUE COMIDA CUANDO SU STAT DE HAMBRE ES BAJO
**/
void Enemigo::buscarComida(scene::ISceneNode *comida)
{

    this->setVelocidad(15.f);

    core::vector3df comidaPosition = comida->getPosition();

    float ComidaX = comidaPosition.X;
    float EnemigoX = EnemigoPosition.X;

    int distanciaComida = ComidaX - EnemigoX;  // DISTANCIA HASTA LA COMIDA

    //this->ComprobarDistancia(distanciaComida);

    if(distanciaComida==0) // HA LLEGADO HASTA LA COMIDA
    {
        encontradoComida=true;
        hambre=100.f;   // RECARGA EL HAMBRE
    }
}

void Enemigo::updateTiempo(const f32 Time)
{
    frameDeltaTime = Time;
}

bool Enemigo::checkInSight(core::vector3df objPos){
    bool inSight = false;  //Valor para retorno, si la posicion recibida se encuentra
    // dentro del rango de vision sera TRUE.

    float pjxmin;          // Valor real en la ventana del punto del area con X Minima.
    float pjxmax;          // Valor real en la ventana del punto del area con X Maxima.
    float pjymin;          // Valor real en la ventana del punto del area con Y Minima, respecto a la X recibida.        
    float pjymax;          // Valor real en la ventana del punto del area con Y Maxima, respecto a la X recibida.
    float xReady;

    
    //Valores necesarios para el Anyadido.
    float ylength = visionXmax * valorPendiente;        
    float xlength = visionXmax;

    float xprima = visionXmax / 5;  //Podria ser 1/5 de visionXmax
    float xprima1 = 2 * xprima / 3;

    float pjxmax2 = 0.0;
    float pjxmin2 = 0.0;

    float yprima = ylength / 2;

    float pend1 = yprima/xprima1;
    float pend2 = yprima/(xprima - xprima1);

    //std::cout << enemigo->getPosition().X << endl;
    if(lastFacedDir){   //Mira hacia derecha
        pjxmin = enemigo->getPosition().X + 2;
        pjxmax = enemigo->getPosition().X + 2 + visionXmax;
        pjxmax2 = pjxmax + xprima;
        xReady = objPos.X - pjxmin;
    }else{              //Mira hacia izquierda
        pjxmin = enemigo->getPosition().X - visionXmax;
        pjxmax = enemigo->getPosition().X;
        pjxmin2 = pjxmin - xprima;
        xReady = -(objPos.X - pjxmax);
    }

    if(objPos.X < pjxmax && objPos.X > pjxmin){
        pjymax = xReady * valorPendiente + EnemigoPosition.Y;
        pjymin = EnemigoPosition.Y - (pjymax - EnemigoPosition.Y);
        
        if(objPos.Y > pjymin && objPos.Y < pjymax)
            inSight = true;
    
    }else{  //Segunda parte del area, anyadido.

        if(lastFacedDir){
            if (objPos.X >= pjxmax && objPos.X < pjxmax2){  
                if(objPos.X < (pjxmax+xprima1)){
                    pjymax = -(objPos.X - (pjxmax + xprima1)) * pend1 + EnemigoPosition.Y + yprima;
                    pjymin = EnemigoPosition.Y - (pjymax - EnemigoPosition.Y);                    
                }else{
                    pjymax = -(objPos.X - (pjxmax + xprima)) * pend2 + EnemigoPosition.Y;
                    pjymin = EnemigoPosition.Y - (pjymax - EnemigoPosition.Y);
                }
                
                if(objPos.Y < pjymax && objPos.Y > pjymin)
                    inSight = true;
                
            }
        }else{

            if(objPos.X > pjxmin2 && objPos.X <= pjxmin){
                if(objPos.X > (pjxmin-xprima1)){
                    pjymax = (objPos.X - (pjxmin - xprima1)) * pend1 + EnemigoPosition.Y + yprima;
                    pjymin = EnemigoPosition.Y - (pjymax-EnemigoPosition.Y);                    
                }else{
                    pjymax = (objPos.X - (pjxmin - xprima)) * pend2 + EnemigoPosition.Y;
                    pjymin = EnemigoPosition.Y - (pjymax-EnemigoPosition.Y);
                }
                
                if(objPos.Y < pjymax && objPos.Y > pjymin)
                    inSight = true;

            }
        }
    }

    return inSight;
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


f32 Enemigo::getVelocidad()
{
    return VELOCIDAD_ENEMIGO;
}

f32 Enemigo::getSed()
{
    return sed;
}

bool Enemigo::getAvistadoProta()
{
    return avistadoProta;
}

f32 Enemigo::getSalud()
{
    return salud;
}

vector<Posicion*> Enemigo::getPosicion()
{
    return posPatrulla;
}

const f32 Enemigo::getVelNormal()
{
    return VELOCIDAD_NORMAL;
}

int Enemigo::getTipo()
{
    return tipo;
}

float Enemigo::getXRange(){
    return visionXmax;
}

float Enemigo::getYPend(){
    return valorPendiente;
}

bool Enemigo::getVisto(){
    return visto;
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

void Enemigo::setAvistadoProta(bool a)
{
    avistadoProta = a;
}

void Enemigo::setVelHambre(f32 v)
{
    velHambre = v;
}

void Enemigo::setVelSed(f32 v)
{
    velSed = v;
}

void Enemigo::setLastFacedDir(bool dirx){
    lastFacedDir = dirx;
}


Enemigo::~Enemigo()
{
    //dtor
}
