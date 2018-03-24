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
	return device->getTimer()->getTime();
}

//Destructor
Fachada::~Fachada(){
	device->drop();
}

//Constructor. Solo accesible desde getInstance
Fachada::Fachada(int h, int w, bool fullscreen){
	
	
    /** SUBTITULO DE VENTANA
 Para poner texto en el subtitulo de la ventana. Necesita de una 'L' delante del string
 debido a que lo necesita el motor de irrlicht
**/
    
    ventana= new sf::RenderWindow(sf::VideoMode(h, w), "Ancient Rise");
    ventana->setFramerateLimit(60);
    /*creo una vista*/
	//sf::View view(sf::FloatRect(0, 0, 1000, 600));
	
	//view.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	//ventana->setView(view);

	
    SIrrlichtCreationParameters Parameters;
    Parameters.DriverType = video::EDT_OPENGL; 
    //Parameters.EventReceiver = &receiver;
    Parameters.WindowId = reinterpret_cast<void*>(ventana->getSystemHandle());
    device = createDeviceEx(Parameters);
    driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	
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
    scene::ISceneNode * node=(scene::ISceneNode*)nodo;

    node->remove();
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
scene::ISceneNode * Fachada::addCube(int x,int y,int z,bool flag){
    
    scene::ISceneNode * rec=smgr->addCubeSceneNode();
    
    if (rec) /** SI HEMOS CREADO EL CUBO **/
    {
        
        rec->setPosition(core::vector3df(x,y,z));
        //rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
        rec->setMaterialFlag(video::EMF_LIGHTING, flag);
    }
    return rec;
}
scene::ISceneNode * Fachada::addSphere(int x,int y,int z,bool flag){
    scene::ISceneNode * rec=smgr->addSphereSceneNode();
    if (rec) /** SI HEMOS CREADO EL CUBO **/
    {
        
        rec->setPosition(core::vector3df(x,y,z));
        //rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
        rec->setMaterialFlag(video::EMF_LIGHTING, flag);
    }
    return rec;
}
Posicion* Fachada::getPosicion(void * nodo){

    scene::ISceneNode * node=(scene::ISceneNode*)nodo;
    core::vector3df pos=node->getPosition();
    Posicion* posicion= new Posicion(pos.X,pos.Y,pos.Z);
    return posicion;
}
Posicion* Fachada::getScala(void * nodo){
    
    scene::ISceneNode * node=(scene::ISceneNode*)nodo;
    core::vector3df esc= node->getScale();
    Posicion* escala = new Posicion(esc.X,esc.Y,esc.Z);
    
    return escala;
}
bool Fachada::setScala(void * nodo,Posicion* scala){
    
    scene::ISceneNode * node=(scene::ISceneNode*)nodo;
    node->setScale(core::vector3df(scala->getPosX(),scala->getPosY(),scala->getPosZ()));
    return true;
    
}
bool Fachada::setPosicion(void * nodo,Posicion* pos){

    scene::ISceneNode * node=(scene::ISceneNode*)nodo;
    core::vector3df position=core::vector3df(pos->getPosX(),pos->getPosY(),pos->getPosZ());
    cout<<position.X<<" "<<position.Y<<" "<<position.Z<<endl;
    node->setPosition(position);
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
	
    //PRUEBAS MOTOR GRAFICO
    TNodo *Escena = new TNodo();
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
	
	TNodo *NLuz = new TNodo();
	NLuz->setEntidad(EntLuz);
	TNodo *NCam = new TNodo();
	NCam->setEntidad(EntCam);
	TNodo *NChasis = new TNodo();
	NChasis->setEntidad(MallaChasis);

	TraslaLuz->addHijoBack(NLuz);
    TraslaCam->addHijoBack(NCam);
    TraslaCoche->addHijoBack(NChasis);

    Escena->draw();
    
    
}

void Fachada::drawTerreno(){

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
}
