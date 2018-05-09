#include "../headerfiles/Mundo.h"

Mundo::Mundo():prota(nullptr),b(nullptr),enem1(nullptr),enemE1(nullptr), cam(nullptr),posA(nullptr), posF(nullptr), p1(nullptr),
p0(nullptr), posC(nullptr), posB(nullptr), posT(nullptr)	//CONSTRUCTOR
{
    Fachada* fachada=fachada->getInstance();

    nivel = 1;

    /*CREAMOS GESTOR DE SONIDO*/
    sonido = GestorSonido::getInstance();
    reverbCueva = sonido->create3DReverb();
    reverbCueva->setAtributos3D(0.0f,0.0f,0.0f, 10.0f, 2000.0f);
    reverbCueva->setTipo(sonido->REVERB_CUEVA);
    musicaBosque = sonido->createMusic(sonido->SOUND_MUSIC_BOSQUE);

    /* CREAMOS PROTA */
    prota = prota->getInstance();
    addGameObject(prota);

    /* CREAMOS LA BLACKBOARD */
    b=new Blackboard();

    /* Lectura del XML para la logica del juego */
    cargarNivel();

    /* Pasamos toda la info necesaria a la blackboard */
    b->setProtagonista(prota);
 
    b->setEnemB(enemB);  // Añadimos todos los enemigos basicos que existen a la blackboard

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
        Posicion* dir = new Posicion(0,-1,-1);
        fachada->addLuzDireccional(dir);
        Posicion* d = new Posicion(0,1,0);
        Posicion* origen = new Posicion(0,65,0);
        fachada->addLuzDirigida(origen,d);

        vector<string> pathsSkybox;
        pathsSkybox.push_back("resources/skybox/skybox_1.tga");
        pathsSkybox.push_back("resources/skybox/skybox_3.tga");
        pathsSkybox.push_back("resources/skybox/skybox_up.tga");
        pathsSkybox.push_back("resources/skybox/skybox_down.tga");
        pathsSkybox.push_back("resources/skybox/skybox_2.tga");
        pathsSkybox.push_back("resources/skybox/skybox_4.tga");
        fachada->addSkybox(pathsSkybox);


    /** TIME AND FRAMES
     Para poder hacer un movimiento independiente del framerate, tenemos que saber
     cuanto ha pasado desde el ultimo frame
    **/
    	lastFPS = -1;

        
    Posicion posmenu(.5f,-5000.f,.5f);
    menu = new Menu(&posmenu);

    Posicion pospausa(-20.5f,-5000.f,.5f);
    pausa = new Pausa(&pospausa);
        
    Posicion poshud(-40.5f,-5001.5f,.5f);
    hud = new Hud(&poshud);
    
    Posicion posOpc(-30.f,-5000.f,.5f);
    opciones = new Opciones(&posOpc);

}	

