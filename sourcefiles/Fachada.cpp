#include "../headerfiles/Fachada.h"

static Fachada* instance = NULL;



//Con esto hacemos que sea singleton. Solo se puede crear el motorgrafico llamando a getInstance. Esta devuelve el motor si ya estaba creado, y sino lo crea
//Parametros: h-> Alto de la ventana, w-> Ancho de la ventana, fullscreen-> si será pantalla completa o no
Fachada* Fachada::getInstance(int h, int w, bool fullscreen) {
    if (instance == NULL) instance = new Fachada(h, w, fullscreen);
    return (instance);
}
Fachada* Fachada::getInstance() {
    
    return (instance);
}
IrrlichtDevice* Fachada::getDevice(){
	return device;
}

u32 Fachada::getTime(){
    sf::Clock clock; 
	sf::Time elapsed1 = clock.getElapsedTime();
    //std::cout << elapsed1.asSeconds() << std::endl;
    clock.restart();
    return elapsed1.asSeconds() ;
}

//Destructor
Fachada::~Fachada(){
	device->drop();
}

//Constructor. Solo accesible desde getInstance
Fachada::Fachada(int h, int w, bool fullscreen){
	
	sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4.6;
    settings.minorVersion = 3.3;
    /** SUBTITULO DE VENTANA
 Para poner texto en el subtitulo de la ventana. Necesita de una 'L' delante del string
 debido a que lo necesita el motor de irrlicht
**/
    
    ventana= new sf::RenderWindow(sf::VideoMode(h, w), "Ancient Rise");
    ventana->setFramerateLimit(60);
    /*creo una vista*/
	/*creo una vista*/
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.1f, 100.0f);
    ventana->setFramerateLimit(60);
	sf::View view(sf::FloatRect(0, 0, 1000, 600));
	
	view.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	ventana->setView(view);
	ventana->setActive(true);
    /*
    SIrrlichtCreationParameters Parameters;
    Parameters.DriverType = video::EDT_OPENGL; 
    //Parameters.EventReceiver = &receiver;
    Parameters.WindowId = reinterpret_cast<void*>(ventana->getSystemHandle());
    device = createDeviceEx(Parameters);
    driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
    */
    //SIrrlichtCreationParameters Parameters;
    //device = createDeviceEx(Parameters);
	
}
sf::RenderWindow* Fachada::getVentana(){
  return ventana;

}



//Modifica la visibilidad del cursor
void Fachada::cursorVisible(bool f){
	device->getCursorControl()->setVisible(f);

}

//Personaliza el sprite del cursor
void Fachada::cursorPersonalizar(std::string path){

}

//Dibuja todo lo dibujable
void Fachada::draw(int a, int b, int c, int d){
	driver->beginScene(true, true, video::SColor(a,b,c,d));

	smgr->drawAll(); // draw the 3d scene
	device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

	driver->endScene();
}

void Fachada::suspension(){
	device->yield();
}

void Fachada::cerrar(){
	device->closeDevice();
}

void Fachada::destruirObjeto(void* nodo)
{
    FObjeto* node=(FObjeto*)nodo;

    node->isActive(false);
}

/*void Motorgrafico::drawGUI(){
	driver->beginScene(true, true, SColor(255,100,101,140));


	driver->endScene();
}*/



bool Fachada::getVentanaEstado(){
	return device->run();
}



bool Fachada::getVentanaActiva(){
	return device->isWindowActive();
}

video::IVideoDriver* Fachada::getDriver(){
	return driver;
}

scene::ISceneManager* Fachada::getScene(){
	return smgr;
}

gui::IGUIEnvironment* Fachada::getGUI(){
	return guienv;
}

int Fachada::getFPS(){
	return driver->getFPS();
}

void Fachada::setNombreVentana(std::string text){
	wstring wide_string = wstring(text.begin(), text.end());
	const wchar_t* result = wide_string.c_str();

	device->setWindowCaption(result);
}

