#include "../headerfiles/Enemigo.h"
#include "../headerfiles/Blackboard.h"
#include "../headerfiles/Proyectil.h"


/**

 CONSTRUCTOR DE ENEMIGO
 Parametros : Objetos Irrlicht, vector con posiciones de la patrulla
*/
Enemigo::Enemigo(vector<Posicion*> pos, float xlength, float pendValue, const Entorno* e, Blackboard *b) : enemigo(nullptr), ent(e), board(nullptr), proyectil(nullptr)
{
    GameObject::setTipo(ENEMY);
    Fachada* fachada=fachada->getInstance();
	//enemigo = fachada->addCube(pos[0]->getPosX(),pos[0]->getPosY(),pos[0]->getPosZ(),false);
    FObjeto* enemigoObjeto = fachada->addMalla(pos[0]->getPosX(),pos[0]->getPosY(),pos[0]->getPosZ(), "resources/personaje.obj");
    enemigo = enemigoObjeto;
    cout<<pos[0]->getPosX()<<" "<<pos[0]->getPosY()<<" "<<pos[0]->getPosZ()<<endl;
    if (enemigo) /** SI HEMOS CREADO EL CUBO **/
	{  
         //driver = fachada->getDriver();
        //fachada ->setMaterial(enemigo,"resources/verde.jpg");
        Posicion* pos= new Posicion(pos[0].getPosX(),pos[0].getPosY(),pos[0].getPosZ());
        EnemigoPosition = pos;


	}

    board = b;                                             // Guardamos la blackboard 

    //env = dev->getGUIEnvironment();

    /* Valores por defecto para los parametros para el rango de vision del enemigo */
    lastFacedDir = true;
    visionXmax = xlength;
    valorPendiente = pendValue;
    visto = false;
    direccVistoUlt = false;

    nodos = board->getNodosGrafo();              // Obtenemos todos los nodos del grafo
    /* COMPROBAMOS QUE LAS POSICIONES DE PATRULLA COINCIDEN CON LOS NODOS DEL GRAFO */
    for(int i=0; i<pos.size();i++)
    {
        for(int i2=0;i2<nodos.size();i2++)
        {
            nodoPosition = nodos[i2]->getPosition();
            if(pos[i]->getPosX()==nodoPosition->getPosX() && pos[i]->getPosY()==nodoPosition->getPosY())
            {
                patrulla.push_back(nodos[i2]);          // Metemos los nodos para poder hacer la patrulla
            }

        }
    }

    /* Valores por defecto para los parametros para el combate del enemigo */
    combate = false;
    disparo = false;
    pos_combate = 2; 
    contador = 0;
    memoria = false;
    orden = 0;                                            // Ninguna orden recibida


}

