#include "../headerfiles/Mundo.h"

Mundo::Mundo():device(nullptr),driver(nullptr),smgr(nullptr),guienv(nullptr),prota(nullptr),
rec(nullptr),Terrain(nullptr),c(nullptr),f(nullptr),a(nullptr),t(nullptr),bebida(nullptr),b(nullptr),enem1(nullptr),enem2(nullptr),enemE1(nullptr),Plataforma(nullptr),
Plataforma2(nullptr), Plataforma3(nullptr), cam(nullptr), terrain(nullptr),selector(nullptr),anim(nullptr)	//CONSTRUCTOR
{
Fachada* fachada=fachada->getInstance();
/* CREAMOS IRRLICHT DEVICE */	 
	device = fachada->getDevice();
	//receiver = mainReceiver;

/** PUNTEROS 
 A VideoDriver, al SceneManager y al entorno de interfaz de usuario, para no tener que
 estar llamandolos siempre y solo los llamamos una vez
**/
	driver = fachada->getDriver();
	smgr = fachada->getScene();
	guienv = fachada->getGUI();


/*CREAMOS GESTOR DE SONIDO*/
	sonido = GestorSonido::getInstance();
	reverbCueva = sonido->create3DReverb();
	reverbCueva->setAtributos3D(0.0f,0.0f,0.0f, 10.0f, 2000.0f);
	reverbCueva->setTipo(sonido->REVERB_CUEVA);
	musicaBosque = sonido->createMusic(sonido->SOUND_MUSIC_BOSQUE);
/* CREAMOS PROTA */
	prota = prota->getInstance();
    
	addGameObject(prota);

	//creo el suelo, el bounding box del prota y la plataforma
	prota->CreateGround(world, 0.f, -150.f,1000*1000);
    prota->CreateGround(world, 6600.f, 900.f,3200);
    prota->CreateGround(world, 9600.f, 1800.f,3200);
    prota->CreateGround(world, 12600.f, 2700.f,3200);
    prota->CreateBox(world, -5000.f, 0.f);


/* CREAMOS VECTOR DE POSICIONES PARA EL ENEMIGO */

	posBuilder();

/* CREAMOS OBJETOS */

	Posicion* pC= new Posicion(-220.f, 0.34f, 30.f);
	c = new Comida(device, smgr, pC);
	comidas.push_back(c);
	addGameObject(c);

	Posicion* pC2= new Posicion(190.f, 0.34f, 30.f);
	c2 = new Comida(device, smgr, pC2);
	comidas.push_back(c2);
	addGameObject(c2);

	Posicion* pF= new Posicion(-190.f,0.34f,40.f);
	f = new Fuente(device, smgr, pF);
	fuentes.push_back(f);
	addGameObject(f);

	Posicion* pF2= new Posicion(330.f,65.34f,40.f);
	f2 = new Fuente(device, smgr, pF2);
	fuentes.push_back(f2);
	addGameObject(f2);
    
	Posicion* pA= new Posicion(210.2f, 35.34f,40.f);
	a = new Alarma(device, smgr, pA);
	alarmas.push_back(a);
	addGameObject(a);

	/*Posicion* pA2= new Posicion(-10.f,0.34f,40.f);
	a2 = new Alarma(device, smgr, pA2);
	alarmas.push_back(a2);
	addGameObject(a2);*/

	Posicion* posbebida= new Posicion(-300,0.34f,30.f);
 	bebida = new Bebida(device, smgr, posbebida);
 	addGameObject(bebida);

	Posicion* postrampa= new Posicion(520,0.34f,30.f);
 	t = new Trampa(device, smgr, postrampa);
 	addGameObject(t);

/* CREAMOS LA BLACKBOARD */

	b=new Blackboard();
	 b->setFuente(fuentes);
	 b->setComida(comidas);
	 b->setAlarma(alarmas);
	 b->setProtagonista(prota);

/* CREAMOS PLATAFORMAS */
    Posicion* escala = new Posicion(10.f,1.f,5.f);

	Plataforma = fachada->addCube(220,25,30,false);

	if (Plataforma) /** SI HEMOS CREADO EL CUBO **/
	{
		fachada->setScala(Plataforma,escala);
        fachada->setMaterial(Plataforma,"resources/plataf.bmp");
		
	}

	Plataforma2= fachada->addCube(320,55,30,false);

	if (Plataforma2) /** SI HEMOS CREADO EL CUBO **/
	{
		fachada->setScala(Plataforma2,escala);
		fachada->setMaterial(Plataforma2,"resources/plataf.bmp");
	}

	Plataforma3= fachada->addCube(420,85,30,false);

	if (Plataforma3) /** SI HEMOS CREADO EL CUBO **/
	{
		fachada->setScala(Plataforma3,escala);
		fachada->setMaterial(Plataforma3,"resources/plataf.bmp");
	}

/** ESTABLECEMOS LA CAMARA
 Aqui indicamos la posicion de la camara en el espacio 3d. En este caso,
 esta mirando desde la posicion (0, 30, -40) a la (0, 5, 0) donde es
 aproximadamente donde esta el objeto.
**/
	cam = smgr->addCameraSceneNode(0, vector3df(prota->getPosition()->getPosX(),50,-140), vector3df(0,5,0));
	device->getCursorControl()->setVisible(true);

/* CREAMOS EL TERRENO Y COLISIONES DE CAMARA */

	//this->terrainBuilder();

/** TIME AND FRAMES
 Para poder hacer un movimiento independiente del framerate, tenemos que saber
 cuanto ha pasado desde el ultimo frame
**/
	lastFPS = -1;
	then = fachada->getTime();
	time_input = fachada->getTime();

	/* CREANDO GRAFO PARA EL MAPA PROTOTIPO */

     NodoGrafo *nA = new NodoGrafo('A',-334.259f, 0.34f);           // Salir Nivel izq
     nodos.push_back(nA);
     addGameObject(nA);

     NodoGrafo *nB = new NodoGrafo('B',-241.2f, 0.34f);               
     nodos.push_back(nB);
     addGameObject(nB);

     NodoGrafo *nC = new NodoGrafo('C',-157.4f, 0.34f);           // Alarma izqd
     nodos.push_back(nC);
     addGameObject(nC);

     NodoGrafo *nD = new NodoGrafo('D',-76.5f, 0.34f);                
     nodos.push_back(nD);
     addGameObject(nD);

     NodoGrafo *nE = new NodoGrafo('E',41.9f, 0.34f);                
     nodos.push_back(nE);
     addGameObject(nE);

     NodoGrafo *nF = new NodoGrafo('F',120.7f, 0.34f);           // Alarma derecha            
     nodos.push_back(nF);
     addGameObject(nF);

     NodoGrafo *nG = new NodoGrafo('G',155.3f, 0.34f);            // Salto 1        
     nodos.push_back(nG);
     addGameObject(nG);

     NodoGrafo *nH = new NodoGrafo('H',180.2f, 35.34f);            // Llegado salto 1       
     nodos.push_back(nH);
     addGameObject(nH);

     NodoGrafo *nI = new NodoGrafo('I',260.3f, 35.34f);            // Salto 2       
     nodos.push_back(nI);
     addGameObject(nI);

     NodoGrafo *nJ = new NodoGrafo('J',277.5f, 65.34f);            // Llegado Salto 2      
     nodos.push_back(nJ);
     addGameObject(nJ);

     NodoGrafo *nK = new NodoGrafo('K',360.3f, 65.34f);            // Salto 3    
     nodos.push_back(nK);
     addGameObject(nK);

     NodoGrafo *nP = new NodoGrafo('P',249.2f, 0.34f);               
     nodos.push_back(nP);
     addGameObject(nP);

     NodoGrafo *nQ = new NodoGrafo('Q',320.2f, 0.34f);          // Fuente decha       
     nodos.push_back(nQ);
     addGameObject(nQ);

     NodoGrafo *nS = new NodoGrafo('S',416.766f, 0.34f);                
     nodos.push_back(nS);
     addGameObject(nS);

      NodoGrafo *nT = new NodoGrafo('T',498.9f, 0.34f);          // TRampa      
     nodos.push_back(nT);
     addGameObject(nT);


     b->setNodosGrafo(nodos);                               // Pasamos los nodos a la blackboard

     Arista *a1 = new Arista(5,1);                          // Arista con coste 5 y del tipo NORMAL
     aristas.push_back(a1);
     Arista *a2 = new Arista(5,1);
     aristas.push_back(a2);
     Arista *a3 = new Arista(5,1);
     aristas.push_back(a3);
     Arista *a4 = new Arista(5,1);
     aristas.push_back(a4);
     Arista *a5 = new Arista(5,1);
     aristas.push_back(a5);
     Arista *a6 = new Arista(5,1);
     aristas.push_back(a6);
     Arista *a7 = new Arista(5,1);
     aristas.push_back(a7);
     Arista *a8 = new Arista(5,1);
     aristas.push_back(a8);
     Arista *a9 = new Arista(5,1);
     aristas.push_back(a9);
     Arista *a10 = new Arista(5,1);
     aristas.push_back(a10);
     Arista *a11 = new Arista(7,2);
     aristas.push_back(a11);
     Arista *a12 = new Arista(7,2);
     aristas.push_back(a12);
     Arista *a13 = new Arista(5,1);
     aristas.push_back(a13);
     Arista *a14 = new Arista(5,1);
     aristas.push_back(a14);
     Arista *a15 = new Arista(5,1);
     aristas.push_back(a15);
     Arista *a16 = new Arista(5,1);
     aristas.push_back(a16);
     Arista *a17 = new Arista(5,1);
     aristas.push_back(a17);
     Arista *a18 = new Arista(5,1);
     aristas.push_back(a18);
     Arista *a19 = new Arista(5,1);
     aristas.push_back(a19);
     Arista *a20 = new Arista(5,1);
     aristas.push_back(a20);
     Arista *a21 = new Arista(5,1);
     aristas.push_back(a21);
     Arista *a22 = new Arista(5,1);
     aristas.push_back(a22);
     Arista *a23 = new Arista(5,1);
     aristas.push_back(a23);
     Arista *a24 = new Arista(5,1);
     aristas.push_back(a24);
     Arista *a25 = new Arista(5,1);
     aristas.push_back(a25);
     Arista *a26 = new Arista(5,1);
     aristas.push_back(a26);
     Arista *a27 = new Arista(5,1);
     aristas.push_back(a27);
     Arista *a28 = new Arista(5,1);
     aristas.push_back(a28);

     nA->insertAristaS(a1,nB);                          // Arista que sale del nodo A hasta el nodo B
     nB->insertAristaS(a2,nA);                          
     nB->insertAristaS(a3,nC);
     nC->insertAristaS(a4,nB);
     nC->insertAristaS(a5,nD);
     nD->insertAristaS(a6,nC);
     nD->insertAristaS(a7,nE);
     nE->insertAristaS(a8,nD);
     nE->insertAristaS(a9,nF);
     nF->insertAristaS(a13,nE);
     nF->insertAristaS(a14,nG);
     nG->insertAristaS(a15,nF);
     nG->insertAristaS(a11,nH);
     nG->insertAristaS(a10,nP);
     nH->insertAristaS(a16,nG);
     nH->insertAristaS(a17,nI);
     nI->insertAristaS(a18,nH);
     nI->insertAristaS(a12,nJ);
     nJ->insertAristaS(a19,nI);
     nJ->insertAristaS(a20,nK);
     nK->insertAristaS(a21,nJ);
     nP->insertAristaS(a22,nG);
     nP->insertAristaS(a23,nQ);
     nQ->insertAristaS(a24,nP);
     nQ->insertAristaS(a25,nS);
     nS->insertAristaS(a26,nQ);
     nS->insertAristaS(a27,nT);
     nT->insertAristaS(a28,nS);


 /* CREAMOS ENEMIGOS BASICOS */
   
	enem1 = new EnemigoBasico(device, smgr, pos, 140.0, 0.8, 2, this, b, world);
	enemB.push_back(enem1);
	addGameObject(enem1);
	
	enem2 = new EnemigoBasico(device, smgr, pos2, 140.0, 0.8, 1, this, b, world);
	enemB.push_back(enem2);
	addGameObject(enem2); 
    /*
    enem3 = new EnemigoBasico(device, smgr, pos4, 140.0, 0.8, 1, this, b, world);
    enemB.push_back(enem3);
    addGameObject(enem3); 
    */
    /*enem4 = new EnemigoBasico(device, smgr, pos3, 140.0, 0.8, 1, this, b, world);
    enemB.push_back(enem4);
    addGameObject(enem4); */
	
	for(int i=0;i<enemB.size();i++)   // Añadimos todos los enemigos basicos que existen a la blackboard
	{
		b->setEnemB(enemB[i]);
	}	

	/* CREAMOS ENEMIGOS ELITES */
	/*enemE1 = new EnemigoElite(device, smgr, pos3, 120.0, 0.8, 2, this, b, world);
	enemE.push_back(enemE1);
	addGameObject(enemE1);*/
    

}	

