#include "../headerfiles/Enemigo.h"
#include "../headerfiles/Blackboard.h"
#include "../headerfiles/Proyectil.h"


/**

 CONSTRUCTOR DE ENEMIGO
 Parametros : Objetos Irrlicht, vector con posiciones de la patrulla
*/
Enemigo::Enemigo(IrrlichtDevice *dev, ISceneManager* smgr, vector<Posicion*> pos, float xlength, float pendValue, const Entorno* e, Blackboard *b) 
: enemigo(nullptr), env(nullptr), driver(nullptr), ent(e), board(nullptr), proyectil(nullptr), alActivar(nullptr)
{
    GameObject::setTipo(ENEMY);
    Fachada* fachada=fachada->getInstance();
	enemigo = fachada->addCube(pos[0]->getPosX(),pos[0]->getPosY(),pos[0]->getPosZ(),false);

    if (enemigo) /** SI HEMOS CREADO EL CUBO **/
	{  
         driver = fachada->getDriver();
        fachada ->setMaterial(enemigo,"resources/verde.jpg");

        EnemigoPosition = fachada->getPosicion(enemigo);


	}

    board = b;                                             // Guardamos la blackboard 

    env = dev->getGUIEnvironment();

    /* Valores por defecto para los parametros para el rango de vision del enemigo */
    lastFacedDir = false;
    visionXmax = xlength;
    valorPendiente = pendValue;
    visto = false;
    direccVistoUlt = false;

    patrulla = pos;
    /*
    nodos = board->getNodosGrafo();              // Obtenemos todos los nodos del grafo
    /* COMPROBAMOS QUE LAS POSICIONES DE PATRULLA COINCIDEN CON LOS NODOS DEL GRAFO */
 /*   for(int i=0; i<pos.size();i++)
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
    saltando = false;
    inv = true;

    /* Pathfinding */
    vuelta = false;
    interrupcion = false;


}

/* Update para todos los enemigos*/
void Enemigo::update(Posicion* Posprota)
{

    if(salud<0)
    {
        fachada->destruirObjeto(enemigo);
    }

    if(enemigo!=nullptr)  // Solo si existe el enemigo hacemos su update
    { 
        actualizarSed();

        //COMPROBAMOS GAMEOBJECTS DENTRO DE LA VISTA
        vistos.clear();

        for(int i = 0; i < ent->getSize(); i++){
            if(checkInSight(ent->getGameObject(i)->getPosition())){
                vistos.push_back(ent->getGameObject(i));
            }
        }

        // COMPROBAMOS SI HEMOS VISTO AL PROTAGONISTA 
        if(checkInSight(Posprota) && inv==false){              
            visto = true;
             fachada->setMaterial(enemigo,"resources/activada.jpeg");  
             contador = 0;
            
        }else{
            if(recordarProta()==false)
            {
                visto = false;
                fachada->setMaterial(enemigo,"resources/verde.jpg");
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
                proyectil = new Proyectil(fachada->getDevice(),fachada->getScene(),this);
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
FUNCION PARA ACTUALIZAR EL ESTADO DE SED DEL ENEMIGO
**/

void Enemigo::actualizarSed()
{
     sed+=velSed*frameDeltaTime;

     //cout<<round(sed)<<endl;

}

void Enemigo::updateTiempo(const f32 Time)
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
/* Funcion para cambiar al lado contrario a donde estaba mirando el enemigo en ese momento */
void Enemigo::changeLastFaceDir()
{
    if(lastFacedDir==true)
    {
        lastFacedDir = false;
    }
    else
    {
        lastFacedDir = true;
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


f32 Enemigo::getVelocidad()
{
    return VELOCIDAD_ENEMIGO;
}

f32 Enemigo::getSed()
{
    return sed;
}

f32 Enemigo::getSalud()
{
    return salud;
}

vector<Posicion*> Enemigo::getPosicion()
{
    return patrulla;
}

const f32 Enemigo::getVelNormal()
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

IVideoDriver* Enemigo::getDriver()
{
    return driver;
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

Objeto* Enemigo::getAlarmaActivar()
{
    return alActivar;
}

bool Enemigo::getSaltando()
{
    return saltando;
}

bool Enemigo::getVuelta()
{
    return vuelta;
}

bool Enemigo::getInterrumpido()
{
    return interrupcion;
}


void Enemigo::setSalud(f32 s)
{
    salud+=s;
}

void Enemigo::setEnergia(f32 e)
{
    energia=e;
}

void Enemigo::setVelocidad(f32 v)
{
    //VELOCIDAD_ENEMIGO=v;

    velocidad2d.x = v;
}

void Enemigo::setSed(f32 se)
{
    sed=se;
}

void Enemigo::setPosition(Posicion* position)
{
    fachada->setPosicion(enemigo,position);
    EnemigoPosition = position;
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

void Enemigo::setAlarmaActivar(Objeto* a)
{
    alActivar = a;
}

void Enemigo::setSaltando(bool s)
{
    saltando = s;
}

void Enemigo::setInvisible()
{
    if(inv==false)
    {
        inv = true;
    }
    else
    {
        inv = false;
    }
}

void Enemigo::setVuelta(bool v)
{
    vuelta = v;
}

void Enemigo::setInterrumpido(bool i)
{
    interrupcion = i;
}


Enemigo::~Enemigo()
{
    //dtor
     vistos.clear();
}
