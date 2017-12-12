#include "../headerfiles/Motorgrafico.h"

static Motorgrafico* instance = NULL;



//Con esto hacemos que sea singleton. Solo se puede crear el motorgrafico llamando a getInstance. Esta devuelve el motor si ya estaba creado, y sino lo crea
//Parametros: h-> Alto de la ventana, w-> Ancho de la ventana, fullscreen-> si será pantalla completa o no
Motorgrafico* Motorgrafico::getInstance(int h, int w, bool fullscreen) {
    if (instance == NULL) instance = new Motorgrafico(h, w, fullscreen);
    return (instance);
}
//Si no existe, crea la ventana de 800x600 y sin fullscreen
Motorgrafico* Motorgrafico::getInstance(){
	if (instance == NULL) instance = new Motorgrafico(800,600,false);
    return (instance);
}

IrrlichtDevice* Motorgrafico::getDevice(){
	return device;
}

u32 Motorgrafico::getTime(){
	return device->getTimer()->getTime();
}

//Destructor
Motorgrafico::~Motorgrafico(){
	device->drop();
}

//Constructor. Solo accesible desde getInstance
Motorgrafico::Motorgrafico(int h, int w, bool fullscreen){
	device =
		createDevice( video::EDT_OPENGL, core::dimension2d<u32>(h, w),16, fullscreen, false, fullscreen, &receiver);

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	
    smgr->addCameraSceneNode(0, core::vector3df(0,30,-40), core::vector3df(0,5,0));

	
}




//Modifica la visibilidad del cursor
void Motorgrafico::cursorVisible(bool f){
	device->getCursorControl()->setVisible(f);

}

//Personaliza el sprite del cursor
void Motorgrafico::cursorPersonalizar(string path){

}

//Dibuja todo lo dibujable
void Motorgrafico::draw(int a, int b, int c, int d){
	driver->beginScene(true, true, video::SColor(a,b,c,d));

	smgr->drawAll(); // draw the 3d scene
	device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

	driver->endScene();
}

void Motorgrafico::suspension(){
	device->yield();
}

/*void Motorgrafico::drawGUI(){
	driver->beginScene(true, true, SColor(255,100,101,140));


	driver->endScene();
}*/



bool Motorgrafico::getVentanaEstado(){
	return device->run();
}

Eventlistener Motorgrafico::getListener(){
	return receiver;
}

bool Motorgrafico::getVentanaActiva(){
	return device->isWindowActive();
}

video::IVideoDriver* Motorgrafico::getDriver(){
	return driver;
}

scene::ISceneManager* Motorgrafico::getScene(){
	return smgr;
}

gui::IGUIEnvironment* Motorgrafico::getGUI(){
	return guienv;
}

int Motorgrafico::getFPS(){
	return driver->getFPS();
}

void Motorgrafico::setNombreVentana(string text){
	wstring wide_string = wstring(text.begin(), text.end());
	const wchar_t* result = wide_string.c_str();

	device->setWindowCaption(result);
}

void Motorgrafico::setNombreVentana(wchar_t* text){
	device->setWindowCaption(text);
}