void Mundo::update()
{
    if(prota->getPosition()->getPosX()>360)
    {
        cambiarNivel();
    }
	//pasos de las fisicas en el mundo
	world.Step(1/60.f, 8, 3);
	//reinicio las fuerzas en el mundo
	world.ClearForces();


	/* Creamos el framedeltatime */
	float frameDeltaTime = fachada->getTime(); // Time in seconds

	Posicion* protaPosition = prota->getPosition();

	/* PROTA UPDATE */
    protaUpdate(frameDeltaTime);
        
    /*HUD UPDATE*/
    hud->update(prota->getVida(),prota->getEnergia());
    
	/* CAM UPDATE*/
    camUpdate(frameDeltaTime);

    b->setTime(frameDeltaTime);
    b->setProta(protaPosition->getPosX());


    /* UPDATE DE LOS OBJETOS */
    for(size_t i=0; i<alarmas.size();i++)
    {
        alarmas[i]->update();
    }

    for(size_t i=0; i<bebidas.size();i++)
    {
        if(bebidas[i]->getNode()!=nullptr)
        {
            prota->comprobarColision(bebidas[i]);
            bebidas[i]->update();
        }
    }

    for(size_t i=0; i<comidas.size();i++)
    {
        if(comidas[i]->getNode()!=nullptr)
        {
            prota->comprobarColision(comidas[i]);
            comidas[i]->update();
        }
    }

    for(size_t i=0; i<trampas.size();i++)
    {
        if(trampas[i]->getNode()!=nullptr)
        {
            prota->comprobarColision(trampas[i]);
            trampas[i]->update();
        }
    }

    if(estado==2)
    {
        //Comprueba las entradas del teclado
        checkInput(-1);
//cout<<"llego2"<<endl;
        /* UPDATE DE LOS ENEMIGOS */
        for(size_t i=0; i<enemB.size();i++)   		// Enemigos Basicos
        {
        	if(enemB[i]->getNode()!=nullptr) 	// Solo si existen hacemos su update
        	{
                //cout<<"llego2.5"<<endl;
    	       	enemB[i]->updateTiempo(frameDeltaTime);
    	     	enemB[i]->Update(prota->getPosition());
    	    }
        }

        //cout<<"llego3"<<endl;

        for(int i2=0; i2<enemE.size();i2++) 	// Enemigos Elites
        {
        	if(enemE[i2]->getNode()!=nullptr)
        	{
    	    	enemE[i2]->updateTiempo(frameDeltaTime);
    	     	enemE[i2]->Update(prota->getPosition());
    	    }
        }

        //cout<<"llego4"<<endl;
        /*UPDATE DE SONIDO*/
        sonido->playSound(musicaBosque);
        sonido->update();
    	sonido->setListener(prota->getPosition()->getPosX(), prota->getPosition()->getPosY(), prota->getPosition()->getPosZ());
    }

}

