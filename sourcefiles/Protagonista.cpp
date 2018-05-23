#include "../headerfiles/Protagonista.h"
#include "../headerfiles/Blackboard.h"
#define SCALE 30.0f

static Protagonista* instance = NULL;


Protagonista::Protagonista():energy(nullptr), life(nullptr), Body(nullptr), rec(nullptr), flecha0(nullptr), flecha1(nullptr), sonido(nullptr),
protaPosition(nullptr), enemigoPosition(nullptr), comidaPosition(nullptr), trampaPosition(nullptr), protaObjeto(nullptr)
{
    GameObject::setTipo(PROTA);

    protaObjeto = fachada->crearProta();

    protaObjeto = fachada->addAnimacion(0, 0,1000, "resources/Animaciones/reposo1/reposo1.txt", protaObjeto);
    rec = protaObjeto;
    
    Posicion escala(2.f,2.f,2.f);
    fachada->setScala((void*)protaObjeto,&escala);
		
    fachada->rotObj(protaObjeto, 0, 1, 0, -90);
        
    flecha1=fachada->addMalla(-160,8,0,"resources/flecha.obj");
    flecha0=fachada->addMalla(-170,8,0,"resources/flecha.obj");
    Posicion escalar(0.f,0.f,.0f);
    fachada->setScala(flecha1,&escalar);
    fachada->rotObj(flecha1, 1, 0, 0, -45);
    fachada->setScala(flecha0,&escalar);
    fachada->rotObj(flecha0, 1, 0, 0, -45);
    fachada->rotObj(flecha0, 0, 1, 0, -3);

    /* Estadisticas del prota */
    energia=ENERGIA_MAXIMA;
    vida=VIDA_MAXIMA;
    saltando=false;
    sigilo=false;
    correr=false;
    estaEnSuelo=false;
    estaCayendo=true;
    direccion=1;

    combate = false;
    pos_combate = 2; 

    //SONIDOS
    sonido = GestorSonido::getInstance();

    Sonido* aux;
    //Ataque
    aux = sonido->create2DSound(sonido->SOUND_PROTA_ATAQUE1);
    ataqueS.push_back(aux);
    aux = sonido->create2DSound(sonido->SOUND_PROTA_ATAQUE2);
    ataqueS.push_back(aux);
    aux = sonido->create2DSound(sonido->SOUND_PROTA_ATAQUE3);
    ataqueS.push_back(aux);
    //Dolor
    aux = sonido->create2DSound(sonido->SOUND_PROTA_DOLOR1);
    dolor.push_back(aux);
    aux = sonido->create2DSound(sonido->SOUND_PROTA_DOLOR2);
    dolor.push_back(aux);
    aux = sonido->create2DSound(sonido->SOUND_PROTA_DOLOR3);
    dolor.push_back(aux);
    //DolorEnemigo
    aux = sonido->create2DSound(sonido->SOUND_ENEM_DOLOR1);
    dolorEnem.push_back(aux);
    aux = sonido->create2DSound(sonido->SOUND_ENEM_DOLOR2);
    dolorEnem.push_back(aux);
    aux = sonido->create2DSound(sonido->SOUND_ENEM_DOLOR3);
    dolorEnem.push_back(aux);
   
    //Otros
    comer = sonido->create2DSound(sonido->SOUND_PROTA_COMER);
    beber = sonido->create2DSound(sonido->SOUND_PROTA_BEBER);
    pasos = sonido->create2DSound(sonido->SOUND_PROTA_PASOS);
    corte = sonido->create2DSound(sonido->SOUND_AMBIENT_CORTECARNE);
    protaPosition=fachada->getPosicion(rec);


    /* Animaciones */
    cambioAnimacion = false;
    tipoSalto = 1;
    
}



//Con esto hacemos que sea singleton. Solo se puede crear el motorgrafico llamando a getInstance. Esta devuelve el motor si ya estaba creado, y sino lo crea
//Parametros: h-> Alto de la ventana, w-> Ancho de la ventana, fullscreen-> si será pantalla completa o no
Protagonista* Protagonista::getInstance() 
{
    if (instance == NULL) instance = new Protagonista();
    return (instance);
}