void Mundo::posBuilder(){	//CONSTRUCTOR DE POSICIONES DE ENEMIGOS

	/* SE LEE DE FICHERO LAS POSICIONES DE LA PATRULLA DE CADA ENEMIGO Y SE ALMACENAN EN LOS VECTORES */
  /*
    Posicion *p0 = new Posicion(41.9f, 0.34f,30.f);
    pos.push_back(p0);
    Posicion *p1 = new Posicion(277.5f, 65.34f,30.f);
    pos.push_back(p1);

    Posicion *p3 = new Posicion(120.7f,0.34f,30.f);
    pos2.push_back(p3);
    Posicion *p4 = new Posicion(498.9f,0.34f,30.f);
    pos2.push_back(p4);

    Posicion *p5 = new Posicion(120.7f,0.34f,30.f);
    pos3.push_back(p5);
    Posicion *p6 = new Posicion(-334.259f,0.34f,30.f);
    pos3.push_back(p6);

    Posicion *p7 = new Posicion(-157.4f,0.34f,30.f);
    pos4.push_back(p7);
    Posicion *p8 = new Posicion(155.3f,0.34f,30.f);
    pos4.push_back(p8);

    Posicion *p9 = new Posicion(498.9f,0.34f,30.f);
    pos5.push_back(p9);
    Posicion *p10 = new Posicion(249.2f,0.34f,30.f);
    pos5.push_back(p10);
    */

    Posicion *p0 = new Posicion(40.f,0.f,30.f);
    pos.push_back(p0);
    Posicion *p1 = new Posicion(0.f,0.f,30.f);
    pos.push_back(p1);
    Posicion *p2 = new Posicion(-40.f,0.f,30.f);
    pos.push_back(p2);
    Posicion *p3 = new Posicion(-60.f,0.f,30.f);
    pos.push_back(p3);
    Posicion *p4 = new Posicion(-80.f,0.f,30.f);
    pos.push_back(p4);


    Posicion *p5 = new Posicion(100.f,0.f,30.f);
    pos2.push_back(p5);
    Posicion *p6 = new Posicion(150.f,0.f,30.f);
    pos2.push_back(p6);
    Posicion *p7 = new Posicion(200.f,0.f,30.f);
    pos2.push_back(p7);


    Posicion *p8 = new Posicion(200.f,0.f,30.f);
    pos3.push_back(p8);
    Posicion *p9 = new Posicion(150.f,0.f,30.f);
    pos3.push_back(p9);
    Posicion *p10 = new Posicion(60.f,0.f,30.f);
    pos3.push_back(p10);
    Posicion *p11 = new Posicion(0.f,0.f,30.f);
    pos3.push_back(p11);

}