void Fachada::setNombreVentana(wchar_t* text){
	device->setWindowCaption(text);
}
FObjeto* Fachada::addCube(int x,int y,int z,bool flag){
    /*
    scene::ISceneNode * rec=smgr->addCubeSceneNode();
    
    if (rec)
    {
        
        rec->setPosition(core::vector3df(x,y,z));
        //rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
        rec->setMaterialFlag(video::EMF_LIGHTING, flag);
    }
    */
    FObjeto* enem = new FObjeto();
	
    enem->setMalla("resources/pared.obj");
    enem->Escalar(vec3(2,2,2));
	

	enem->setPosicion(vec3(x,y,z));
	enem->Rotar(vec3(0,1,0), -4.5f);
    
    return enem;
}
FObjeto* Fachada::addSphere(int x,int y,int z,bool flag){
    //scene::ISceneNode * rec=smgr->addSphereSceneNode();
    /*if (rec) 
    {
        
        rec->setPosition(core::vector3df(x,y,z));
        //rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
        rec->setMaterialFlag(video::EMF_LIGHTING, flag);
    }
    */
    
    FObjeto* prota = new FObjeto();
	
    prota->setMalla("resources/esfera.obj");
    prota->Escalar(vec3(2,2,2));
	

	prota->setPosicion(vec3(x,y,z));
	prota->Rotar(vec3(0,1,0), -4.5f);
    
    return prota;
}
FObjeto* Fachada::addMalla(int x,int y,int z,string ruta){
    
    FObjeto* prota = new FObjeto();
	
    prota->setMalla(ruta);
    prota->Escalar(vec3(2,2,2));
	

	prota->setPosicion(vec3(x,y,z));
	//prota->Rotar(vec3(0,1,0), -4.5f);
    
    return prota;
}
Posicion* Fachada::getPosicion(void * nodo){

    FObjeto* node=(FObjeto*)nodo;
    vec3 pos=node->getPosicion();
    Posicion* posicion= new Posicion(pos.x,pos.y,pos.z);
    //std::cout<<posicion->getPosX()<<endl;
    return posicion;
}
Posicion* Fachada::getScala(void * nodo){
    
    scene::ISceneNode * node=(scene::ISceneNode*)nodo;
    core::vector3df esc= node->getScale();
    Posicion* escala = new Posicion(esc.X,esc.Y,esc.Z);
    
    return escala;
}
bool Fachada::setScala(void * nodo,Posicion* scala){
    
    FObjeto * node=(FObjeto*)nodo;
    node->Escalar(vec3(scala->getPosX(),scala->getPosY(),scala->getPosZ()));
    return true;
    
}
bool Fachada::setPosicion(void * nodo,Posicion* pos){

    //std::cout<<pos->getPosX()<<endl;
    FObjeto* node=(FObjeto*)nodo;
    vec3 position=vec3(pos->getPosX(),pos->getPosY(),pos->getPosZ());
    node->setPosicion(position);
    return true;
}
bool Fachada::setMaterialFlag(void * nodo,bool b){
    scene::ISceneNode * node=(scene::ISceneNode*)nodo;
    node->setMaterialFlag(video::EMF_LIGHTING, b);
    return true;
}
bool Fachada::setMaterial(void * nodo,const io::path& ruta){
    scene::ISceneNode * node=(scene::ISceneNode*)nodo;
    node->setMaterialTexture(0,driver->getTexture(ruta));
    return true;
}
//Dibuja la escena
void Fachada::drawEscena(){
	
 /*
    //PRUEBAS MOTOR GRAFICO
    TNodo *AEscena = new TNodo();
    Escena = AEscena;
    TNodo *RotarLuz = new TNodo();
    TNodo *RotarCam = new TNodo();
    TNodo *RotarCoche = new TNodo();
    Escena->addHijoBack(RotarLuz);
    Escena->addHijoBack(RotarCam);
    Escena->addHijoBack(RotarCoche);
    TNodo *TraslaLuz = new TNodo();
    TNodo *TraslaCam = new TNodo();
    TNodo *TraslaCoche = new TNodo();
    RotarLuz->addHijoBack(TraslaLuz);
    RotarCam->addHijoBack(TraslaCam);
    RotarCoche->addHijoBack(TraslaCoche);

    TTransf *TransfRotaLuz = new TTransf();
    TransfRotaLuz->rotar(1.2, 0, 0, 42.0);
	TTransf *TransfRotaCam = new TTransf();
	TransfRotaCam->rotar(1.2, 0, 0, 94.0);
	TTransf *TransfRotaCoche = new TTransf();
	TransfRotaCoche->rotar(1.2, 0, 0, 57.0);

	TTransf *TransfTraslaLuz = new TTransf();
    TransfTraslaLuz->trasladar(20.0, 0, 0);
    TTransf *TransfTraslaCam = new TTransf();
    TransfTraslaCam->trasladar(12.0, 0, 0);
    TTransf *TransfTraslaCoche = new TTransf();
    TransfTraslaCoche->trasladar(52.0, 0, 0);

	RotarLuz->setEntidad(TransfRotaLuz);
	RotarCam->setEntidad(TransfRotaCam);
	RotarCoche->setEntidad(TransfRotaCoche);

	TraslaLuz->setEntidad(TransfTraslaLuz);
	TraslaCam->setEntidad(TransfTraslaCam);
	TraslaCoche->setEntidad(TransfTraslaCoche);


	TLuz *EntLuz = new TLuz();
	TCamara *EntCam = new TCamara();
	TMalla *MallaChasis = new TMalla();

    MallaChasis->cargarMalla("caja");
	
	TNodo *NLuz = new TNodo();
	NLuz->setEntidad(EntLuz);
	TNodo *NCam = new TNodo();
	NCam->setEntidad(EntCam);
	TNodo *NChasis = new TNodo();
	NChasis->setEntidad(MallaChasis);

	TraslaLuz->addHijoBack(NLuz);
    TraslaCam->addHijoBack(NCam);
    TraslaCoche->addHijoBack(NChasis);


    //Escena->draw();
    
    */
}
/*
void Fachada::drawDrawEscena(){
    Escena->draw();
}
*/
void Fachada::drawTerreno(){
/*
	scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(

        "resources/terrain-heightmap.bmp",

        0,                  					// parent node

        -1,                 					// node id

        core::vector3df(-5000, -177, -250),		// position

        core::vector3df(0.f, 0.f, 0.f),     	// rotation

        core::vector3df(40.f, 4.4f, 40.f),  	// scale

        video::SColor ( 255, 255, 255, 255 ),   // vertexColor

        5,                 						// maxLOD

        scene::ETPS_17,             			// patchSize

        4                   					// smoothFactor

        );

    //LE APLICAMOS TEXTURA AL TERRENO

    terrain->setMaterialFlag(video::EMF_LIGHTING, false);
    terrain->setMaterialTexture(0, driver->getTexture("resources/terrain-texture.jpg"));

    //LE APLICAMOS RELIEVE

    terrain->setMaterialTexture(1, driver->getTexture("resources/detailmap3.jpg"));
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
    terrain->scaleTexture(1.0f, 20.0f);
*/
    
	FObjeto* suelo = new FObjeto();
	
    suelo->setMalla("resources/escenario.3DS");
    suelo->Escalar(vec3(700,700,700));
	

	suelo->Mover(vec3(-220,48,30));
	//prota->Rotar(vec3(0,1,0), -3.f);
	
    
    
}
FCamara* Fachada::addCamara(Posicion* p){
 
    //cam = smgr->addCameraSceneNode(0, core::vector3df(p->getPosX(),50,-140), core::vector3df(0,5,0));
	//device->getCursorControl()->setVisible(true);
    
    FCamara* camara = new FCamara();
	camara->Activar();
	vec3 camaraOrigin = vec3(-160,-20,-130);
	//cajita->Unir(cajita2);
	//cajita->Mover(vec3(0,0,4));
	camara->Mover(camaraOrigin);
	//camara->Rotar(vec3(0,1,0), 3.0f);
    
    return camara;
    
}
FLuz* Fachada::addLuz(Posicion* p){
 
    FColor* color = new FColor(1.0f,		1.0f,	1.0f, 1.0f);
	glm::vec4 vColor;

	FLuz* luz = new FLuz(1.0f,color);
	vec3 luzOrigin = vec3(-160,0,-10);
	luz->Mover(luzOrigin);
    
    return luz;
}