/* Funcion para hacer el update del protagonista */
void Protagonista::update(Blackboard* b)
{   

    timeAtq = relojAtq.getElapsedTime().asSeconds();
    if( ataca == true && timeAtq>=0.5)       // PROTA EN COMBATE Y ATACANDO
    {   
        if(pos_combate==1)
        {
            protaObjeto = fachada->addAnimacion(0, 0, 1000, "resources/Animaciones/ataquearriba/ataquearriba.txt", protaObjeto);
            rec = protaObjeto;
        }

        relojAtq.restart();
        enemB = b->getEnemB();

        for(int i=0; i<enemB.size();i++)
        {   
            if(enemB[i]!=nullptr)
            {
                comprobarColision(enemB[i]);
            }
        }
    }

    if(direccion==2) // Sin movimiento
    {
        if(combate == false)
        {
            /* Animacion de estar quieto */
            protaObjeto = fachada->addAnimacion(0, 0, 1000, "resources/Animaciones/reposo1/reposo1.txt", protaObjeto);
            rec = protaObjeto;
        }
        else
        {
            if(ataca==false)
            {
                /* Animacion de estar quieto */
                protaObjeto = fachada->addAnimacion(0, 0, 1000, "resources/Animaciones/reposo1/reposo1.txt", protaObjeto);
                rec = protaObjeto;
            }
        }
    }

    if(saltando==true)
    {
        b2Vec2 velocidad=Body->GetLinearVelocity();
        /* Animacion salto */
        protaObjeto = fachada->addAnimacion(0, 0, 1000, "resources/Animaciones/saltoadelante/saltoadelante.txt", protaObjeto);
        rec = protaObjeto;

        /* Rotamos en funcion de adonde mire */
        if(direccion==0)
        {
            fachada->setRotObj(protaObjeto, 0, 1, 0, +90); 
        }
        else
        {
            fachada->setRotObj(protaObjeto, 0, 1, 0, -90); 
        }

        if(velocidad.y<0)
        {
            if(contador==0)
            {
                tiempoSalto.restart();
                contador = contador +1;
            }

            int time = tiempoSalto.getElapsedTime().asSeconds();  // OBTENEMOS SU DURACION EN SEGUNDOS

              saltando = false;
        }
    }

}

/**
FUNCION PARA crear el objeto dinamico
**/
void Protagonista::CreateBox(b2World& world, float X, float Y)
{
    BodyDef.position = b2Vec2(X+4, Y+4);
    BodyDef.type = b2_dynamicBody;
    Body = world.CreateBody(&BodyDef);
    Shape.SetAsBox((8.f/2), (10.f/2));
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.5f;
    FixtureDef.friction = 0.2f;
    FixtureDef.shape = &Shape;
    FixtureDef.isSensor = false;
    FixtureDef.filter.groupIndex = GROUP_PLAYER;
    Body->CreateFixture(&FixtureDef);
    Body->SetUserData( rec );
}

