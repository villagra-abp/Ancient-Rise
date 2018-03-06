#ifndef FACHADA_H
#define FACHADA_H


#include <irrlicht/irrlicht.h>
#include <SFML/Window/Window.hpp>
#define GL3_PROTOTYPES 1 
//#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "motorgrafico/glm/vec3.hpp" // glm::vec3
#include <iostream>


using namespace irr;
using namespace std;

class Fachada {
public:

	virtual ~Fachada();

	static Fachada* getInstance();
    static Fachada* getInstance(int h, int w, bool fullscreen);	

	bool getVentanaEstado();
	bool getVentanaActiva();
	video::IVideoDriver* getDriver();
	scene::ISceneManager* getScene();
	gui::IGUIEnvironment* getGUI();
	IrrlichtDevice* getDevice();
	int getFPS();
	u32 getTime();
    sf::RenderWindow* getVentana();
    core::vector3df getPosicion(void * nodo);
    core::vector3df getScala(void * nodo);
    
    
    
    bool setScala(void * nodo,core::vector3df scala);
    bool setPosicion(void * nodo,core::vector3df pos);
    bool setMaterialFlag(void * nodo,bool b);
    
	void setNombreVentana(std::string text);
	void setNombreVentana(wchar_t* text);

	void cursorVisible(bool f);
	void cursorPersonalizar(std::string path);
	void draw(int a, int b, int c, int d);
	void suspension();
	void cerrar();
	/*
	void drawEscena();
	void drawGUI();
	*/
    scene::ISceneNode * addCube(int x,int y,int z,bool flag);
    scene::ISceneNode * addSphere(int x,int y,int z,bool flag);

private:
	Fachada(int h, int w, bool fullscreen);
	
    //MyEventReceiver* mainReceiver;
    IrrlichtDevice *device;

	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment* guienv;
    
    sf::RenderWindow* ventana;

};


#endif  //FACHADA_H
