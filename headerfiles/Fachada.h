#ifndef FACHADA_H
#define FACHADA_H


#include <GL/glew.h>
#include <irrlicht/irrlicht.h>
#include "../headerfiles/Posicion.h"
#include <SFML/Window/Window.hpp>
#ifndef GL3_PROTOTYPES 
#define GL3_PROTOTYPES 1 
#endif
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//#include "../motorgrafico/glm/vec3.hpp" // glm::vec3
#include <glm/vec3.hpp>
#include "../motorgrafico/headerfiles/TNodo.h"
#include "../motorgrafico/headerfiles/TTransf.h"
#include "../motorgrafico/headerfiles/TLuz.h"
#include "../motorgrafico/headerfiles/TMalla.h"
#include "../motorgrafico/headerfiles/TCamara.h"
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
    Posicion* getPosicion(void * nodo);
    Posicion* getScala(void * nodo);
    
    
    
    bool setScala(void * nodo,Posicion* scala);
    bool setPosicion(void * nodo,Posicion* pos);
    bool setMaterialFlag(void * nodo,bool b);
    bool setMaterial(void * nodo,const io::path& ruta);
    
	void setNombreVentana(std::string text);
	void setNombreVentana(wchar_t* text);

	void cursorVisible(bool f);
	void cursorPersonalizar(std::string path);
	void draw(int a, int b, int c, int d);
	void suspension();
	void cerrar();
	
	void drawEscena();
	//void drawGUI();
    void drawTerreno();
	
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