void Mundo::terrainBuilder(){	//CONSTRUCTOR DEL TERRENOS Y COLISIONES DE CAMARA

    fachada->drawTerreno();

}

void Mundo::update(){
    //Comprueba las entradas del teclado
	checkInput();
	//pasos de las fisicas en el mundo
	world.Step(1/60.f, 8, 3);
	//reinicio las fuerzas en el mundo
	world.ClearForces();

	/* Creamos el framedeltatime y el tiempo */

	const u32 now = device->getTimer()->getTime();
	const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;
	f32 tiempo=(f32)(now - time_input)/1000.f;

	Posicion* protaPosition = prota->getPosition();
	core::vector3df camPosition = cam->getPosition();

	/* PROTA UPDATE */

	protaUpdate(now, frameDeltaTime, tiempo);

	/* CAM UPDATE*/

    camUpdate(frameDeltaTime);

    b->setTime(frameDeltaTime);
    b->setProta(protaPosition->getPosX());

    /* ALARMA UPDATE*/
    a->update();
    //a2->update();


    /* UPDATE DE LOS ENEMIGOS */
    for(int i=0; i<enemB.size();i++)   		// Enemigos Basicos
    {
    	if(enemB[i]->getNode()!=nullptr) 	// Solo si existen hacemos su update
    	{
	       	enemB[i]->updateTiempo(frameDeltaTime);
	     	enemB[i]->Update(prota->getPosition());
	    }
    }

    for(int i2=0; i2<enemE.size();i2++) 	// Enemigos Elites
    {
    	if(enemE[i2]->getNode()!=nullptr)
    	{
	    	enemE[i2]->updateTiempo(frameDeltaTime);
	     	enemE[i2]->Update(prota->getPosition());
	    }
    }

    /* DRAW SCENE */

    draw();

    /* CONTROL DE FRAMES POR SEGUNDO */

    fpsControl();

    /*UPDATE DE SONIDO*/
    sonido->playSound(musicaBosque);
    sonido->update();
	sonido->setListener(prota->getPosition()->getPosX(), prota->getPosition()->getPosY(), prota->getPosition()->getPosZ());

}

