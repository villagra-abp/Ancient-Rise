#include "../headerfiles/Enemigo.h"
#include "../headerfiles/Blackboard.h"
#include "../headerfiles/Proyectil.h"


/**

 CONSTRUCTOR DE ENEMIGO
 Parametros : Objetos Irrlicht, vector con posiciones de la patrulla
*/
Enemigo::Enemigo(vector<Posicion*> pos, float xlength, float pendValue, const Entorno* e, Blackboard *b) : enemigo(nullptr), ent(e), board(nullptr), proyectil(nullptr), alActivar(nullptr),
enemigoObjeto(nullptr)
{
    GameObject::setTipo(ENEMY);
    Fachada* fachada=fachada->getInstance();

    enemigoObjeto = fachada->addMalla(pos[0]->getPosX(),pos[0]->getPosY(),pos[0]->getPosZ(), "resources/Protagonista/personaje.obj");
    enemigo = enemigoObjeto;

    if (enemigo) /** SI HEMOS CREADO EL CUBO **/
	{  
        Posicion* pos= new Posicion(pos[0].getPosX(),pos[0].getPosY(),pos[0].getPosZ());
        EnemigoPosition = pos;
	}

    energy=fachada->addMalla(-170,15,0,"resources/Hud/cajitaobj.obj");
    life=fachada->addMalla(-170,25,0,"resources/Hud/cajaColor.obj");
    flecha1=fachada->addMalla(-160,8,0,"resources/flecha.obj");
    flecha0=fachada->addMalla(-170,8,0,"resources/flecha.obj");
    Posicion escalar(0.f,0.f,.0f);
    fachada->setScala(flecha1,&escalar);
    fachada->rotObj(flecha1, 1, 0, 0, -45);
    fachada->setScala(flecha0,&escalar);
    fachada->rotObj(flecha0, 1, 0, 0, -45);
    fachada->rotObj(flecha0, 0, 1, 0, -3);

    board = b;                                             // Guardamos la blackboard 

    /* Valores por defecto para los parametros para el rango de vision del enemigo */
    lastFacedDir = false;
    visionXmax = xlength;
    valorPendiente = pendValue;
    visto = false;
    direccVistoUlt = false;

    patrulla = pos;


    /* Valores por defecto para los parametros para el combate del enemigo */
    combate = false;
    disparo = false;
    pos_combate = 2; 
    contador = 0;
    memoria = false;
    orden = 0;                                            // Ninguna orden recibida
    saltando = false;
    inv = true;
    recargandoEnergia = false;

    /* Pathfinding */
    vuelta = false;
    interrupcion = false;

    /* Establecemos su velocidad de movimiento estandar la cual no consume energia */
    velocidad2d.x = VELOCIDAD_NORMAL;

}

