#include "../headerfiles/Mundo.h"

Mundo::Mundo():prota(nullptr),b(nullptr),enem1(nullptr),enemE1(nullptr), cam(nullptr),posA(nullptr), posF(nullptr), p1(nullptr),
p0(nullptr), posC(nullptr), posB(nullptr), posT(nullptr), salidaNivel(nullptr), posP(nullptr), menu(nullptr), pausa(nullptr),
hud(nullptr), opciones(nullptr), carga(nullptr), protaPosition(nullptr)	//CONSTRUCTOR
{
    Fachada* fachada=fachada->getInstance();

    nivel = 1; 
    nivelAnterior = 0 ;

    cargado = false;

    /*CREAMOS GESTOR DE SONIDO*/
    sonido = GestorSonido::getInstance();

    /* CREAMOS LA BLACKBOARD */
    b=new Blackboard();

    /** ESTABLECEMOS LA CAMARA
     Aqui indicamos la posicion de la camara en el espacio 3d. En este caso,
     esta mirando desde la posicion (0, 30, -40) a la (0, 5, 0) donde es
     aproximadamente donde esta el objeto.
    **/
    Posicion* camaraPos = new Posicion(-100,50,-140);
        
    cam = fachada->addCamara(camaraPos);

    /* AÑADIMOS UNA LUZ */   
//    Posicion* luzPos=camaraPos;
//    fachada->addLuz(luzPos);
    Posicion* dir = new Posicion(0,-1,-1);
    fachada->addLuzDireccional(dir);
//    Posicion* d = new Posicion(0,1,0);
//    Posicion* origen = new Posicion(0,65,0);
//    fachada->addLuzDirigida(origen,d);

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
        
    Posicion posOpc(-30.f,-5000.f,.5f);
    opciones = new Opciones(&posOpc);

    Posicion posCarga(-40.f,-5000.f,.5f);
    carga = new PantallaCarga(&posCarga);
    
    Posicion posMuerte(50.f,-5000.f,.5f);
    muerte = new Muerte(&posMuerte);

    musicaNivel = sonido->createMusic(sonido->SOUND_MUSIC_MENU);


}	

