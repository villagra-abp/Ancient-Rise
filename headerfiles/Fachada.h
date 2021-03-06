#ifndef FACHADA_H
#define FACHADA_H

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
#include "../motorsonido/headerfiles/GestorSonido.h"
#include <iostream>



using namespace std;

class Fachada {
public:

	virtual ~Fachada();

	static Fachada* getInstance();
    static Fachada* getInstance(int h, int w, bool fullscreen);

	bool getVentanaEstado();
	bool getVentanaActiva();
	
	int getFPS();
	glm::f32 getTime();
    sf::RenderWindow* getVentana();
    Posicion* getPosicion(void * nodo);
    Posicion* getScala(void * nodo);
    bool getBounding(){return bounding;}
    
    
    bool setScala(void * nodo,Posicion* scala);
    bool setPosicion(void * nodo,Posicion* pos);
    bool setMaterialFlag(void * nodo,bool b);
    bool setMaterial(void * nodo,std::string ruta);
    void setBounding(bool flag);
    bool setSkybox(FSkybox* skybox);
    void activarPalanca(bool b);
    bool getPalancaActiva();
    
	void setNombreVentana(std::string text);
	void setNombreVentana(wchar_t* text);

	void cursorVisible(bool f);
	void cursorPersonalizar(std::string path);
	void draw();
	void suspension();
	void cerrar();
	void destruirObjeto(void* nodo);
	void destruirBodies();

    FObjeto* drawTerreno(int nivel);
    void addMenu(int t);
    void addFlecha(int pos);
    
    
	void setMalla(void* malla,string ruta);
    void setVolumen(float nivel);
    FObjeto* addCube(int x,int y,int z,bool flag);
    FObjeto* addSphere(int x,int y,int z,bool flag);
    FObjeto* addMalla(float x,float y,float z,string ruta);
    FBillboard* addBillboard(float x,float y,float z,string ruta);
    FObjeto* addAnimacion(int x, int y, int z, string path, FObjeto* objeto);
    FObjeto* resetAnimacion(FObjeto* objeto);
    FObjeto* crearProta();
    FCamara* addCamara(Posicion*);
    FLuz* addLuz(Posicion*);
    FLuz* addLuzDireccional(Posicion* p);
    FLuz* addLuzDirigida(Posicion* p, Posicion* d);
    FSkybox* addSkybox(vector<string> paths);

    void rotObj(void* o, float x, float y, float z, float angulo);
    void setRotObj(void* o, float x, float y, float z, float angulo);
    void movObj(void* o, float x, float y, float z);
    
    void CreateGround(b2World& world, float X, float Y,float largo, float ancho);

private:
	Fachada(int h, int w, bool fullscreen);
	
    
    FObjeto* prota;
    sf::RenderWindow* ventana;

    TNodo* Escena;
    
    //MOTOR GRAFICO
    TMotorTAG* motorgrafico = TMotorTAG::getInstance();
    
    /* BOX2D */
    b2BodyDef BodyDef;
    b2PolygonShape Shape;
    vector <b2Body*> bodies;

    sf::Clock reloj; 
        
    bool bounding;
    bool activaPalanca=false;

};


#endif  //FACHADA_H
