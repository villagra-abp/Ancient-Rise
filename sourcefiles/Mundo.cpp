#include "../headerfiles/Mundo.h"

Mundo::Mundo():prota(nullptr),c(nullptr),f(nullptr),a(nullptr),t(nullptr),bebida(nullptr),b(nullptr),enem1(nullptr),enem2(nullptr),enemE1(nullptr),Plataforma(nullptr),
Plataforma2(nullptr), Plataforma3(nullptr), cam(nullptr)	//CONSTRUCTOR
{
Fachada* fachada=fachada->getInstance();


/*CREAMOS GESTOR DE SONIDO*/
	sonido = GestorSonido::getInstance();
	reverbCueva = sonido->create3DReverb();
	reverbCueva->setAtributos3D(0.0f,0.0f,0.0f, 10.0f, 2000.0f);
	reverbCueva->setTipo(sonido->REVERB_CUEVA);
	musicaBosque = sonido->createMusic(sonido->SOUND_MUSIC_BOSQUE);
/* CREAMOS PROTA */
	prota = prota->getInstance();
    //
	addGameObject(prota);
    

	//creo el suelo, el bounding box del prota y la plataforma
	//prota->CreateGround(world, 0.f, -150.f,1000*1000);
    //prota->CreateGround(world, 6600.f, 800.f,3200);
   // prota->CreateGround(world, 9600.f, 1700.f,3200);
    //prota->CreateGround(world, 12600.f, 2600.f,3200);
    prota->CreateBox(world, -5000.f, 30.f);
    
    //fachada->CreateGround(world, 0.25f, 128.f,176.25f, 22);
    //fachada->CreateGround(world, 177.f, 143.f,220,22);
    //fachada->CreateGround(world, 9600.f, 1800.f,3200,300);
    //fachada->CreateGround(world, 12600.f, 2700.f,3200,300);


/* CREAMOS VECTOR DE POSICIONES PARA EL ENEMIGO */

	posBuilder();

/* CREAMOS OBJETOS */

	Posicion* pC= new Posicion(-220.f, 0.34f, 30.f);
	c = new Comida(pC);
	comidas.push_back(c);
	addGameObject(c);

	Posicion* pC2= new Posicion(190.f, 0.34f, 30.f);
	c2 = new Comida(pC2);
	comidas.push_back(c2);
	addGameObject(c2);

	Posicion* pF= new Posicion(-190.f,0.34f,40.f);
	f = new Fuente( pF);
	fuentes.push_back(f);
	addGameObject(f);

	Posicion* pF2= new Posicion(320.f,0.34f,40.f);
	f2 = new Fuente( pF2);
	fuentes.push_back(f2);
	addGameObject(f2);

	Posicion* pA= new Posicion(120.f,0.34f,40.f);
	a = new Alarma( pA);
	alarmas.push_back(a);
	addGameObject(a);

	Posicion* pA2= new Posicion(-160.f,0.34f,40.f);
	a2 = new Alarma( pA2);
	alarmas.push_back(a2);
	addGameObject(a2);

	Posicion* posbebida= new Posicion(-300,0.34f,30.f);
 	bebida = new Bebida(posbebida);
 	addGameObject(bebida);

	Posicion* postrampa= new Posicion(520,0.34f,30.f);
 	t = new Trampa(postrampa);
 	addGameObject(t);


/* CREAMOS LA BLACKBOARD */

	b=new Blackboard();
    
	 b->setFuente(fuentes);
	 b->setComida(comidas);
	 b->setAlarma(alarmas);
	 b->setProtagonista(prota);
	 

/* CREAMOS PLATAFORMAS */
/*
    Posicion* escala = new Posicion(55.f,5.f,20.f);

    Plataforma = fachada->addCube(220,25,30,false);

    if (Plataforma)
    {
        fachada->setScala(Plataforma,escala);
        //fachada->setMaterial(Plataforma,"resources/plataf.bmp");
        Plataforma->Rotar(vec3(0,1,0), 1.5f);
        
    }

    Plataforma2= fachada->addCube(320,55,30,false);

    if (Plataforma2)
    {
        fachada->setScala(Plataforma2,escala);
        //fachada->setMaterial(Plataforma2,"resources/plataf.bmp");
        Plataforma2->Rotar(vec3(0,1,0), 1.5f);
    }

    Plataforma3= fachada->addCube(420,85,30,false);

    if (Plataforma3)
    {
        fachada->setScala(Plataforma3,escala);
        //fachada->setMaterial(Plataforma3,"resources/plataf.bmp");
        Plataforma3->Rotar(vec3(0,1,0), 1.5f);
    }

*/

/** ESTABLECEMOS LA CAMARA
 Aqui indicamos la posicion de la camara en el espacio 3d. En este caso,
 esta mirando desde la posicion (0, 30, -40) a la (0, 5, 0) donde es
 aproximadamente donde esta el objeto.
**/
    Posicion* camaraPos = new Posicion(prota->getPosition()->getPosX(),50,-140);
    
	cam = fachada->addCamara(camaraPos);
	//device->getCursorControl()->setVisible(true);

 /* AÑADIMOS UNA LUZ */   
    Posicion* luzPos=camaraPos;
    fachada->addLuz(luzPos);
    
/* CREAMOS EL TERRENO Y COLISIONES DE CAMARA */

	terrainBuilder();

/** TIME AND FRAMES
 Para poder hacer un movimiento independiente del framerate, tenemos que saber
 cuanto ha pasado desde el ultimo frame
**/
	lastFPS = -1;
	then = fachada->getTime();
	time_input = fachada->getTime();

	/* CREANDO GRAFO PARA EL MAPA PROTOTIPO */
     NodoGrafo *nA = new NodoGrafo('A',-9.8f, 0.34f); 				// EN MEDIO
     nodos.push_back(nA);
     addGameObject(nA);
     NodoGrafo *nB = new NodoGrafo('B',-190.08f, 0.34f); 				// FUENTE
     nodos.push_back(nB);
     addGameObject(nB);
     NodoGrafo *nC = new NodoGrafo('C',-334.259f, 0.34f); 			// Salir Nivel izq
     nodos.push_back(nC);
     addGameObject(nC);
     NodoGrafo *nD = new NodoGrafo('D',153.782f, 0.34f); 				// ALARMA DECHA
     nodos.push_back(nD);
     addGameObject(nD);
     NodoGrafo *nE = new NodoGrafo('E',387.195f, 0.34f); 				// TRAMPA
     nodos.push_back(nE);
     addGameObject(nE);

     b->setNodosGrafo(nodos); 								// Pasamos los nodos a la blackboard

     Arista *a1 = new Arista(5,1); 							// Arista con coste 5 y del tipo NORMAL
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

     nA->insertAristaS(a1,nB);  						// Arista que sale del nodo A hasta el nodo B
     nA->insertAristaS(a3,nD);
     nB->insertAristaS(a2,nC);
     nB->insertAristaS(a5,nA);
     nC->insertAristaS(a6,nB);
     nD->insertAristaS(a7,nA);
     nD->insertAristaS(a4,nE);
     nE->insertAristaS(a8,nD);


 /* CREAMOS ENEMIGOS BASICOS */
   
	enem1 = new EnemigoBasico( pos, 140.0, 0.8, 2, this, b, world);
	enemB.push_back(enem1);
	addGameObject(enem1);
	
	enem2 = new EnemigoBasico(pos2, 140.0, 0.8, 1, this, b, world);
	enemB.push_back(enem2);
	addGameObject(enem2); 

	for(int i=0;i<enemB.size();i++)   // Añadimos todos los enemigos basicos que existen a la blackboard
	{
		b->setEnemB(enemB[i]);
	}	

	/* CREAMOS ENEMIGOS ELITES */
	/*enemE1 = new EnemigoElite(pos3, 120.0, 0.8, 2, this, b, world);
	enemE.push_back(enemE1);
	addGameObject(enemE1);
*/
    ///Añado el menu
    //fachada->addMenu(1);
    
    Posicion* posmenu= new Posicion(.5f,-.5f,.5f);
 	Menu* menu = new Menu(posmenu);
 	addGameObject(menu);
    
    Posicion* pospausa= new Posicion(-20.5f,-.5f,.5f);
 	Pausa* pausa = new Pausa(pospausa);
 	addGameObject(pausa);

    cargarNivel();


}	