void Mundo::protaUpdate(const u32 now, const f32 frameDeltaTime, f32 tiempo){
	//scene::ISceneNode* pro = (scene::ISceneNode*)prota->getNode();
    //core::vector3df protaPosition = pro->getPosition();

	energiaAnterior = prota->getEnergia();

    //prota->ataque(frameDeltaTime);
    
    prota->pintarInterfaz();
    
	prota->comprobarColision(c);
    prota->comprobarColision(bebida);
    prota->comprobarColision(t);

    prota->updateBody(world);
    
    if(!prota->checkVida())
		device->closeDevice();

	if(tiempo>0.2f) 	// HACEMOS QUE LO QUE HAYA DENTRO SE HAGA MENOS VECES POR SEGUNDO
    {
        f32 energia=prota->getEnergia();

        time_input=now;

        checkCombate(); 							// Comprobamos si hemos pulsado la tecla de combate (K)

        prota->update(b);
            
    }

    if(prota->getCombate()==false)
    {
    	//prota->checkSigilo(prota);  						// Comprobamos si hemos pulsado la tecla de sigilo (C)
    }

    /* Velocidad Barra de Energia */
    energiaActual = prota->getEnergia();
    energiaDelta = energiaActual - energiaAnterior;

    if(energiaDelta < 0){
    	relojDescanso.restart();
    }

    tiempoTrans = relojDescanso.getElapsedTime().asSeconds();
    
    if(tiempoTrans > 0.8f)	
    	prota->setEnergia(25,frameDeltaTime);  //CAMBIO 5 a 15
    else
    	prota->setEnergia(2, frameDeltaTime);

}
void Mundo::checkInput(){
	if(sf::Joystick::isConnected(0)){
		JoyY=sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		JoyX=sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		//std::cout<<JoyX<<"\n";
	}
        /* movimiento hacia los lados y control de la velocidad en funcion de
        las variables de correr, sigilo y vitalidad */

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)||JoyX<=-50)//A
        {
            prota->setDireccion(0);
            prota->movimiento(0.1f);
    		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)||sf::Joystick::isButtonPressed(0, 5))
    		{
                prota->setCorrer(true);
      		    prota->setEnergia(-5.0f,0.2f);
    		}else
		  prota->setCorrer(false);
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||JoyX>=50){//D

            prota->setDireccion(1);
            prota->movimiento(0.1f);
    		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)||sf::Joystick::isButtonPressed(0, 5))
    		{
		  prota->setCorrer(true);
      		  prota->setEnergia(-5.0f,0.2f);
    		}else
		  prota->setCorrer(false);
        }
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||sf::Joystick::isButtonPressed(0, 0)){
        	prota->setSalto(true);
    	}else
		prota->setSalto(false);
       	
	       
}