void Mundo::protaUpdate(const glm::f32 frameDeltaTime)
{
	Tiempo=Tiempo+frameDeltaTime;
    
	energiaAnterior = prota->getEnergia();

    prota->updateBody(world);

    if(!prota->checkVida())
		fachada->cerrar();

	if(Tiempo>0.3f) 	// HACEMOS QUE LO QUE HAYA DENTRO SE HAGA MENOS VECES POR SEGUNDO
    {
        glm::f32 energia=prota->getEnergia();

        //checkCombate(); 							// Comprobamos si hemos pulsado la tecla de combate (K)
        
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        {   
            for(int i=0; i<enemB.size();i++)
            {
                enemB[i]->setInvisible();
            }
        }
        prota->update(b);
        Tiempo=0;
            
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
    	prota->setEnergia(5,frameDeltaTime);  //CAMBIO 5 a 15
    else
    	prota->setEnergia(2, frameDeltaTime);

}
/* Funcion para controlar todas las entradas por teclado del jugador */

void Mundo::checkInput(int tecla){
    if (tecla!=-1)
    {
        //std::cout<<tecla<<endl;  
    }
     
    switch(tecla){

        case 10: // Tecla K Activar/Desactivar Combate
        {        
           prota->setCombate();      
           break;
        }

        case 36: 		//escape
        {
            if(estado==1){
                CambioEstado(2);
            }
            else if(estado==2){
                CambioEstado(1);
            }
            else if(estado==3){
                if(opciones->getJuego()){
                    CambioEstado(1);
                }else
                    CambioEstado(0);
            }
            
            break;
        }
        case 58: 		//enter
        {
            if(estado==0)
            {
                int estm=menu->getEstado();
                if(estm==3)
                {
                    estado=2;
                    opciones->setJuego(true);
                }
                if(estm==2)
                {
                    estado=3;   //opciones
                }
                if(estm==1)
                {
                    fachada->cerrar();
                }
                
            }
            if(estado==1){
                int estp=pausa->getEstado();
                if(estp==3)
                {
                    estado=2;
                }
                if(estp==2)
                {
                    estado=3;   //opciones
                }
                if(estp==1)
                {
                    estado=0;
                }
            }
            break;
        }
        case 71: 		//izquierda
        {
            if(estado==4){
                if(opciones->getEstado()==5)
                    opciones->update(0,false,opciones->getShadow());
                if(opciones->getEstado()==4)
                    opciones->update(0,opciones->getSound(),false);
            }
            
            break;
        }
        case 72: 		//derecha
        {
            if(estado==4){
                if(opciones->getEstado()==5)
                    opciones->update(0,true,opciones->getShadow());
                if(opciones->getEstado()==4)
                    opciones->update(0,opciones->getSound(),true);
            }
            
            break;
        }
        case 73: 		//arriba
        {
            if(estado==0){
                menu->update(1);
            }
            if(estado==1){
                pausa->update(1);
            }
            if(estado==3){
                opciones->update(1,opciones->getSound(),opciones->getShadow());
            }
            break;
        }
        case 74: 		//abajoo
        {
            if(estado==0){
                menu->update(-1);
            }
            if(estado==1){
                pausa->update(-1);
            }
            if(estado==3){
                opciones->update(-1,opciones->getSound(),opciones->getShadow());
            }
            break;
        }

        case 14:                        //O    -   Cambiamos el modo de visualizacion de bounding boxes
        {
            if(fachada->getBounding())
                fachada->setBounding(false);
            else
                fachada->setBounding(true);
            break;
        }

        case 15:    // TECLA P - Realizar ataque

        {
            if(prota->getCombate() && prota->getTiempoAtaque()>=0.5)
            {
                prota->setAtaque(true);
            }
            break;
        }
    }

    if(prota->getCombate()==false || prota->getTiempoAtaque()<0.5)
    {
        prota->setAtaque(false);
    }
        
	if(sf::Joystick::isConnected(0)){
		JoyY=sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		JoyX=sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		////std::cout<<JoyX<<"\n";
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
      		    prota->setEnergia(-2.f,0.2f);
    		}else
		  prota->setCorrer(false);
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||JoyX>=50){//D

            prota->setDireccion(1);
            prota->movimiento(0.1f);
    		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)||sf::Joystick::isButtonPressed(0, 5))
    		{
		  prota->setCorrer(true);
      		  
    		}else
		  prota->setCorrer(false);
        }
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||sf::Joystick::isButtonPressed(0, 0)){
        	prota->setSalto(true);
    	}else
		prota->setSalto(false);
        
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||JoyY>=50)//W
    {
        prota->setPosCombate(1);
        
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)||JoyY<=-50)
    {
        prota->setPosCombate(3);
    }
    else
        prota->setPosCombate(2);
   // if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
   //     
   // }
	       
}
/* Funcion para activar/desactivar el combate y atacar */
void Mundo::checkCombate()
{
    /* Control del ataque (Solo si el combate esta activado) */
    if(prota->getCombate())
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)||sf::Joystick::isButtonPressed(0, 2))
        {  
            prota->setAtaque(true);
        }
        else
        {
            prota->setAtaque(false);  
        }
    }
}

void Mundo::camUpdate(const glm::f32 frameDeltaTime){
    int posm=menu->getEstado();
    int posp=pausa->getEstado();
    int posopc=opciones->getEstado();
    Posicion* protaPosition = prota->getPosition();
	vec3 posCam = cam->getPosicion();
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
    if(estado==3){  ///Opciones
        cam->setPosicion(vec3(30,5000*posopc,-20));
    }
    if(estado==2){  ///Juego
        if(pintaHud){
            cam->setPosicion(vec3(40,5000,-20));
        }
        else
    cam->setPosicion(vec3(-protaPosition->getPosX(),-protaPosition->getPosY()-25,-120)); // cambio 5O A ProtaPosition.Y
    
    }
    if(estado==1){  ///Pausa
        /*
        vec3 posCam=cam->getPosicion();
        posCam.x=20;
        posCam.z=-120;
        posCam.y=0;
        //std::cout<<posCam.y<<endl;
        
      
            while(posCam.y<5000*(posp))
            {
                //std::cout<<posCam.y<<endl;
                //posCam.y=5000*posp;
                posCam.y+=5*frameDeltaTime;
                //posCam.z+=0.1*frameDeltaTime;
                cam->setPosicion(posCam);
                //cam->Rotar(vec3(0,1,0), 3.0f);
            }
            while(posCam.z<-20){
                posCam.z+=0.01f*frameDeltaTime;
                cam->setPosicion(posCam);
            }
            
        */
        cam->setPosicion(vec3(20,5000*posp,-20));
         
        
    }
    if(estado==0){  ///Menu
        cam->setPosicion(vec3(0,5000*posm,-20));
        //cam->Rotar(vec3(0,1,0), 3.0f);
    }
}