void Mundo::posBuilder(){	//CONSTRUCTOR DE POSICIONES DE ENEMIGOS

	/* SE LEE DE FICHERO LAS POSICIONES DE LA PATRULLA DE CADA ENEMIGO Y SE ALMACENAN EN LOS VECTORES */
  	Posicion *p0 = new Posicion(-9.8f, 0.34f,30.f);
  	pos.push_back(p0);
  	Posicion *p1 = new Posicion(-190.08f, 0.34f,30.f);
  	pos.push_back(p1);
  	Posicion *p2 = new Posicion(153.782f, 0.34f,30.f);
  	pos.push_back(p2);

  	Posicion *p3 = new Posicion(153.782f,0.34f,30.f);
  	pos2.push_back(p3);
  	Posicion *p4 = new Posicion(387.195f,0.34f,30.f);
  	pos2.push_back(p4);
  	Posicion *p5 = new Posicion(-9.8f,0.34f,30.f);
	pos2.push_back(p5);
  
  	Posicion *p6 = new Posicion(387.195f,0.34f,30.f);
  	pos3.push_back(p6);
  	Posicion *p7 = new Posicion(-9.8f,0.34f,30.f);
  	pos3.push_back(p7);
  	Posicion *p8 = new Posicion(-190.08f,0.34f,30.f);
  	pos3.push_back(p8);

    Posicion *p9 = new Posicion(153.782f,0.34f,30.f);
    pos4.push_back(p9);
    Posicion *p10 = new Posicion(-9.8f,0.34f,30.f);
    pos4.push_back(p10);
    Posicion *p11 = new Posicion(-190.08f,0.34f,30.f);
    pos4.push_back(p11);

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

	const glm::u32 now = fachada->getTime();
	const glm::f32 frameDeltaTime = (glm::f32)(now - then) / 1000.f; // Time in seconds
	then = now;
	glm::f32 tiempo=(glm::f32)(now - time_input)/1000.f;

	Posicion* protaPosition = prota->getPosition();
	//core::vector3df camPosition = cam->getPosition();

	/* PROTA UPDATE */

	protaUpdate(now, frameDeltaTime, tiempo);

	/* CAM UPDATE*/

    camUpdate(frameDeltaTime);

    b->setTime(frameDeltaTime);
    b->setProta(protaPosition->getPosX());

    /* ALARMA UPDATE*/
    a->update();
    a2->update();


    /* UPDATE DE LOS ENEMIGOS */

    for(int i=0; i<enemB.size();i++)   		// Enemigos Basicos
    {
    	if(enemB[i]->getNode()!=nullptr) 	// Solo si existen hacemos su update
    	{
	       	//enemB[i]->updateTiempo(frameDeltaTime);
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

    //draw();

    /* CONTROL DE FRAMES POR SEGUNDO */

    //fpsControl();

    /*UPDATE DE SONIDO*/
    sonido->playSound(musicaBosque);
    sonido->update();
	sonido->setListener(prota->getPosition()->getPosX(), prota->getPosition()->getPosY(), prota->getPosition()->getPosZ());

}

void Mundo::protaUpdate(const glm::u32 now, const glm::f32 frameDeltaTime, glm::f32 tiempo){
	//scene::ISceneNode* pro = (scene::ISceneNode*)prota->getNode();
    //core::vector3df protaPosition = pro->getPosition();

	energiaAnterior = prota->getEnergia();

    //prota->ataque(frameDeltaTime);
    
    //prota->pintarInterfaz();
    
	prota->comprobarColision(c);
    prota->comprobarColision(bebida);
    prota->comprobarColision(t);

    prota->updateBody(world);
    
    if(!prota->checkVida())
		fachada->cerrar();

	if(tiempo>0.2f) 	// HACEMOS QUE LO QUE HAYA DENTRO SE HAGA MENOS VECES POR SEGUNDO
    {
        glm::f32 energia=prota->getEnergia();

        time_input=now;

        checkCombate(); 							// Comprobamos si hemos pulsado la tecla de combate (K)

        prota->update(b);
        /*
        for(int i2=0; i2<enemB.size();i2++)
        {
           	prota->comprobarColision(enemB[i2]);
        }
        */
            
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
		////std::cout<<JoyX<<"\n";
	}
	/*
	if (sf::Joystick::isButtonPressed(0, 2))
	{
	    //std::cout<<"x=2"<<"\n";
	}
	if (sf::Joystick::isButtonPressed(0, 4))
	{
	    //std::cout<<"l=4"<<"\n";
	}
	if (sf::Joystick::isButtonPressed(0, 0))
	{
	    //std::cout<<"a=0"<<"\n";
	}
	if (sf::Joystick::isButtonPressed(0, 5))
	{
	    //std::cout<<"r=5"<<"\n";
	}
	*/

/* hacemos un set de ataque a 2 que es arriba 
        if(inputkey==22)//w
        {
           pos_pelea(prota,2);
           pos_defensa(prota,2);
        }
        else if(inputkey==18)//s
        {
            pos_pelea(prota,0);
            pos_defensa(prota,0);
        }
        else
        {
            pos_pelea(prota,1);
            pos_defensa(prota,1);
        }
*/

        /* movimiento hacia los lados y control de la velocidad en funcion de
        las variables de correr, sigilo y vitalidad */

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)||JoyX<=-50)//A
        {
            prota->setDireccion(0);
            prota->movimiento(0.1f);
    		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)||sf::Joystick::isButtonPressed(0, 5))
    		{
                prota->setCorrer(true);
      		    prota->setEnergia(-1.0f,0.2f);
    		}else
		  prota->setCorrer(false);
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||JoyX>=50){//D

            prota->setDireccion(1);
            prota->movimiento(0.1f);
    		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)||sf::Joystick::isButtonPressed(0, 5))
    		{
		  prota->setCorrer(true);
      		  prota->setEnergia(-1.0f,0.2f);
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

void Mundo::camUpdate(const glm::f32 frameDeltaTime){
    //prueba zoom camara
    /*
    if(prota->getCaida()){
       while(CamZ>-200){
            CamZ-=0.00001f;
            ////std::cout<<"con zoom"<<endl;
        }
    }
    if(prota->getSalto()){
        while(CamZ<-100){
            CamZ+=0.00001f;
            ////std::cout<<"con zoom"<<endl;
        }
        
        zoom=false;
        //CamZ=-200;
    }
    ////std::cout<<"Camz"<<CamZ<<endl;
    */
    
	Posicion* protaPosition = prota->getPosition();
	//vec3 camPosition = cam->getPosicion();
    if(estado==2){
    cam->setPosicion(vec3(-protaPosition->getPosX(),-protaPosition->getPosY()-40,-170)); // cambio 5O A ProtaPosition.Y
    //camPosition=vec3(protaPosition->getPosX(),protaPosition->getPosY()+30,protaPosition->getPosZ());
    //camPosition.y=protaPosition->getPosY()+30;
    //Falta funcion para enfocar la camara
    //cam->setTarget(camPosition);
    }
    if(estado==1){
        cam->setPosicion(vec3(20,2,-20));
        //cam->Rotar(vec3(0,1,0), 3.0f);
    }
    if(estado==0){
        cam->setPosicion(vec3(0,2,-20));
        //cam->Rotar(vec3(0,1,0), 3.0f);
    }
}

void Mundo::fpsControl(){
	
	int fps = 60;

	if (lastFPS != fps)
	{
		//core::stringw tmp(L"Movement Example - Irrlicht Engine [");
		//tmp += driver->getName();
		//tmp += L"] fps: ";
		//tmp += fps;

		//device->setWindowCaption(tmp.c_str());
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
	//estado=1;
    //camUpdate(5.f);
    //fachada->draw();
    //estado=0;
    //camUpdate(5.f);
    fachada->draw();
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
 void Mundo::CambioEstado(int n){
    estado=n;
}
int Mundo::getEstado(){
    return estado;
}



void Mundo::cargarNivel(){

   
TiXmlDocument doc;

if(doc.TiXmlDocument::LoadFile("resources/nivel2.xml",TIXML_ENCODING_UTF8 )){ //TIXML_ENCODING_UTF8
  //std::cout <<"Leyendo bien"<<endl;
    
}
//std::cout<<"CargarNivel"<<endl;

//OBTENER ELEMENTO MAPA
TiXmlElement* map = doc.FirstChildElement("map");

if(map){ 

  //std::cout <<"Obtenido elemento raiz(mapa)"<<endl;


//MOSTRAR ATRIBUTOS MAPA
      TiXmlAttribute* atri = map->FirstAttribute();
      
      int i=0;
      int ival;
      double dval;
     
      

      //std::cout <<"Obtenido atributos del mapa:"<<endl;
      while (atri)
      {
      //printf( "%s%s:", atri->Name(), atri->Value());

      if (atri->QueryIntValue(&ival)==TIXML_SUCCESS)    //printf( " int=%d", ival);//muestra su valor entero
      if (atri->QueryDoubleValue(&dval)==TIXML_SUCCESS) //printf( " d=%1.1f", dval);//muestra su valor doble
      //printf( "\n" );

      i++;
      atri=atri->Next();

      }

      //OBTENER ELEMENTO TILESET

        TiXmlElement* tileset = map->FirstChildElement("tileset");

       if(tileset){ 


         //std::cout <<"Obtenido elemento (tileset)"<<endl;

         
         TiXmlAttribute* atri2 = tileset->FirstAttribute();
          
          int i2=0;
          int ival2;
          double dval2;
         

          //printf("\n");
          //std::cout <<"Obtenido atributos del tileset:"<<endl;
              while (atri2)
              {
                //printf( "%s%s:", atri2->Name(), atri2->Value());

                if (atri2->QueryIntValue(&ival2)==TIXML_SUCCESS)    //printf( " int=%d", ival2);//muestra su valor entero
                if (atri2->QueryDoubleValue(&dval2)==TIXML_SUCCESS) //printf( " d=%1.1f", dval2);//muestra su valor doble
                //printf( "\n" );

                i2++;
                atri2=atri2->Next();
               
              }
      } 

      //OBTENER ELEMENTO LAYER

        TiXmlElement* layer = map->FirstChildElement("layer");//a la misma altura que tileset(hijos de mapa)
           if(layer){ 

              //std::cout <<"Layer ok"<<endl;

           }

    //OBTENER ELEMENTO DATA

        TiXmlElement* data = layer->FirstChildElement("data");//data es hijo de layer
           if(data){ 

              //std::cout <<"data ok"<<endl;

           }

    //OBTENER ELEMENTO OBJECTGROUP
        TiXmlElement* grupo = map->FirstChildElement("objectgroup");//objectgroup es hijo de map
           if(grupo){ 

              //std::cout <<"objectgroup suelo OK"<<endl;

                

//OBTENER ELEMENTO SUELO

    TiXmlElement* obje = grupo->FirstChildElement("object");//object es hjo de objectgroup


    
      
          int id;

          int i3=1;

          double altura;
          double ancho;
          double x;
          double y;
                  
            


              //printf("\n");
              //std::cout <<"Obtenido atributos del suelo:"<<endl;


              while(obje){
                 TiXmlAttribute* atri3 = obje->FirstAttribute();


                     //std::cout <<"Plataforma:"<<i3<<endl;
                      

                        while (atri3)
                        {
                             ////printf( "%s%s:", atri3->Name(), atri3->Value()

                            
                           

                             if(strcmp(atri3->Name(),"id")==0){
                              atri3->QueryIntValue(&id);

                                //std::cout <<"Id:"<<id<<endl;


                            }

                            //OBTENER DIMENSIONES DE LAS CAJAS QUE FORMAN EL SUELO


                             if(strcmp(atri3->Name(),"x")==0){
                              atri3->QueryDoubleValue(&x);

                                //std::cout <<"X:"<<(float)x<<endl;


                            }//CAJAS MAS ALTAS QUE ANCHAS NO TRATARLAS

                             if(strcmp(atri3->Name(),"y")==0){
                              atri3->QueryDoubleValue(&y);

                                //std::cout <<"Y:"<<(float)y<<endl;


                            }

                              if(strcmp(atri3->Name(),"width")==0){
                              atri3->QueryDoubleValue(&ancho);

                                //std::cout <<"Ancho:"<<(float)ancho<<endl;


                            }

                            if(strcmp(atri3->Name(),"height")==0){
                              atri3->QueryDoubleValue(&altura);

                                //std::cout <<"Altura:"<<(float)altura<<endl;

                            }  
                            //std::cout<<"cuenta: "<<i3<<endl;
                            
                             atri3=atri3->Next();   

                        }//atributos
                        //if(id==i3){
                                i3++;
                                fachada->CreateGround(world, (int)x, (int)y,(int)ancho, (int)altura);
                                //std::cout<<"cuenta: "<<x<<endl;
                            //}
                      obje=obje->NextSiblingElement("object");//pasamos a la siguiente caja
                       //printf("\n");

                         
                   }//objeto/elemento    


                   //TRATAMOS LAS PLATAFORMAS DE UNA FORMA LIGERAMENTE DISTINTA, LOSDEMAS OBJETOS COMPARTEN NUMERO Y TIPODE ATRIBUTOS
                   TiXmlElement* grupo2=grupo->NextSiblingElement("objectgroup");
              
              while(grupo2){ 
               
                  double dval9;
                  TiXmlAttribute* atriE = grupo2->FirstAttribute();

                   //std::cout <<"Objectgroup de:"<<atriE->Value()<<endl;
                    while(atriE){
                        atriE->QueryDoubleValue(&dval9)==TIXML_SUCCESS;
                         //printf( " d=%1.1f", dval9);
                         atriE=atriE->Next();
                         //printf("\n");

                     }//atributosGrupoEnemigos
               
               TiXmlElement* ene = grupo2->FirstChildElement("object");//object es hjo de objectgroup

                int idE;
                int iE;
                int tipo;
                double xEn;
                double yEn;
                
                  while(ene){
                      TiXmlAttribute* atriEn = ene->FirstAttribute();

                      //std::cout <<"Objeto:"<<iE<<endl;

                      iE++;
                          while(atriEn){
                           
                            if(strcmp(atriEn->Name(),"id")==0){
                              atriEn->QueryIntValue(&idE);

                                //std::cout <<"Id:"<<idE<<endl;

                            }

                            if(strcmp(atriEn->Name(),"type")==0){
                              atriEn->QueryIntValue(&tipo);
                              

                                //std::cout <<"Tipo:"<<tipo<<endl;

                              
                            }

                            if(strcmp(atriEn->Name(),"x")==0){
                              atriEn->QueryDoubleValue(&xEn);

                                //std::cout <<"X:"<<xEn<<endl;

                            }

                            if(strcmp(atriEn->Name(),"y")==0){
                              atriEn->QueryDoubleValue(&yEn);

                                //std::cout <<"Y:"<<yEn<<endl;

                            }

                            atriEn=atriEn->Next();

                          }//atributosEnemigo

                          //printf("\n");
                  if(strcmp(grupo2->FirstAttribute()->Value(),"Enemigos")==0){
                      //cout<<"Enemigo tipo: "<<tipo<<endl;
                  }   
                  if(strcmp(grupo2->FirstAttribute()->Value(),"Recolectables")==0){
                      //cout<<"Recolectables tipo: "<<tipo<<endl;
                  }  
                  if(strcmp(grupo2->FirstAttribute()->Value(),"armas")==0){
                      //cout<<"armas tipo: "<<tipo<<endl;
                  }  
                  if(strcmp(grupo2->FirstAttribute()->Value(),"alarmas")==0){
                      //cout<<"alarmas"<<endl;
                        Posicion* posA= new Posicion(xEn-190,-yEn+60,30.f);
                        Alarma* alarm = new Alarma( posA);
                        alarmas.push_back(alarm);
                        addGameObject(alarm);
                        delete posA;
                  }  
                  if(strcmp(grupo2->FirstAttribute()->Value(),"fuentes")==0){
                      //cout<<"fuentes"<<endl;
                        Posicion* posF= new Posicion(xEn-190,-yEn+60,30.f);
                        Fuente* fuente = new Fuente( posF);
                        fuentes.push_back(fuente);
                        addGameObject(fuente);
                        delete posF;
                  }  
                  if(strcmp(grupo2->FirstAttribute()->Value(),"Nodos")==0){
                      //cout<<"Nodos "<<endl;
                      Posicion* posN= new Posicion(xEn-190,-yEn+60,30.f);
                      //std::cout<<posN->getPosX()<<"++1+"<<posN->getPosY()<<endl;
                      
                      delete posN;
                  } 
                    ene=ene->NextSiblingElement("object");//pasamos a la siguiente caja
                  }//enemigo
                  

                  grupo2=grupo2->NextSiblingElement("objectgroup");//pasamos a la siguiente caja
              }//grupo2


           }//objectgroup
              
    }//mapa

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

	pos.clear();
	pos2.clear();
	pos3.clear();

    delete c;
    delete c2;
    delete f;
    delete f2;
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
