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

//Destructor
Motorgrafico::~Motorgrafico(){
	device->drop();
}

//Constructor. Solo accesible desde getInstance
Motorgrafico::Motorgrafico(int h, int w, bool fullscreen){
	device =
		createDevice( video::EDT_OPENGL, core::dimension2d<u32>(h, w),16, fullscreen, false, fullscreen, 0/*&receiver*/);

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

    smgr->addCameraSceneNode(0, core::vector3df(0,30,-40), core::vector3df(0,5,0));

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
        core::rect<s32>(10,10,260,22), true);
}




//Modifica la visibilidad del cursor
void Motorgrafico::cursorVisible(bool f){
	device->getCursorControl()->setVisible(f);

}

//Personaliza el sprite del cursor
void Motorgrafico::cursorPersonalizar(string path){

}

//Dibuja todo lo dibujable
void Motorgrafico::draw(){
	driver->beginScene(true, true, video::SColor(255,100,101,140));

	smgr->drawAll(); // draw the 3d scene
	device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

	driver->endScene();
}

/*void Motorgrafico::drawGUI(){
	driver->beginScene(true, true, SColor(255,100,101,140));


	driver->endScene();
}*/


/*Eventlistener* Motorgrafico::getListener(){
	return receiver;
}*/

bool Motorgrafico::getVentanaEstado(){
	return device->run();
}

void Motorgrafico::setNombreVentana(string text){
	wstring wide_string = wstring(text.begin(), text.end());
	const wchar_t* result = wide_string.c_str();

	device->setWindowCaption(result);
}

void Motorgrafico::setNombreVentana(wchar_t* text){
	device->setWindowCaption(text);
}