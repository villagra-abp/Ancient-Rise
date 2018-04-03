#ifndef MUNDO_H
#define MUNDO_H

#include "../headerfiles/Protagonista.h"
#include "../headerfiles/Posicion.h"
#include "../headerfiles/EnemigoBasico.h"
#include "../headerfiles/EnemigoAvanzado.h"
#include "../headerfiles/EnemigoElite.h"
#include "../headerfiles/Comida.h"
#include "../headerfiles/Fuente.h"
#include "../headerfiles/Alarma.h"
#include "../headerfiles/Trampa.h"
#include "../headerfiles/Bebida.h"
#include "../headerfiles/BehaviorTree.h"
#include "../headerfiles/Entorno.h"
#include "../headerfiles/Fachada.h"
#include "../headerfiles/NodoGrafo.h"

#include "../motorsonido/headerfiles/GestorSonido.h"

/*
Estos son los 5 sub namespace del motor de Irrlicht

1º irr::core--> En este podemos encontrar las clases basicas como vectores, planos, arrays, listas y demas
2º irr::gui--> Contiene clases utiles para la facil creacion de una interfaz grafica de usuario
3º irr::io-->  Proporciona interfaces para la entrada/salida. Lectura y escritura de ficheros, acceso a ficheros zip, ficheros xml..
4º irr::scene--> Se encuentra toda la gestion de la escena
5º irr::video--> Contiene clases para acceder al driver del video. Todo el rendererizado 3d o 2d se realiza aqui
*/



class Mundo : public Entorno
{
    public:
    	//DEFINICION DE TIPOS
    	typedef vector<Posicion*> patrulla;
    	typedef vector<EnemigoBasico*> enemigosBasicos;
        typedef vector<EnemigoElite*> enemigosElites;
        typedef vector<GameObject*> GameObjects;
        typedef vector<Objeto*> objetos;
        
    	//CONSTRUCTOR Y DESTRUCTOR
        Mundo();
        virtual ~Mundo();

        //MANEJO DE GAMEOBJECTS
        void    addGameObject   (GameObject* o);

        virtual int     getSize() const { return gos.size(); }
        virtual GameObject* getGameObject(uint8_t pos) const override;

        //UPDATERS
        void update();

        void draw();
        
        void checkInput();
        void checkCombate();
        
        
        int estado=1;

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

        
        int PosFlecha=3;

    	//PROTAGONISTA
    	Protagonista*  prota;
    	

    	//POSICIONES ENEMIGOS
    	patrulla pos, pos2, pos3;	//Vector de posiciones para los enemigos

    	//OBJETOS
    	Comida *c, *c2;
        Fuente *f, *f2;
        Alarma *a, *a2;
        Trampa *t;
        Bebida *bebida;
        vector<Objeto*> alarmas;
        vector<Objeto*> fuentes;
        vector<Objeto*> comidas;

    	//BLACKBOARD
    	Blackboard *b;

    	//ENEMIGOS
    	enemigosBasicos enemB;	//Vector de enemigos Basicos
    	EnemigoBasico 	*enem1, *enem2;

        enemigosElites enemE;
        EnemigoElite *enemE1;

    	//PLATAFORMAS
    	FObjeto* Plataforma;
	    FObjeto* Plataforma2;
	    FObjeto* Plataforma3;

        //GRAFO PATHFINDING
        vector<NodoGrafo*> nodos;            // Contiene todos los nodos del grafo
        vector<Arista*> aristas;

    	//CAMARA
    	FCamara* cam;

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

        //VARIABLES RECUPERACION ENERGIA PROTAGONISTA
        float energiaAnterior;
        float energiaActual;
        float energiaDelta;
        sf::Clock relojDescanso;
        float tiempoTrans;

        //SONIDO
        GestorSonido* sonido;
        Reverb* reverbCueva;
        Sonido* musicaBosque;

        //MANJEO DE GAME OBJECTS
        GameObjects gos;

        //PRUEBAS MOTOR GRAFICO
        vector<TNodo*> nodosGL;
        
        //VARIABLES JOYSTICK
        float JoyY;
        float JoyX;

        Fachada* fachada=fachada->getInstance();
    private:
};

#endif // MUNDO_H