/* Update para todos los enemigos*/
void Enemigo::update(Posicion* Posprota)
{   
    if(salud<=0) // Enemigo Muerto
    {   
        //cout<<"Muerto"<<endl;
        // Eleminamos el enemigo(parcialmente)

        fachada->destruirObjeto(enemigo);
        enemigo = nullptr;

        // Elminamos su hud
        fachada->destruirObjeto(life);
        life = nullptr;
        fachada->destruirObjeto(energy);
        energy = nullptr;
        fachada->destruirObjeto(flecha0);
        flecha0= nullptr;
        fachada->destruirObjeto(flecha1);
        flecha1 = nullptr;

        //Eliminamos su body
        Body->GetWorld()->DestroyBody(Body);
    } 

    if(enemigo!=nullptr)  // Solo si existe el enemigo hacemos su update
    { 
        hud();

        actualizarSed();
        //COMPROBAMOS GAMEOBJECTS DENTRO DE LA VISTA
        vistos.clear();

        for(int i = 0; i < ent->getSize(); i++){
            if(checkInSight(ent->getGameObject(i)->getPosition())){
                vistos.push_back(ent->getGameObject(i));
                
            }
        }

        /* Animaciones */
        if(lastFacedDir==true) 
        {
            if(velocidad2d.x <=VELOCIDAD_NORMAL)  // Andar 
            {
                enemigoObjeto = fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/marchaE/marchaE.txt", enemigoObjeto);
            }
            else // Correr
            {
                enemigoObjeto = fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/correrE/correrE.txt", enemigoObjeto);
            }

            enemigo = enemigoObjeto;
            fachada->setRotObj(enemigoObjeto, 0, 1, 0, -90);

        }
        else
        {
            if(velocidad2d.x <=VELOCIDAD_NORMAL)
            {
                enemigoObjeto = fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/marchaE/marchaE.txt", enemigoObjeto);
            }
            else
            {
                enemigoObjeto = fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/correrE/correrE.txt", enemigoObjeto);
            }

            enemigo = enemigoObjeto;
            fachada->setRotObj(enemigoObjeto, 0, 1, 0, +90);
        }

         //cout<<"llego2.8"<<endl;
        // COMPROBAMOS SI HEMOS VISTO AL PROTAGONISTA 
        if(checkInSight(Posprota) && inv==false)
        {              
            visto = true; 
             contador = 0;
            
        }else{
            if(recordarProta()==false)
            {
                visto = false;
            }
        }
        
        /* COMBATE MELE */
            

        /* COMBATE DISTANCIA */
        /*if(tipo==2) // Enemigo tipo distancia
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
        */
        
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

    //Para depuracion
    float ymaxABS;
    float yminABS;

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

    //fachada->setPosicion( dep1, EnemigoPosition);
    //std::cout << enemigo->getPosition().X << endl;

    //Depuracion
    //ymaxABS = visionXmax * valorPendiente;
    //yminABS = EnemigoPosition->getPosY() - (ymaxABS - EnemigoPosition->getPosY());

    if(lastFacedDir){   //Mira hacia derecha
        pjxmin = EnemigoPosition->getPosX();
        pjxmax = EnemigoPosition->getPosX() + visionXmax;
        pjxmax2 = pjxmax + xprima;
        xReady = posObjX - pjxmin;

        //Depuracion
        Posicion depurar(pjxmax, EnemigoPosition->getPosY(), 30.f);
        //fachada->setPosicion( dep2, &depurar);
        
        //Depuracion
        Posicion depurar2(pjxmax, ymaxABS, 30.f);
        //fachada->setPosicion( dep3, &depurar2);
        Posicion depurar3(pjxmax, yminABS, 30.f);
        //fachada->setPosicion( dep4, &depurar3);

    }else{              //Mira hacia izquierda
        pjxmin = EnemigoPosition->getPosX() - visionXmax;
        pjxmax = EnemigoPosition->getPosX();
        pjxmin2 = pjxmin - xprima;
        xReady = -(posObjX - pjxmax);

       //Depuracion
        Posicion depurar(pjxmin, EnemigoPosition->getPosY(), 30.f);
        //fachada->setPosicion( dep2, &depurar);
        
        //Depuracion
        Posicion depurar2(pjxmin, ymaxABS, 30.f);
        //fachada->setPosicion( dep3, &depurar2);
        Posicion depurar3(pjxmin, yminABS, 30.f);
        //fachada->setPosicion( dep4, &depurar3);
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
/* FUncion para mostrar el hud de los enemigos */
void Enemigo::hud()
{
    Posicion posicionHUD(EnemigoPosition->getPosX(), EnemigoPosition->getPosY(),0.f);
    posicionHUD.setPosX(posicionHUD.getPosX()+5);

    /* Posicion de las flechas del combate del enemigo */
    if(pos_combate==2)
    {
        posicionHUD.setPosY(posicionHUD.getPosY()+5);
    }
            
    if(pos_combate==1)
    {
        posicionHUD.setPosY(posicionHUD.getPosY()+10);
    }
            
    if(pos_combate==3)
    {
        posicionHUD.setPosY(posicionHUD.getPosY());
    }

    fachada->setPosicion(flecha1,&posicionHUD);
    posicionHUD.setPosX(posicionHUD.getPosX()-10);
    fachada->setPosicion(flecha0,&posicionHUD);

    if(pos_combate==1){
        posicionHUD.setPosY(posicionHUD.getPosY()-5);
    }
            
    if(pos_combate==3){
        posicionHUD.setPosY(posicionHUD.getPosY()+5);
    }
        
    Posicion escalaFlechaCorta(0,0.f,0.f);
    Posicion escalaFlechaLarga(0.1,.1f,0.1f);
    Posicion escalaFlechaLarga2(0.2,.1f,0.1f);
        
    if(lastFacedDir==true &&combate){
        fachada->setScala(flecha0,&escalaFlechaCorta);
    if(!ataca){
        fachada->setScala(flecha1,&escalaFlechaLarga);
    }else
        fachada->setScala(flecha1,&escalaFlechaLarga2);    
        }

    if(lastFacedDir==false  &&combate){
        fachada->setScala(flecha1,&escalaFlechaCorta);
        if(!ataca){
                fachada->setScala(flecha0,&escalaFlechaLarga);
            }else
                fachada->setScala(flecha0,&escalaFlechaLarga2);
        }
        if(!combate){
            fachada->setScala(flecha1,&escalaFlechaCorta);
            fachada->setScala(flecha0,&escalaFlechaCorta);
            
        }

    if(lastFacedDir==true)
    {    
        posicionHUD.setPosX(posicionHUD.getPosX()+6);
    }
    else
    {
        posicionHUD.setPosX(posicionHUD.getPosX()+4);
    }
    posicionHUD.setPosY(posicionHUD.getPosY()+10);
    fachada->setPosicion(energy,&posicionHUD);
    posicionHUD.setPosY(posicionHUD.getPosY()+3);
    fachada->setPosicion(life,&posicionHUD);
    Posicion escalaEnergy(energia/20,1.5f,0.01f);
    Posicion escalaLife(salud/40,1.5f,0.01f);
    fachada->setScala(energy,&escalaEnergy);
    fachada->setScala(life,&escalaLife);
}

void Enemigo::hudCombate()
{
    
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

FObjeto* Enemigo::getFObjeto()
{
    return enemigoObjeto;
}

glm::f32 Enemigo::getSed()
{
    return sed;
}

glm::f32 Enemigo::getSalud()
{
    return salud;
}

vector<Posicion*> Enemigo::getPosicion()
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

glm::f32 Enemigo::getVelRapida()
{
    return VELOCIDAD_RAPIDA;
}

glm::f32 Enemigo::getEnergia()
{
    return energia;
}

bool Enemigo::getRecargandoEnerg()
{
    return recargandoEnergia;
}


void Enemigo::setSalud(glm::f32 s)
{
    salud+=s;
}

void Enemigo::setEnergia(glm::f32 e)
{
    energia=e;
}

void Enemigo::setVelocidad(glm::f32 v)
{
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

void Enemigo::setNode(FObjeto* node)
{
    enemigoObjeto = node;
}


Enemigo::~Enemigo()
{
    //dtor
     vistos.clear();

     fachada->destruirObjeto(enemigo);
     fachada->destruirObjeto(life);
      fachada->destruirObjeto(energy);

        fachada->destruirObjeto(flecha0);

        fachada->destruirObjeto(flecha1);

}