void Mundo::fpsControl(){
	
	int fps = 60;

	if (lastFPS != fps)
	{
		lastFPS = fps;
	}

	timeWait();
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
	pintaHud=false;
    camUpdate(5.f);
    fachada->draw();
    pintaHud=true;
    camUpdate(5.f);
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


/* Funcion para hacer la lectura de la logica de los niveles a partir de un xml */ 
void Mundo::cargarNivel()
{
    TiXmlDocument doc;

     switch(nivel){

        case 1: 
        {        
           doc.TiXmlDocument::LoadFile("resources/nivel2.xml",TIXML_ENCODING_UTF8);
           /* CREAMOS EL TERRENO Y COLISIONES DE CAMARA */
           fachada->drawTerreno(1);
           break;
        }

        case 2:
        {
            doc.TiXmlDocument::LoadFile("resources/nivel3.xml",TIXML_ENCODING_UTF8);
            fachada->drawTerreno(2);
           break;
        }
    }

    //OBTENER ELEMENTO MAPA
    TiXmlElement* map = doc.FirstChildElement("map");

    if(map)
    { 
        //MOSTRAR ATRIBUTOS MAPA
        TiXmlAttribute* atri = map->FirstAttribute();
          
        int i=0;
        int ival;
        double dval;
         
          
        while (atri)
        {
          if (atri->QueryIntValue(&ival)==TIXML_SUCCESS)    //muestra su valor entero
          if (atri->QueryDoubleValue(&dval)==TIXML_SUCCESS) //muestra su valor doble
          //printf( "\n" );

          i++;
          atri=atri->Next();

        }

        //OBTENER ELEMENTO TILESET
        TiXmlElement* tileset = map->FirstChildElement("tileset");

        if(tileset)
        { 
            TiXmlAttribute* atri2 = tileset->FirstAttribute();
              
            int i2=0;
            int ival2;
            double dval2;
             
            while (atri2)
            {
              if (atri2->QueryIntValue(&ival2)==TIXML_SUCCESS)    //muestra su valor entero
              if (atri2->QueryDoubleValue(&dval2)==TIXML_SUCCESS) //muestra su valor doble

                i2++;
                atri2=atri2->Next();
                   
            }
          } 

        //OBTENER ELEMENTO LAYER
        TiXmlElement* layer = map->FirstChildElement("layer");//a la misma altura que tileset(hijos de mapa)
        if(!layer)
        { 
            cout <<"Error Layer"<<endl;
        }

        //OBTENER ELEMENTO DATA
        TiXmlElement* data = layer->FirstChildElement("data");//data es hijo de layer
        if(!data)
        { 
            cout <<"Error data"<<endl;
        }

        //OBTENER ELEMENTO OBJECTGROUP
        TiXmlElement* grupo = map->FirstChildElement("objectgroup");//objectgroup es hijo de map
        if(grupo)
        {                     
            //OBTENER ELEMENTO SUELO
            TiXmlElement* obje = grupo->FirstChildElement("object");//object es hjo de objectgroup

            int id;
            int i3=1;
            double altura;
            double ancho;
            double x;
            double y;

            while(obje)
            {
                TiXmlAttribute* atri3 = obje->FirstAttribute();
                          
                while (atri3)
                {
                    if(strcmp(atri3->Name(),"id")==0)
                    {
                        atri3->QueryIntValue(&id);
                    }

                    //OBTENER DIMENSIONES DE LAS CAJAS QUE FORMAN EL SUELO
                    if(strcmp(atri3->Name(),"x")==0)
                    {
                        atri3->QueryDoubleValue(&x);
                    }//CAJAS MAS ALTAS QUE ANCHAS NO TRATARLAS

                    if(strcmp(atri3->Name(),"y")==0)
                    {
                        atri3->QueryDoubleValue(&y);
                    }

                    if(strcmp(atri3->Name(),"width")==0)
                    {
                        atri3->QueryDoubleValue(&ancho);
                    }

                    if(strcmp(atri3->Name(),"height")==0)
                    {
                        atri3->QueryDoubleValue(&altura);

                    }  
                                
                    atri3=atri3->Next();   

                }//atributos
                            
                i3++;
                fachada->CreateGround(world, (int)x, (int)y,(int)ancho, (int)altura);
                obje=obje->NextSiblingElement("object");//pasamos a la siguiente caja

                             
            }//objeto/elemento    


            //TRATAMOS LAS PLATAFORMAS DE UNA FORMA LIGERAMENTE DISTINTA, LOSDEMAS OBJETOS COMPARTEN NUMERO Y TIPODE ATRIBUTOS
            TiXmlElement* grupo2=grupo->NextSiblingElement("objectgroup");
                  
            while(grupo2)
            { 
                double dval9;
                TiXmlAttribute* atriE = grupo2->FirstAttribute();

                while(atriE)
                {
                    atriE->QueryDoubleValue(&dval9)==TIXML_SUCCESS;
                    atriE=atriE->Next();
                }//atributosGrupoEnemigos
                   
                TiXmlElement* ene = grupo2->FirstChildElement("object");//object es hjo de objectgroup

                int idE;        // Identificador de los objects del xml
                int iE;         // No se
                int tipo;       
                double xEn;     // Pos en X del object
                double yEn;     // Pos en Y del object
                int name;
                    
                while(ene)
                {
                    TiXmlAttribute* atriEn = ene->FirstAttribute();
                    iE++;
                    while(atriEn)
                    {
                        if(strcmp(atriEn->Name(),"id")==0)
                        {
                            atriEn->QueryIntValue(&idE);
                        }

                        if(strcmp(atriEn->Name(),"type")==0)
                        {
                            atriEn->QueryIntValue(&tipo);                                                                    
                        }

                        if(strcmp(atriEn->Name(),"x")==0)
                        {
                            atriEn->QueryDoubleValue(&xEn);
                        }

                        if(strcmp(atriEn->Name(),"y")==0)
                        {
                            atriEn->QueryDoubleValue(&yEn);
                        }

                        if(strcmp(atriEn->Name(),"name")==0)
                        {
                            atriEn->QueryIntValue(&name);
                        }

                        atriEn=atriEn->Next();

                    }//atributosEnemigo


                    if(strcmp(grupo2->FirstAttribute()->Value(),"enemigos")==0)
                    {   
                        int nodoI = name/100;
                        int nodoF = name%100;

                        NodoGrafo *nI, *nF;                        
                        for(size_t i=0; i<nodos.size();i++)
                        {
                            if(nodos[i]->getNombre()==nodoI)
                            {
                                nI = nodos[i];
                            }

                            if(nodos[i]->getNombre()==nodoF)
                            {
                                nF = nodos[i];
                            }
                        }


                        p0 = new Posicion(nI->getPosition()->getPosX(),(nI->getPosition()->getPosY()),30.f);
                        pos.push_back(p0);

                        p1 = new Posicion(nF->getPosition()->getPosX(),(nF->getPosition()->getPosY()),30.f);
                        pos.push_back(p1);

                        int t = tipo/10;    // Tipo de enemigo
                        int a = tipo%10;    // TIpo de ataque

                        switch (t)
                        {   
                            case 1: // Enemigos Basicos
                            {
                                enem1 = new EnemigoBasico( pos, 50.0, 1.2, a, this, b, world);
                                enemB.push_back(enem1);
                                addGameObject(enem1);
                                break;
                            }

                            case 2: // Enemigos Avanzados
                            {
                                break;
                            }

                            case 3: // Enemigos Elites
                            {
                                enemE1 = new EnemigoElite( pos, 120.0, 0.8, a, this, b, world);
                                enemE.push_back(enemE1);
                                addGameObject(enemE1);
                                break;
                            }

                        }

                        pos.clear();    // Vaciamos el vector para que no de problemas para el siguiente
                        
                    }   

                    if(strcmp(grupo2->FirstAttribute()->Value(),"recolectables")==0)
                    {
                        int t = tipo%10;    // Tipo de recolectable

                        switch (t)
                        {   
                            case 1: // Agua
                            {
                                posB= new Posicion(xEn-190,-yEn+59,0.f);
                                Bebida *bebida = new Bebida(posB);
                                bebidas.push_back(bebida);
                                addGameObject(bebida);
                                break;
                            }

                            case 2: // Comida
                            {
                                posC= new Posicion(xEn-190,-yEn+59,0.f);
                                Comida *comida = new Comida(posC);
                                comidas.push_back(comida);
                                addGameObject(comida);
                                break;
                            }
                        }
                    } 

                    if(strcmp(grupo2->FirstAttribute()->Value(),"armas")==0)
                    {
                
                    }  

                     if(strcmp(grupo2->FirstAttribute()->Value(),"puerta")==0)
                    {
                
                    }  

                    if(strcmp(grupo2->FirstAttribute()->Value(),"prota")==0) // Posicion inicial del prota
                    {
                        int t = tipo%10;  

                        if(t==1)
                        {
                            prota->CreateBox(world,xEn-190,-yEn+59); // Pos inicial del prota en cada nivel
                        }
                        
                    } 

                    if(strcmp(grupo2->FirstAttribute()->Value(),"alarmas")==0)
                    {
                        posA= new Posicion(xEn-190,-yEn+59,0.f);

                        Alarma* alarm = new Alarma( posA);
                        alarmas.push_back(alarm);
                        addGameObject(alarm);

                        b->setAlarma(alarmas);
                    }  

                    if(strcmp(grupo2->FirstAttribute()->Value(),"fuentes")==0)
                    {
                        posF= new Posicion(xEn-190,-yEn+59,0.f);

                        Fuente* fuente = new Fuente(posF);
                        fuentes.push_back(fuente);
                        addGameObject(fuente);

                        b->setFuente(fuentes);
                    }  

                    if(strcmp(grupo2->FirstAttribute()->Value(),"trampa")==0)
                    {
                        int t = tipo%10;    // Tipo de "trampa"

                        switch (t)
                        {   
                            case 1: // Palanca
                            {
                                break;
                            }

                            case 2: // Trampa pinchos
                            {
                                posT= new Posicion(xEn-190,-yEn+59,0.f);
                                Trampa *trampa = new Trampa(posT);
                                trampas.push_back(trampa);
                                addGameObject(trampa);
                                break;
                            }
                        }
                
                    } 

                    if(strcmp(grupo2->FirstAttribute()->Value(),"nodos")==0)
                    {
                        NodoGrafo *nA = new NodoGrafo(idE,xEn-190, -yEn+60);           
                        nodos.push_back(nA);
                        addGameObject(nA);

                        b->setNodosGrafo(nodos);            // Pasamos los nodos a la blackboard
                    } 

                    if(strcmp(grupo2->FirstAttribute()->Value(),"aristas")==0)
                    {
                        int p = tipo/10;                    // Peso de la arista
                        int t = tipo%10;                    // Tipo de comportamiento

                        Arista *a1 = new Arista(p,t);       // Indicamos peso y tipo de la arista
                        aristas.push_back(a1);

                        int nodoI = name/100;               // Nodo Inicio
                        int nodoF = name%100;               // Nodo FInal
                        
                        NodoGrafo *nI, *nF;                        
                        for(size_t i=0; i<nodos.size();i++)
                        {
                            if(nodos[i]->getNombre()==nodoI)
                            {
                                nI = nodos[i];
                            }

                            if(nodos[i]->getNombre()==nodoF)
                            {
                                nF = nodos[i];
                            }
                        }

                        nI->insertAristaS(a1,nF);
                        

                    } 

                    ene=ene->NextSiblingElement("object");//pasamos a la siguiente caja
                }//enemigo

                grupo2=grupo2->NextSiblingElement("objectgroup");//pasamos a la siguiente caja
            }//grupo2

        }//objectgroup
                  
    }//mapa

}    

/* Funcion para hacer el cambio de nivel cuando se llegue al final */
void Mundo::cambiarNivel()
{
    if(nivel<MAX_NIVEL) // No cambiar nivel si no hay mas
    {
        nivel = nivel +1;

        fachada->destruirBodies();

        b->borrarEnemB();

    /* DELETE DEL GRAFO PROVISIONAL */
    for(size_t cont3=0; cont3<nodos.size();cont3++)
    {
        delete nodos[cont3];
    }
    nodos.clear();

    for(size_t cont4=0; cont4<aristas.size();cont4++)
    {
        delete aristas[cont4];
    }
    aristas.clear();

    /* DELETE DE LOS OBJETOS DEL MAPA */
    for (size_t cont=0; cont<alarmas.size();cont++)
    {
        delete alarmas[cont];
    }
    alarmas.clear();

    for (size_t cont=0; cont<fuentes.size();cont++)
    {
        delete fuentes[cont];
    }
    fuentes.clear();

    for (size_t cont=0; cont<comidas.size();cont++)
    {
        delete comidas[cont];
    }
    comidas.clear();

    for (size_t cont=0; cont<bebidas.size();cont++)
    {
        delete bebidas[cont];
    }
    bebidas.clear();

    for (size_t cont=0; cont<trampas.size();cont++)
    {
        delete trampas[cont];
    }
    trampas.clear();

    delete posA;
    delete posF;
    delete posB;
    delete posC;
    delete posT;
    delete p0;
    delete p1;

        cargarNivel(); // Volvemos a hacer la lectura del xml 
        //cout<<"llego1"<<endl;
    }


}


Mundo::~Mundo()	//DESTRUCTOR
{
	/* DELETE PROTAGONISTA */
	delete prota;

	/* DELETE ENEMIGOS */
	for(size_t cont=0; cont<enemB.size();cont++)
	{
		delete enemB[cont];
	}
	enemB.clear();

	for(size_t cont2=0; cont2<enemE.size();cont2++)
	{
		delete enemE[cont2];
	}
	enemE.clear();

    /* DELETE DEL GRAFO PROVISIONAL */
   	for(size_t cont3=0; cont3<nodos.size();cont3++)
   	{
   		delete nodos[cont3];
   	}
   	nodos.clear();

   	for(size_t cont4=0; cont4<aristas.size();cont4++)
   	{
   		delete aristas[cont4];
   	}
   	aristas.clear();

    /* DELETE DE LOS OBJETOS DEL MAPA */
    for (size_t cont=0; cont<alarmas.size();cont++)
    {
        delete alarmas[cont];
    }
    alarmas.clear();

    for (size_t cont=0; cont<fuentes.size();cont++)
    {
        delete fuentes[cont];
    }
    fuentes.clear();

    for (size_t cont=0; cont<comidas.size();cont++)
    {
        delete comidas[cont];
    }
    comidas.clear();

    for (size_t cont=0; cont<bebidas.size();cont++)
    {
        delete bebidas[cont];
    }
    bebidas.clear();

    for (size_t cont=0; cont<trampas.size();cont++)
    {
        delete trampas[cont];
    }
    trampas.clear();

    delete posA;
    delete posF;
    delete posB;
    delete posC;
    delete posT;
    delete p0;
    delete p1;
    
    
}
