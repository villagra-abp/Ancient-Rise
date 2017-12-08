#include <irrlicht/irrlicht.h>
#include <iostream>
//#include "Eventlistener.h"

using namespace irr;
using namespace std;

class Motorgrafico {
public:

	virtual ~Motorgrafico();

	static Motorgrafico* getInstance();
    static Motorgrafico* getInstance(int h, int w, bool fullscreen);	

	//Eventlistener* getListener();
	bool getVentanaEstado();
	
	void setNombreVentana(string text);
	void setNombreVentana(wchar_t* text);

	void cursorVisible(bool f);
	void cursorPersonalizar(string path);
	void draw();
	/*
	void drawEscena();
	void drawGUI();
	*/


private:
	Motorgrafico(int h, int w, bool fullscreen);
	

	IrrlichtDevice *device;

	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment* guienv;

	//Eventlistener receiver;
};