void Mundo::checkCombate()
{
	/* control de ataque*/
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)||sf::Joystick::isButtonPressed(0, 2))//p
    {  
        prota->setAtaque(true);
    }
        
    /* control de defensa*/
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)||sf::Joystick::isButtonPressed(0, 4))//k
    {
        prota->setCombate();
    }
}

void Mundo::camUpdate(const f32 frameDeltaTime){
	Posicion* protaPosition = prota->getPosition();
	core::vector3df camPosition = cam->getPosition();

	//rec->setPosition(protaPosition);
    cam->setPosition(vector3df(protaPosition->getPosX(),protaPosition->getPosY()+30,-140)); // cambio 5O A ProtaPosition.Y
    camPosition=core::vector3df(protaPosition->getPosX(),protaPosition->getPosY(),protaPosition->getPosZ());
    camPosition.Y=protaPosition->getPosY()+30;
    cam->setTarget(camPosition);
}

void Mundo::fpsControl(){
	
	int fps = driver->getFPS();

	if (lastFPS != fps)
	{
		core::stringw tmp(L"Movement Example - Irrlicht Engine [");
		tmp += driver->getName();
		tmp += L"] fps: ";
		tmp += fps;

		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}

	this->timeWait();
}

void Mundo::timeWait(){
	static long t=clock();
	const float fps = 60.f;

	long toWait = t + CLOCKS_PER_SEC / fps - clock();
	
	if(toWait > 0)
		usleep(toWait);

	t = clock();
}

