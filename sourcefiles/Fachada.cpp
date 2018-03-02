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
	//mainReceiver=myReceiver;
    smgr->addCameraSceneNode(0, core::vector3df(0,30,-40), core::vector3df(0,5,0));
    
	//device->setWindowCaption(L"Ancient Rise");

	
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
scene::ISceneNode * Fachada::addCube(){
    scene::ISceneNode * cubo=smgr->addCubeSceneNode();
    return cubo;
}
scene::ISceneNode * Fachada::addSphere(){
    scene::ISceneNode * cubo=smgr->addSphereSceneNode();
    return cubo;
}
