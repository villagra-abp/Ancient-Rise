#ifndef FACHADA_H
#define FACHADA_H



#include <irrlicht/irrlicht.h>
#include <GL/glew.h>
#include <Box2D/Box2D.h>
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

#include <glm/vec3.hpp>

#include "../motorgrafico/fachada/headerfiles/Fachada.h"
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
	void draw();
	void suspension();
	void cerrar();
	void destruirObjeto(void* nodo);
	
	void drawEscena();
	//void drawDrawEscena();
	//void drawGUI();
    void drawTerreno();
	
    FObjeto* addCube(int x,int y,int z,bool flag);
    FObjeto* addSphere(int x,int y,int z,bool flag);
    FObjeto* addMalla(int x,int y,int z,string ruta);
    FCamara* addCamara(Posicion*);
    FLuz* addLuz(Posicion*);

    void rotObj(FObjeto* o, float x, float y, float z, float angulo);
    void movObj(FObjeto* o, float x, float y, float z);
    
    void CreateGround(b2World& world, float X, float Y,float largo, float ancho);

private:
	Fachada(int h, int w, bool fullscreen);
	
    //MyEventReceiver* mainReceiver;
    IrrlichtDevice *device;

	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment* guienv;
    
    sf::RenderWindow* ventana;

    TNodo* Escena;
    //CAMARA
    	scene::ICameraSceneNode* cam;
    //MOTOR GRAFICO
    TMotorTAG* motorgrafico = TMotorTAG::getInstance();
    
    /* BOX2D */
        b2Body* Body;
        b2BodyDef BodyDef;
        b2PolygonShape Shape;

};


#endif  //FACHADA_H
