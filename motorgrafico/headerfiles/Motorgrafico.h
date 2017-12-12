#ifndef MOTORFISICO_H
#define MOTORFISICO_H


#include <irrlicht/irrlicht.h>
#include <iostream>
#include "Eventlistener.h"
#include "resources.h"

using namespace irr;
using namespace std;

class Motorgrafico {
public:

	virtual ~Motorgrafico();

	static Motorgrafico* getInstance();
    static Motorgrafico* getInstance(int h, int w, bool fullscreen);	

	Eventlistener getListener();
	bool getVentanaEstado();
	bool getVentanaActiva();
	video::IVideoDriver* getDriver();
	scene::ISceneManager* getScene();
	gui::IGUIEnvironment* getGUI();
	IrrlichtDevice* getDevice();
	int getFPS();
	u32 getTime();

	void setNombreVentana(string text);
	void setNombreVentana(wchar_t* text);

	void cursorVisible(bool f);
	void cursorPersonalizar(string path);
	void draw(int a, int b, int c, int d);
	void suspension();
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

	Eventlistener receiver;
};


#endif  //MOTORFISICO_H