/**
FUNCION PARA actualizar el cuerpo
**/
void Protagonista::updateBody(b2World& world)
{
    if(Body->GetPosition().y<-185){
        //cout<<Body->GetPosition().y<<endl;
        quitarVida(100);
    }
	
    protaPosition->setPosX(Body->GetPosition().x);
    protaPosition->setPosY(Body->GetPosition().y);
    
    fachada->setPosicion(rec,protaPosition);
    
    
    protaPosition->setPosX(protaPosition->getPosX()+5);
    if(pos_combate==2){
        protaPosition->setPosY(protaPosition->getPosY()+5);
    }
        
    if(pos_combate==1)
    {
        protaPosition->setPosY(protaPosition->getPosY()+10);
    }
        
    if(pos_combate==3){
        protaPosition->setPosY(protaPosition->getPosY());
    }
    fachada->setPosicion(flecha1,protaPosition);
    protaPosition->setPosX(protaPosition->getPosX()-10);
    fachada->setPosicion(flecha0,protaPosition);
    if(pos_combate==1){
        protaPosition->setPosY(protaPosition->getPosY()-5);
    }
        
    if(pos_combate==3){
        protaPosition->setPosY(protaPosition->getPosY()+5);
    }
    
    Posicion escalaFlechaCorta(0,0.f,0.f);
    Posicion escalaFlechaLarga(0.1,.1f,0.1f);
    Posicion escalaFlechaLarga2(0.2,.1f,0.1f);
    
    if(direccion==1&&combate){
        fachada->setScala(flecha0,&escalaFlechaCorta);
        if(!ataca){
            fachada->setScala(flecha1,&escalaFlechaLarga);
        }else
            fachada->setScala(flecha1,&escalaFlechaLarga2);
        
    }
    if(direccion==0&&combate){
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
    
}

/**
FUNCION PARA CONTROLAR EL ATAQUE DEL PROTA
**/
void Protagonista::ataque(EnemigoBasico* e)
{
    sonido->playRandomSound(ataqueS);
    if(pos_combate != e->getPosCombate() || e->getCombate()!=true)
    {
        bool flag = sonido->playSound(corte);
        if(flag) corte->getCanal()->setGrupoCanales(sonido->getGrupoAmbiente());
        int aux = sonido->playRandomSound(dolorEnem);
        if(aux != -1) dolorEnem[aux]->getCanal()->setGrupoCanales(sonido->getGrupoVoces());
        e->setSalud(-20.f);
    }
    
}

b2Body* Protagonista::getBody(){
    
    return Body;
}

/**
FUNCION PARA CONTROLAR EL MOVIMIENTO DEL PROTA
**/
void Protagonista::movimiento(const glm::f32 Time)
{
    b2Vec2 velo=Body->GetLinearVelocity();

    if(direccion==0) // MOVIMIENTO HACIA LA IZQUIERDA
    {
        if(sigilo==true) // Sigilo
        {
            velo.x=-10.f;
            Body->SetLinearVelocity(velo);
        }else if(correr==true && velo.y>=-4 && velo.y<4) // Corriendo
        {
            setEnergia(-0.3f,0.1f);
            Body->ApplyForceToCenter(b2Vec2(-3500.f,0.f),true);

            /* Animacion de correr */
            protaObjeto = fachada->addAnimacion(0, 0, 1000, "resources/Animaciones/correr/correr.txt", protaObjeto);
            rec = protaObjeto;
            fachada->setRotObj(protaObjeto, 0, 1, 0, +90);

            
        }else // Andar
        {
            /* Animacion de andar */
            if(saltando==false)
            {
                if(combate==false)
                {
                    protaObjeto = fachada->addAnimacion(0, 0, 1000, "resources/Animaciones/marcha5/marcha5.txt", protaObjeto);
                    velo.x=-25.f;
                }
                else
                {
                    protaObjeto = fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/movercombate/movercombate.txt", protaObjeto);
                    velo.x=-10.f;
                }
            }

            Body->SetLinearVelocity(velo);
            rec = protaObjeto;
            fachada->setRotObj(protaObjeto, 0, 1, 0, +90);

        }

    }
    else       
    {
        if(direccion==1) //MOVIMIENTO HACIA LA DERECHA
        {
             if(sigilo==true)
                {
                    velo.x=10.f;
                    //Body->ApplyForceToCenter(b2Vec2(35.f,0.f),true);
                   Body->SetLinearVelocity(velo);
                }else if(correr==true && velo.y>=-4 && velo.y<4){
                    setEnergia(-0.3f,0.1f);
                    Body->ApplyForceToCenter(b2Vec2(3500.f,0.f),true);

                    /* Animacion de correr */
                    protaObjeto = fachada->addAnimacion(0, 0, 1000, "resources/Animaciones/correr/correr.txt", protaObjeto);
                    rec = protaObjeto;
                    fachada->setRotObj(protaObjeto, 0, 1, 0, -90);
              
                }
                else{
                        if(saltando==false)
                        {
                            if(combate==false)
                            {
                                protaObjeto = fachada->addAnimacion(0, 0, 1000, "resources/Animaciones/marcha5/marcha5.txt", protaObjeto);
                                velo.x=25.f;
                            }
                            else
                            {
                                protaObjeto = fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/movercombate/movercombate.txt", protaObjeto);
                                velo.x=10.f;
                            }
                        }

                        Body->SetLinearVelocity(velo);
                        rec = protaObjeto;
                        fachada->setRotObj(protaObjeto, 0, 1, 0, -90);
                }
        }
    }

}
/**
FUNCION PARA COMPROBAR LAS COLISIONES CON ENEMIGOS
**/
void Protagonista::comprobarColision(EnemigoBasico *e)
{   
    enemigoPosition=e->getPosition();
    int distanciaEnemigo = protaPosition->getPosX() - enemigoPosition->getPosX();

    float enemigoPosY = enemigoPosition->getPosY();

      /* Posicion del prota en y */
    float protaPosY=protaPosition->getPosY();

    if(abs(distanciaEnemigo)<20 && protaPosY>enemigoPosY-10  && protaPosY<enemigoPosY+10 )   // Distancia para poder atacar
    {   
        ataque(e);
    }
    
}

/**
ESTA FUNCION ES PARA QUE NO PETE EL CONTACTLISTENER PREGUNTAR RUBEN
**/
void Protagonista::comprobarColision(Enemigo *e)
{   /*
    enemigoPosition=e->getNode()->getPosition();
    int distanciaEnemigo = protaPosition.X - enemigoPosition.X;

    if(abs(distanciaEnemigo)<25)   // Distancia para poder atacar
    {   
        ataque(e);
    }
    */
}

/**
FUNCION PARA COMPROBAR LAS COLISIONES CON COMIDA
**/
void Protagonista::comprobarColision(Objeto *comida)
{
    /* Posicion del prota */
    float protaPosX=protaPosition->getPosX();
    float protaPosY=protaPosition->getPosY();
    
    /* Posicion de la comida */
    float comidaPosX=comida->getPosition()->getPosX();
    float comidaPosY=comida->getPosition()->getPosY();
    
    if(protaPosY<comidaPosY+12 && protaPosY>comidaPosY-12)
    {
        if(protaPosX>comidaPosX-3 && protaPosX<comidaPosX+3)
        {
            if(vida<VIDA_MAXIMA) // Solo lo recogemos si nos falta vida
            {
                vida+=20;
                if(vida>VIDA_MAXIMA)
                {
                    vida=VIDA_MAXIMA;
                }

                comida->setRecogido(true);
                bool flag = sonido->playSound(comer);
                if(flag) comer->getCanal()->setGrupoCanales(sonido->getGrupoAmbiente());
            }
        }
    }
    
}

void Protagonista::comprobarColision(Bebida *bebida)
{
 /* Posicion bebida */
    float bebidaPosX=bebida->getPosition()->getPosX();
    float bebidaPosY=bebida->getPosition()->getPosY();

    /* Posicion prota*/
    float protaPosX=protaPosition->getPosX();
    float protaPosY=protaPosition->getPosY();

    if(protaPosY<bebidaPosY+12 && protaPosY>bebidaPosY-12)
    {
        if(protaPosX>bebidaPosX-3 && protaPosX<bebidaPosX+3)
        {
            if(energia<ENERGIA_MAXIMA)
            {
                energia+=40;
                if(energia>ENERGIA_MAXIMA)
                {
                    energia=ENERGIA_MAXIMA;
                }

                bebida->setRecogido(true);
                bool flag = sonido->playSound(beber);
                if(flag) beber->getCanal()->setGrupoCanales(sonido->getGrupoAmbiente());
            }
        }
    }

    
}

void Protagonista::comprobarColision(Trampa *trampa)
{
    /* Posicion del prota */
    float protaPosX=protaPosition->getPosX();
    float protaPosY=protaPosition->getPosY();
    
    /* Posicion de la trampa */
    float tramPosX=trampa->getPosition()->getPosX();
    float tramPosY=trampa->getPosition()->getPosY();

    if(protaPosY<tramPosY+11 && protaPosY>tramPosY-11)
    {
        if(protaPosX>tramPosX-7 && protaPosX<tramPosX+4)
        {
            quitarVida(0.4f);
        }
    }
    
    
}
void Protagonista::comprobarColision(Palanca *palanca)
{
    
    /* Posicion del prota */
    float protaPosX=protaPosition->getPosX();
    float protaPosY=protaPosition->getPosY();
    
    /* Posicion de la palanca*/
    float palPosX=palanca->getPosition()->getPosX();
    float palPosY=palanca->getPosition()->getPosY();

    if(protaPosY<palPosY+11 && protaPosY>palPosY-11)
    {
        if(protaPosX>palPosX-7 && protaPosX<palPosX+9)
        {
            
            fachada->activarPalanca(true);
        }
        else
        {
            fachada->activarPalanca(false);
            
        }
    }
     //cout<<fachada->getPalancaActiva()<<endl;
   
}
/*
FUNCION PARA COMPROBAR LA POSICION DE COMBATE DEL PROTA Y CAMBIAR LA POS EN Y 
DEL PROTA 
*/
void Protagonista::checkPosCombate()
{
    
    if(pos_combate == 1)    // ARRIBA
    {
        protaPosition->setPosY(protaPosition->getPosY()+5);
        protaPosition->setPosY(protaPosition->getPosY()-5);
    }
    else
    {
        if(pos_combate == 3) // ABAJO
        {
            protaPosition->setPosY(protaPosition->getPosY()-5);
            protaPosition->setPosY(protaPosition->getPosY()+5);
        }
        else        // CENTRO
        {
            protaPosition->setPosY(protaPosition->getPosY());
        }
    }

}

/**
FUNCION PARA COMPROBAR LA VIDA DEL PROTA
**/
bool Protagonista::checkVida()
{
    if(vida<=0)
    {
        return false;
    }else
    {
        return true;
    }
}

void Protagonista::startClock()
{
    if(contAtq == 0)
    {
        relojAtq.restart();
        contAtq = contAtq+1;
    }
}

/*
FUNCION PARA CAMBIAR LA POS DE COMBATE DEL PROTA
*/
void Protagonista::setPosCombate(int n)
{
    pos_combate = n;
}
/**
FUNCION PARA RECUPERAR LA VIDA DEL PROTA
**/
void Protagonista::setVida(glm::f32 cantidad,const glm::f32 Time)
{
    //std::cout<<Time<<endl;
    if(vida>0 || vida<100)
        vida+=cantidad* Time;
    if(vida<0){
        vida=0;
    }else if(vida>100){
        vida=100;
    }

}

void Protagonista::setLife(glm::f32 cantidad)
{
    vida = cantidad;
}

void Protagonista::setEnergy(glm::f32 cantidad)
{
    energia = cantidad;
}
/**
METODO PARA GESTIONAR LA ENERGIA
**/
void Protagonista::setEnergia(glm::f32 cantidad,const glm::f32 Time)
{
    if(energia>0 || energia<100)
        energia+=cantidad* Time;
    if(energia<0){
        energia=0;
    }else if(energia>100)
        energia=100;

}
/**
METODO PARA GESTIONAR EL SALTO
**/
void Protagonista::setSalto(bool s)
{
    int aux = -1;
    b2Vec2 velocidad=Body->GetLinearVelocity();

    if(velocidad.y>=-5 && velocidad.y<5 && s && !saltando && !sigilo){
        aux = sonido->playRandomSound(ataqueS);  
        if(aux != -1)
            ataqueS[aux]->getCanal()->setGrupoCanales(sonido->getGrupoVoces());
        if(correr && energia>20)
        {   
            Body->ApplyForceToCenter(b2Vec2(0.f,10000000.f),true);
        }else if(energia<20)
        {
            Body->ApplyForceToCenter(b2Vec2(0.f,35000.f),true);
        }
        else
        {
            Body->ApplyForceToCenter(b2Vec2(0.f,6000000.f),true);  
          
        }

        setEnergia(1.5f,-10);
    }
    saltando=s;
}

/**
ACTUALIZA LA POSICION DEL PROTA
**/
void Protagonista::setPosition(Posicion* v)
{
   protaPosition=v;
}

/*
FUNCION PARA ACTIVAR O DESACTIVAR EL SIGILO
*/
void Protagonista::setSigilo()
{
    if(sigilo==false)
    {
        sigilo=true;
        //rec->setMaterialFlag(video::EMF_LIGHTING, true);
    }
    else{
        //rec->setMaterialFlag(video::EMF_LIGHTING, false);
        sigilo=false;
    }
}

void Protagonista::setCorrer(bool s)
{
    if(energia>10){
        correr=s;
    }else
        correr=false;
    
}

void Protagonista::setDireccion(int d)
{
    direccion=d;
}

void Protagonista::setAtaque(bool d)
{
    ataca = d;

}

void Protagonista::setCombate()
{
    if(combate == true)
    {
        combate = false;        // DESACTIVAMOS MODO COMBATE
        
    }
    else
    {
        combate = true;         // MODO COMBATE ACTIVADO
        
    }
    //std::cout<<combate<<endl;
}

void Protagonista::setNode(FObjeto* node)
{
    protaObjeto = node;
}

void Protagonista::quitarVida(glm::f32 cantidad)
{
    vida -=cantidad; 
    int aux = sonido->playRandomSound(dolor);
    if(aux != -1)
            dolor[aux]->getCanal()->setGrupoCanales(sonido->getGrupoVoces());

}

/**
DEVUELVE EL NODO QUE HEMOS CREADO
**/
FObjeto* Protagonista::getNode()
{
    return protaObjeto;
}

bool Protagonista::getCombate()
{
    return combate;
}

Posicion* Protagonista::getPosition()
{
   return protaPosition;
}

glm::f32 Protagonista::getEnergia()
{
    return energia;
}
glm::f32 Protagonista::getVida()
{
    return vida;
}

bool Protagonista::getSigilo()
{
    return sigilo;
}
bool Protagonista::getCorrer()
{
    return correr;
}

bool Protagonista::getSalto()
{
    return saltando;
}

int Protagonista::getPosCombate()
{
    return pos_combate;
}
int Protagonista::getDireccion()
{
    return direccion;
}

int Protagonista::getTiempoAtaque()
{
    return timeAtq;
}



Protagonista::~Protagonista()
{
 
    fachada->destruirObjeto(rec);
    fachada->destruirObjeto(flecha0);
    fachada->destruirObjeto(flecha1);
}