void Mundo::draw(){
	
    fachada->draw(255,100,101,140);
}

void Mundo::addGameObject (GameObject* o){
	gos.push_back(o);
}

GameObject* Mundo::getGameObject(uint8_t pos) const{
	GameObject* o = nullptr;

	if(pos < gos.size() && gos[pos] != nullptr){
		o = gos[pos];
	}

	return o;
}

Mundo::~Mundo()	//DESTRUCTOR
{
	/* DELETE PROTAGONISTA */
	delete prota;

	/* DELETE ENEMIGOS */
	for(int cont=0; cont<enemB.size();cont++)
	{
		delete enemB[cont];
	}
	enemB.clear();

	for(int cont2=0; cont2<enemE.size();cont2++)
	{
		delete enemE[cont2];
	}
	enemE.clear();

    for(int cont3=0; cont3<pos.size();cont3++)
    {
        delete pos[cont3];
    }
	pos.clear();

    for(int cont4=0; cont4<pos2.size();cont4++)
    {
        delete pos2[cont4];
    }
    pos2.clear();

    for(int cont5=0; cont5<pos3.size();cont5++)
    {
        delete pos3[cont5];
    }
    pos3.clear();

    for(int cont6=0; cont6<pos4.size();cont6++)
    {
        delete pos4[cont6];
    }
    pos4.clear();

    delete b;
    delete c;
    delete f;
    delete a;
    delete a2;
    delete bebida;
    delete t;
    delete sonido;

   // delete pC, pC2, pF, pF2, pA, pA2, posbebida, postrampa;

    /* DELETE DEL GRAFO PROVISIONAL */
   	for(int cont3=0; cont3<nodos.size();cont3++)
   	{
   		delete nodos[cont3];
   	}
   	nodos.clear();

   	for(int cont4=0; cont4<aristas.size();cont4++)
   	{
   		delete aristas[cont4];
   	}
   	aristas.clear();

}