/* Update para todos los enemigos*/
void Enemigo::update(Posicion* Posprota)
{

    if(salud<0)
    {
        //enemigo->remove();
    }

    if(enemigo!=nullptr)  // Solo si existe el enemigo hacemos su update
    { 

        actualizarHambre(); 
        actualizarSed();
    
        //cout<<"Vida: "<<salud<<endl;
        //COMPROBAMOS GAMEOBJECTS DENTRO DE LA VISTA
        vistos.clear();

        for(int i = 0; i < ent->getSize(); i++){
            if(checkInSight(ent->getGameObject(i)->getPosition())){
                vistos.push_back(ent->getGameObject(i));
                
            }
        }

        // COMPROBAMOS SI HEMOS VISTO AL PROTAGONISTA 
        if(checkInSight(Posprota)){              
            visto = true;
             //fachada->setMaterial(enemigo,"resources/activada.jpeg");  
             contador = 0;
            
        }else{
            if(recordarProta())
            {
                visto = false;
                //fachada->setMaterial(enemigo,"resources/verde.jpg");
            }
            
        }

        
        /* COMBATE MELE */
            

        /* COMBATE DISTANCIA */
        if(tipo==2) // Enemigo tipo distancia
        {
            if(disparo==true)  // Nuevo disparo, hay que crear un proyectil nuevo
            {   
                if(proyectil!=nullptr)  // SI habia ya un proyectil creado lo borramos antes de crear uno nuevo
                {
                    proyectil->destroyProyectil();
                    proyectil = nullptr;
                }
                proyectil = new Proyectil(this);
            }
            else  // Aun no disparamos otra vez
            {
                if(combate == false)  // No combatiendo
                {
                    if(proyectil!=nullptr)
                    {   
                        proyectil->destroyProyectil();   
                        proyectil = nullptr;
                    }
                }
            }

                proyectil->update(this,board);

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

void Enemigo::updateTiempo(const glm::f32 Time)
{
    frameDeltaTime = Time;
}

/*
FUNCION PARA RECORDAR DURANTE UNOS SEGUNDOS AL PROTA DESPUES DE PERDERLE DE VISTA
*/
bool Enemigo::recordarProta()
{

    memoria = true;

    if(contador==0)
    {
        reloj.restart();
        contador = contador +1;
    }

    int time = reloj.getElapsedTime().asSeconds();

    if(time>5)      // Si pasan mas de 5 segundos desde que me vio, entonces ya no me ve
    {
        memoria = false;
    }

    return memoria;
}

/**
FUNCION QUE SIRVE PARA SABER SI UN DETERMINADO OBJETO DEL JUEGO ESTA DENTRO DEL AREA DE VISION DEFINIDO PARA EL ENEMIGO. 
DEVUELVE TRUE EN EL CASO DE ESTARLO
**/
bool Enemigo::checkInSight(Posicion* objPos){
    
    float posObjX=objPos->getPosX();
    float posObjY=objPos->getPosY();
    
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
        pjxmin = fachada->getPosicion(enemigo)->getPosX();
        pjxmax = fachada->getPosicion(enemigo)->getPosX() + visionXmax;
        pjxmax2 = pjxmax + xprima;
        xReady = posObjX - pjxmin;
    }else{              //Mira hacia izquierda
        pjxmin = fachada->getPosicion(enemigo)->getPosX() - visionXmax;
        pjxmax = fachada->getPosicion(enemigo)->getPosX();
        pjxmin2 = pjxmin - xprima;
        xReady = -(posObjX - pjxmax);
    }

    if(posObjX < pjxmax && posObjX > pjxmin){
        pjymax = xReady * valorPendiente + EnemigoPosition->getPosY();
        pjymin = EnemigoPosition->getPosY() - (pjymax - EnemigoPosition->getPosY());
        
        if(posObjY > pjymin && posObjY < pjymax)
            inSight = true;
    
    }else{  //Segunda parte del area, anyadido.

        if(lastFacedDir){
            if (posObjX >= pjxmax && posObjX < pjxmax2){  
                if(posObjX < (pjxmax+xprima1)){
                    pjymax = -(posObjX - (pjxmax + xprima1)) * pend1 + EnemigoPosition->getPosY() + yprima;
                    pjymin = EnemigoPosition->getPosY() - (pjymax - EnemigoPosition->getPosY());                    
                }else{
                    pjymax = -(posObjX - (pjxmax + xprima)) * pend2 + EnemigoPosition->getPosY();
                    pjymin = EnemigoPosition->getPosY() - (pjymax - EnemigoPosition->getPosY());
                }
                
                if(posObjY < pjymax && posObjY > pjymin)
                    inSight = true;
                }
        }else{
            if(posObjX > pjxmin2 && posObjX <= pjxmin){
                if(posObjX > (pjxmin-xprima1)){
                    pjymax = (posObjX - (pjxmin - xprima1)) * pend1 + EnemigoPosition->getPosY() + yprima;
                    pjymin = EnemigoPosition->getPosY() - (pjymax-EnemigoPosition->getPosY());                    
                }else{
                    pjymax = (posObjX - (pjxmin - xprima)) * pend2 + EnemigoPosition->getPosY();
                    pjymin = EnemigoPosition->getPosY() - (pjymax-EnemigoPosition->getPosY());
                }
                
                if(posObjY < pjymax && posObjY > pjymin)
                    inSight = true;

            }
        }
    }

    return inSight;
}

/** FUNCION PARA SABER SI UN DETERMINADO GAMEOBJECT HA SIDO INCLUIDO EN EL VECTOR DE VISTOS DE ESTE ENEMIGO 
DEVUELVE TRUE SI SE ENCUENTRA DENTRO DEL VECTOR **/
bool Enemigo::see(GameObject* o){
    bool seeing = false;
    for(int i = 0; i < vistos.size(); i++){
        if(vistos[i] == o){
            seeing = true;
        }
    }
    return seeing;
}

/* Para actualizar en un momento dado lo que esta viendo el enemigo */
void Enemigo::actualizarVistos()
{
    /* VISTA ENEMIGO */
    /* COMPROBAMOS GAMEOBJECTS DENTRO DE LA VISTA */
    vistos.clear();

        for(int i = 0; i < ent->getSize(); i++){
            if(checkInSight(ent->getGameObject(i)->getPosition())){
                vistos.push_back(ent->getGameObject(i));
            }
        }
}

/**
==============================================
A PARTIR DE AQUI VAN TODOS LOS GETS Y LOS SETS
==============================================
**/
void* Enemigo::getNode()
{
    return enemigo;
}


glm::f32 Enemigo::getVelocidad()
{
    return VELOCIDAD_ENEMIGO;
}

glm::f32 Enemigo::getSed()
{
    return sed;
}

glm::f32 Enemigo::getSalud()
{
    return salud;
}

glm::f32 Enemigo::getHambre()
{
    return hambre;
}

vector<NodoGrafo*> Enemigo::getPosicion()
{
    return patrulla;
}

const glm::f32 Enemigo::getVelNormal()
{
    return VELOCIDAD_NORMAL;
}

int Enemigo::getTipo()
{
    return tipo;
}

int Enemigo::getClaseEnemigo()
{
    return claseEnemigo;
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
bool Enemigo::getLastFaceDir()
{
    return lastFacedDir;
}

b2Body* Enemigo::getBody()
{
    return Body;
}

b2Vec2 Enemigo::getVelocidad2d()
{
    return velocidad2d;
}

bool Enemigo::getUltDirecVisto()
{
    return direccVistoUlt;
}

int Enemigo::getPosCombate()
{
    return pos_combate;
}

bool Enemigo::getCombate()
{
    return combate;
}

int Enemigo::getOrden()
{
    return orden;
}

bool Enemigo::getDisparo()
{
    return disparo;
}

Proyectil* Enemigo::getProyectil()
{
    return proyectil;
}


void Enemigo::setSalud(glm::f32 s)
{
    salud+=s;
}

void Enemigo::setEnergia(glm::f32 e)
{
    energia=e;
}

void Enemigo::setHambre(glm::f32 h)
{
    hambre=h;
}

void Enemigo::setVelocidad(glm::f32 v)
{
    //VELOCIDAD_ENEMIGO=v;

    velocidad2d.x = v;
}

void Enemigo::setSed(glm::f32 se)
{
    sed=se;
}

void Enemigo::setPosition(Posicion* position)
{
    fachada->setPosicion(enemigo,position);
    EnemigoPosition = position;
}

void Enemigo::setVelHambre(glm::f32 v)
{
    velHambre = v;
}

void Enemigo::setVelSed(glm::f32 v)
{
    velSed = v;
}

void Enemigo::setLastFacedDir(bool dirx){
    lastFacedDir = dirx;
}

void Enemigo::setUltDirecVisto(bool v)
{
    direccVistoUlt = v;
}

void Enemigo::setCombate(bool b)
{
    combate = b;
}

void Enemigo::setPosCombate(int n)
{
    pos_combate = n;
}

void Enemigo::setOrden(int o)
{
    orden = o;
}

void Enemigo::setDisparo(bool d)
{
    disparo = d;
}


Enemigo::~Enemigo()
{
    //dtor
     vistos.clear();
}
