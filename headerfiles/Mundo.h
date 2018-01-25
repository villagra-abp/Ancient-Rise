#ifndef MUNDO_H
#define MUNDO_H

#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <GL/gl.h>
#include "../headerfiles/Protagonista.h"
#include "../headerfiles/Posicion.h"
#include "../headerfiles/MyEventReceiver.h"
#include "../headerfiles/EnemigoBasico.h"
#include "../headerfiles/EnemigoAvanzado.h"
#include "../headerfiles/EnemigoElite.h"
#include "../headerfiles/Comida.h"
#include "../headerfiles/Fuente.h"
#include "../headerfiles/Alarma.h"
#include "../headerfiles/Trampa.h"
#include "../headerfiles/Bebida.h"
#include "../headerfiles/Blackboard.h"
#include "../headerfiles/BehaviorTree.h"

#include "../motorsonido/headerfiles/GestorSonido.h"



#include <iostream>
#include <unistd.h>
#include <irrlicht/irrlicht.h>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace irr; // Para poder usar cualquier clase del motor Irrlicht se utiliza el namespace irr
using namespace std;

/*
Estos son los 5 sub namespace del motor de Irrlicht

1º irr::core--> En este podemos encontrar las clases basicas como vectores, planos, arrays, listas y demas
2º irr::gui--> Contiene clases utiles para la facil creacion de una interfaz grafica de usuario
3º irr::io-->  Proporciona interfaces para la entrada/salida. Lectura y escritura de ficheros, acceso a ficheros zip, ficheros xml..
4º irr::scene--> Se encuentra toda la gestion de la escena
5º irr::video--> Contiene clases para acceder al driver del video. Todo el rendererizado 3d o 2d se realiza aqui
*/

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Mundo
{
    public:
    	//DEFINICION DE TIPOS
    	typedef vector<Posicion*> patrulla;
    	typedef vector<EnemigoBasico*> enemigosBasicos;
        typedef vector<EnemigoElite*> enemigosElites;

    	//CONSTRUCTOR Y DESTRUCTOR
        Mundo(IrrlichtDevice* mainDevice, MyEventReceiver* mainReceiver);
        virtual ~Mundo();

        //UPDATERS
        void update();

        void draw();

    protected:
    /* METHODS */

    	//BUILDERS
        void posBuilder();
        void terrainBuilder();

        //UPDATERS
        void protaUpdate(const u32 now, const f32 frameDeltaTime, f32 tiempo);
        void camUpdate(const f32 frameDeltaTime);
        void fpsControl();
        void timeWait();


 	/* VARIABLES */

    	//EVENTS
    	MyEventReceiver* receiver;

    	//DEVICE
    	IrrlichtDevice* device;

    	//ESCENA
    	IVideoDriver* 		driver;
    	ISceneManager* 		smgr;
    	IGUIEnvironment* 	guienv;

    	//PROTAGONISTA
    	Protagonista*		prota;
    	scene::ISceneNode*	rec;
    	scene::ISceneNode* 	Terrain;

    	//POSICIONES ENEMIGOS
    	patrulla pos, pos2, pos3;	//Vector de posiciones para los enemigos

    	//OBJETOS
    	Comida *c;
    	Fuente *f;
    	Alarma *a;
	    Trampa *t;
	    Bebida *bebida;

    	//BLACKBOARD
    	Blackboard *b;

    	//ENEMIGOS
    	enemigosBasicos enemB;	//Vector de enemigos Basicos
    	EnemigoBasico 	*enem1, *enem2;

        enemigosElites enemE;
        EnemigoElite *enemE1;

    	//PLATAFORMAS
    	scene::ISceneNode* Plataforma;
	    scene::ISceneNode* Plataforma2;
	    scene::ISceneNode* Plataforma3;

    	//CAMARA
    	scene::ICameraSceneNode* cam;

    	//TERRENO
    	scene::ITerrainSceneNode* terrain;

    	//COLISIONES
    	scene::ITriangleSelector* 	selector;
    	scene::ISceneNodeAnimator* 	anim;

    	//TIME AND FRAMES
        int lastFPS;
    	u32 then;
    	u32 time_input;

    	//MUNDO BOX2D
    	b2Vec2 gravedad=b2Vec2(0.f, -9.8f*20);
    	b2World world=b2World(gravedad);

         /* VARIABLES PARA RECUPERACION DE ENERGIA PROTAGONISTA */
        float energiaAnterior;
        float energiaActual;
        float energiaDelta;
        sf::Clock relojDescanso;
        float tiempoTrans;

        //Sonido

        GestorSonido* sonido;
        Reverb* reverbCueva;
        Sonido* musicaBosque;


    private:
};

#endif // MUNDO_H