void Mundo::update()
{
    if(estado==4)  // Estado de pantalla de carga
    {   
        //cout<<"NIvel :"<<nivel<<endl;
        //cout<<"Pantalla "<<carga->getPantallaCarga()<<endl;
        if(cont==0 && loading==false) // Reset del reloj de carga
        {
            //cout<<"entro"<<endl;
            relojCarga.restart();
            cont = 1;
        }

        carga->update();

        if(cargado==false && loading==true)
        {
            //cout<<"Cargando "<<endl;
            cargaNivel(); // Carga del nivel 
            estado = 2;
            cargado = false;
        }

        /* Comprobamos que pantalla de carga es */
        if(carga->getPantallaCarga()==1)
        {
            if(loading==true)
            {
                loading = false;
            }
            else
            {
                loading = true;
            }

            cont = 0;
        }
        else
        {
            if(carga->getPantallaCarga()==2 || carga->getPantallaCarga()==3)
            {
                int time = relojCarga.getElapsedTime().asSeconds();      // OBTENEMOS SU DURACION EN SEGUNDOS
               // cout<<time<<endl;
                if(time>3)
                {
                    //cout<<"entroTIme"<<endl;
                    if(loading==true)
                    {
                        loading = false;
                    }
                    else
                    {
                        loading = true;
                    }
                    cont = 0;
                }
            }
        }

    }

    if(estado==2) // Jugando 
    {
        //cout<<nivel<<endl;
        if(prota->checkVida()==false) // Prota muerto hay que reiniciar el nivel
        {
            int aux = sonido->playRandomSound(muerteProtaS);
            if(aux != -1) muerteProtaS[aux]->getCanal()->setGrupoCanales(sonido->getGrupoAmbiente());
            estado=5;   //pantalla de muerte
            //muerteProta();
        }

      
        controlCambioNivel();  // Para comprobar si hay que cambiar de nivel o no


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
        for(size_t i=0; i<palancas.size();i++)
        {
            if(palancas[i]->getNode()!=nullptr)
            {
                //cout<<palancas.size()<<endl;
                prota->comprobarColision(palancas[i]);
                palancas[i]->update();
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
        //Comprueba las entradas del teclado
        checkInput(-1);

        /* UPDATE DE LOS ENEMIGOS */
        for(size_t i=0; i<enemB.size();i++)   		// Enemigos Basicos
        {
            if(enemB[i]->getNode()!=nullptr) 	// Solo si existen hacemos su update
            {
        	   enemB[i]->updateTiempo(frameDeltaTime);
        	   enemB[i]->Update(prota->getPosition());
		    if(nivel==3)
		       {
			 enemB[i]->setInvisible();  
		       }
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
        /*UPDATE DE SONIDO*/
        sonido->playSound(musicaNivel);
        sonido->update();
        sonido->setListener(prota->getPosition()->getPosX(), prota->getPosition()->getPosY(), prota->getPosition()->getPosZ());
    } else {
        sonido->playSound(musicaNivel);
        sonido->update();
    }

}

void Mundo::protaUpdate(const glm::f32 frameDeltaTime)
{
	Tiempo=Tiempo+frameDeltaTime;

    prota->updateBody(world);

	if(Tiempo>0.3f) 	// HACEMOS QUE LO QUE HAYA DENTRO SE HAGA MENOS VECES POR SEGUNDO
    {
        glm::f32 energia=prota->getEnergia();
        
        prota->update(b);
        Tiempo=0;
            
    }

    /* Velocidad Barra de Energia */
    if(prota->getCorrer() || prota->getSalto()){
    	relojDescanso.restart();
    }

    tiempoTrans = relojDescanso.getElapsedTime().asSeconds();
    //cout<<tiempoTrans<<endl;
    if(tiempoTrans > 2.f)	
    	prota->setEnergia(15,frameDeltaTime);  //CAMBIO 5 a 15
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
                    estado=4;
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
            if(estado==5){
                int estp=muerte->getEstado();
                if(estp==2)
                {
                    muerteProta();;   //reinicia nivel

                    estado=2;

                }
                if(estp==1)
                {
                    fachada->cerrar();
                }
            }
            if(estado==2)
            {
                if(fachada->getPalancaActiva()==true)
                {
                    abrirPuerta=true;
                    fachada->setMalla(palancas[0]->getNode(),"resources/Palanca/Palanca1.obj");
                    
                }
            }
            break;
        }
        case 71: 		//izquierda
        {
            if(estado==3){
                if(opciones->getEstado()==5)
                    opciones->update(0,true,opciones->getShadow());
                if(opciones->getEstado()==4)
                    opciones->update(0,opciones->getSound(),true);
            }
            
            break;
        }
        case 72: 		//derecha
        {
            if(estado==3){
                if(opciones->getEstado()==5)
                    opciones->update(0,false,opciones->getShadow());
                if(opciones->getEstado()==4)
                    opciones->update(0,opciones->getSound(),false);
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
            if(estado==5){
                muerte->update(1);
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
            if(estado==5){
                muerte->update(-1);
            }
            break;
        }

        case 14:      //O    -   Cambiamos el modo de visualizacion de bounding boxes
        {
            if(fachada->getBounding())
                fachada->setBounding(false);
            else
                fachada->setBounding(true);
            break;
        }

        case 15:    // TECLA P - Realizar ataque
        {
            if(estado==2)
            {
                if(prota->getCombate() && prota->getTiempoAtaque()>=0.5)
                {
                    prota->setAtaque(true);
                }
            }
            break;
        }
    } // END SWITCH

    if(estado==2)  // Solo si estamos dentro del juego
    {
        controlProta();
    }   
}

/* Funcion para controlar las teclas que permiten al jugador mover al protagonista */
void Mundo::controlProta()
{

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
            prota->setEnergia(-1.5f,0.2f);
        }else
        prota->setCorrer(false);
    }
    else 
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||JoyX>=50) //D
        {

            prota->setDireccion(1);
            prota->movimiento(0.1f);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)||sf::Joystick::isButtonPressed(0, 5))
            {
                prota->setCorrer(true);
                prota->setEnergia(-1.5f,0.2f);
                      
            }else
                prota->setCorrer(false);
        }
        else // REPOSO
        {
            prota->setDireccion(2);
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||sf::Joystick::isButtonPressed(0, 0))
    {
        if(prota->getCombate()==false)
        {
            prota->setSalto(true);
        }
    }
            
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
    if(estado==2)
    {
        protaPosition = prota->getPosition();
        velo=prota->getBody()->GetLinearVelocity();
    }

    vec3 posCam = cam->getPosicion();
   
   switch(estado)  // La camara se mueve en funcion en que estado del juego estemos
   {
        case 0:  // MENU PRINCIPAL
        {
            cam->setPosicion(vec3(0,5000*posm,-20));
            break;
        }

        case 1: // PAUSA
        {
            cam->setPosicion(vec3(20,5000*posp,-20));
            break;
        }

        case 2: // JUGANDO
        {
            if(pintaHud)
            {
                //cam->setRotacion(vec3(0,1,0), 0.f);
                cam->setPosicion(vec3(40,5000,-20));
            }
	    else if(prota->getCombate())
            {
                for(float i=-115;i<-105;i+=frameDeltaTime*0.001f)
                    {
                        
                        cam->setPosicion(vec3(-protaPosition->getPosX()-5,-protaPosition->getPosY()-25,i)); 
                        
                    } 
            }
            else 
            {
                /*
                if(prota->getDireccion()==0){
                    cam->setRotacion(vec3(0,1,0), -0.10f);
                }
                else
                {
                    cam->setRotacion(vec3(0,1,0), 0.15f);
                }
                */
                if(velo.x>30||velo.x<-30)
                {
                    if(velo.x>30)
                    {
                    velo.x=-velo.x;
                    }
                    for(float i=-115;i>(-112+(velo.x/5));i-=frameDeltaTime*0.001f)
                    {
                        
                            cam->setPosicion(vec3(-protaPosition->getPosX()-5,-protaPosition->getPosY()-25,i)); 
                        
                    }
                }
                else{
                    
                        for(float i=-120;i<-115;i+=frameDeltaTime*0.001f)
                        {
                            cam->setPosicion(vec3(-protaPosition->getPosX()-5,-protaPosition->getPosY()-25,i)); 
                        }
                    }
            }  
            break;
        }

        case 3: // OPCIONES
        {
            cam->setPosicion(vec3(30,5000*posopc,-20));
            break;
        }

        case 4: // PANTALLA DE CARGA
        {
            switch(carga->getPantallaCarga())
            {
                case 1:
                {
                    cam->setPosicion(vec3(58.7,5000*posopc,-23.5));
                    break;
                }

                case 2:
                {
                    cam->setPosicion(vec3(59.2,(5000*posopc)+2,-31));
                    break;
                }

                case 3:
                {
                    cam->setPosicion(vec3(59.5,(5000*posopc)+1.5,-27));
                    break;
                }
            }

            break;
        }
        case 5: // MUERTE
        {
            cam->setPosicion(vec3(-50,5000,-20));
            break;
        }

   } // END SWITCH
    
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
void Mundo::cargarLogicaNivel()
{
    TiXmlDocument doc;

     switch(nivel){

        case 1: 
        {        
           doc.TiXmlDocument::LoadFile("resources/Niveles/nivel3.xml",TIXML_ENCODING_UTF8);
           /* CREAMOS EL TERRENO Y COLISIONES DE CAMARA */
           Terreno = fachada->drawTerreno(2);
           break;
        }

        case 2:
        {
            doc.TiXmlDocument::LoadFile("resources/Niveles/nivel2.xml",TIXML_ENCODING_UTF8);
            Terreno = fachada->drawTerreno(1);
           break;
        }
        case 3:
        {
            doc.TiXmlDocument::LoadFile("resources/Niveles/nivel4.xml",TIXML_ENCODING_UTF8);
            Terreno = fachada->drawTerreno(3);
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
                                enem1 = new EnemigoBasico( pos, 70.0, 1.2, a, this, b, world);
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

                        b->setEnemB(enemB);
                        
                    }   

                    if(strcmp(grupo2->FirstAttribute()->Value(),"recolectables")==0)
                    {
                        int t = tipo%10;    // Tipo de recolectable

                        switch (t)
                        {   
                            case 1: // Agua
                            {
                                posB= new Posicion(xEn-190,-yEn+58,-5.f);
                                Bebida *bebida = new Bebida(posB);
                                bebidas.push_back(bebida);
                                addGameObject(bebida);
                                break;
                            }

                            case 2: // Comida
                            {
                                posC= new Posicion(xEn-190,-yEn+59,-5.f);
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
                        int t = tipo%10;  

                        switch (t)
                        {   
                            case 1: // Palanca para abrir puerta
                            {
                                posP = new Posicion(xEn-190,-yEn+57,0.f);
                                Palanca* pal = new Palanca(posP);
                                palancas.push_back(pal);
                                addGameObject(pal);
                                break;
                            }

                            case 2: // Puerta para salir del nivel
                            {
                                if(nivel==3){
                                    salidaNivel = new Posicion(xEn-190,-yEn+58,0.f);
                                }else
                                    salidaNivel = new Posicion(xEn-190,-yEn+58,1000.f);
                                Puerta *p = new Puerta(salidaNivel);
                                puertas.push_back(p);
                                addGameObject(p);
                                break;
                            }
                        }
                
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
                        posA= new Posicion(xEn-190,-yEn+57,-15.f);

                        Alarma* alarm = new Alarma( posA);
                        alarmas.push_back(alarm);
                        addGameObject(alarm);

                        b->setAlarma(alarmas);
                    }  

                    if(strcmp(grupo2->FirstAttribute()->Value(),"fuentes")==0)
                    {
                        posF= new Posicion(xEn-190,-yEn+57,-10.f);

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
                                posT= new Posicion(xEn-190,-yEn+57,0.f);
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

/* FUncion para controlar cuando cambiar de nivel */
void Mundo::controlCambioNivel()
{
    if(prota->getPosition()->getPosX()>=salidaNivel->getPosX()&&abrirPuerta)
    {
        if(prota->getPosition()->getPosY()<salidaNivel->getPosY()+10 && prota->getPosition()->getPosY()>salidaNivel->getPosY()-10 && musicaParada)
        {
            abrirPuerta=false;
            //cout<<"entroControl"<<endl;

            estado = 4;

            if(nivel==1)
            {
                carga->setPantallaCarga(2); // Tiene que ser el del siguiente nivel, no en el que estamos
            }
            else
            {
                if(nivel==2)
                {
                    carga->setPantallaCarga(3);
                }
                else
                {
                    //carga->setPantallaCarga(3);
                }
            } 

            if(nivel<MAX_NIVEL)  // Comprobamos que hay un nivel mas al que pasar
            {
                nivel = nivel +1;
            }
            musicaParada = false;
            //cambiarNivel();
        } 
        else if(prota->getPosition()->getPosY()<salidaNivel->getPosY()+10 && prota->getPosition()->getPosY()>salidaNivel->getPosY()-10 && !musicaParada)
        {
            musicaNivel->getCanal()->stop();
            switch(nivel){
                case 1:
                    musicaNivel = sonido->createMusic(sonido->SOUND_MUSIC_NIVEL2);
                    break;
                case 2:
                    musicaNivel = sonido->createMusic(sonido->SOUND_MUSIC_NIVEL3);
                    break;
                default:
                    musicaNivel = sonido->createMusic(sonido->SOUND_MUSIC_NIVEL1);
                    break;
            }
            musicaParada = true;
        }
    }

}

/* Funcion para resetear el nivel cuando el prota muera */
void Mundo::muerteProta()
{
    /* REseteamos la vida y energia del prota y lo ponemos al principio del nivel en el que se encuentre */
    prota->setEnergy(100);
    prota->setLife(100);

    borradoNivel();     // Para borrar todo lo que hay en el nivel

    cargarLogicaNivel(); // Volvemos a hacer la lectura del xml para cargar toda la logica del nuevo nivel

    b->setProtagonista(prota);

}

/* Funcion para hacer el cambio de nivel cuando sea correspondiente */
void Mundo::cambiarNivel()
{
    //cout<<"entroCoño"<<endl;
    if(nivel<MAX_NIVEL) // No cambiar nivel si no hay mas o no queremos cambiar de nivel. SOlo reset si prota muerto
    {
        //cout<<"entro"<<endl;
        borradoNivel();     // Para borrar todo lo que hay en el nivel
        cargarLogicaNivel(); // Volvemos a hacer la lectura del xml para cargar toda la logica del nuevo nivel

        cargado = true;
    }
}

/* Funcion para hacer toda la carga que falte y sea necesaria para el nivel en el que nos encontremos */
void Mundo::cargaNivel()
{
    switch(nivel)
    {
        case 1:
        {
            /* CREAMOS PROTA */
            prota = new Protagonista();
            addGameObject(prota);

            /* Lectura del XML para la logica del juego */
            cargarLogicaNivel();

            /* Pasamos toda la info necesaria a la blackboard */
            b->setProtagonista(prota);

            /* Creacion del HUD */
            Posicion poshud(-40.5f,-5001.5f,.5f);
            hud = new Hud(&poshud);

            /* Carga de todas las animaciones del prota */
            prota->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/marcha5/marcha5.txt", prota->getNode()));
            prota->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/saltoadelante/saltoadelante.txt", prota->getNode()));
            prota->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/correr/correr.txt", prota->getNode()));
            prota->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/movercombate/movercombate.txt", prota->getNode()));
            prota->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/ataquearriba/ataquearriba.txt", prota->getNode()));
            prota->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/ataquebajo/ataquebajo.txt", prota->getNode()));
            prota->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/ataquemedio/ataquemedio.txt", prota->getNode()));
            prota->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/reposocombate/reposocombate.txt", prota->getNode()));
            prota->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/reposo1/reposo1.txt", prota->getNode()));

            /* Carga de todas las animaciones de los enemigos */
            for(size_t i=0; i<enemB.size();i++)
            {
                enemB[i]->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/marchaE/marchaE.txt", enemB[i]->getFObjeto()));
                enemB[i]->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/correrE/correrE.txt", enemB[i]->getFObjeto()));
                enemB[i]->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/ataquemedioE/ataquemedioE.txt", enemB[i]->getFObjeto()));
                enemB[i]->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/reposocombateE/reposocombateE.txt", enemB[i]->getFObjeto()));
                enemB[i]->setNode(fachada->addAnimacion(0, 0, 10000, "resources/Animaciones/reposoE/reposoE.txt", enemB[i]->getFObjeto()));
            }


            /* Carga de sonidos */
            reverbCueva = sonido->create3DReverb();
            reverbCueva->setAtributos3D(0.0f,0.0f,0.0f, 10.0f, 2000.0f);
            reverbCueva->setTipo(sonido->REVERB_CUEVA);
            musicaNivel->getCanal()->stop();
            musicaNivel = sonido->createMusic(sonido->SOUND_MUSIC_NIVEL1);
            Sonido* aux;
            aux = sonido->create2DSound(sonido->SOUND_PROTA_MUERTE1);
            muerteProtaS.push_back(aux);
            aux = sonido->create2DSound(sonido->SOUND_PROTA_MUERTE2);
            muerteProtaS.push_back(aux);
            break;
        }

        case 2: 
        {   
            cambiarNivel();
            break;
        }

        case 3:
        {
            cambiarNivel();
            break;
        }
    }



    cargado = true;
}

void Mundo::borradoNivel()
{
    fachada->destruirBodies();              // Se destruyen todos los bodies del nivel en el que estabamos

    fachada->destruirObjeto(Terreno);       // Se borra todo el terreno
        

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

    for (size_t cont=0; cont<palancas.size();cont++)
    {
        delete palancas[cont];
    }
    palancas.clear();

    for (size_t cont=0; cont<puertas.size();cont++)
    {
        delete puertas[cont];
    }
    puertas.clear();

    delete posA;
    delete posF;
    delete posB;
    delete posC;
    delete posT;
    delete posP;
    delete p0;
    delete p1;

    gos.clear();

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

    for (size_t cont=0; cont<palancas.size();cont++)
    {
        delete palancas[cont];
    }
    palancas.clear();

    for (size_t cont=0; cont<puertas.size();cont++)
    {
        delete puertas[cont];
    }
    puertas.clear();

   

    delete posA;
    delete posF;
    delete posB;
    delete posC;
    delete posT;
    delete posP;
    delete p0;
    delete p1;
    delete salidaNivel;

    delete menu;
    delete pausa;
    delete opciones;
    delete hud;
    delete carga;
    delete sonido;
    
}
