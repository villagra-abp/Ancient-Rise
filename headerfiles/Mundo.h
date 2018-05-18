#ifndef MUNDO_H
#define MUNDO_H

#include "../headerfiles/Protagonista.h"
#include "../headerfiles/Posicion.h"
#include "../headerfiles/EnemigoBasico.h"
#include "../headerfiles/EnemigoAvanzado.h"
#include "../headerfiles/EnemigoElite.h"
#include "../headerfiles/Comida.h"
#include "../headerfiles/Palanca.h"
#include "../headerfiles/Puerta.h"
#include "../headerfiles/Fuente.h"
#include "../headerfiles/Alarma.h"
#include "../headerfiles/Trampa.h"
#include "../headerfiles/Bebida.h"
#include "../headerfiles/BehaviorTree.h"
#include "../headerfiles/Entorno.h"
#include "../headerfiles/Fachada.h"
#include "../headerfiles/NodoGrafo.h"
#include "../headerfiles/Menu.h"
#include "../headerfiles/Pausa.h"
#include "../headerfiles/Hud.h"
#include "../headerfiles/Opciones.h"
#include <tinyxml.h>

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

        void cambiarNivel();

        //MANEJO DE GAMEOBJECTS
        void    addGameObject   (GameObject* o);

        virtual int     getSize() const { return gos.size(); }
        virtual GameObject* getGameObject(uint8_t pos) const override;

        //UPDATERS
        void update();

        void draw();
        
        void checkInput(int tecla);
        void checkCombate();
        
        void CambioEstado(int n);
        int getEstado();
        void cargarLogicaNivel();
        void controlCambioNivel();
        void cargaNivel();
        void controlProta();
        
        

    protected:
    /* METHODS */

        //UPDATERS
        void protaUpdate(const glm::f32 frameDeltaTime);
        void camUpdate(const glm::f32 frameDeltaTime);
        void fpsControl();
        void timeWait();


 	/* VARIABLES */

        int estado=0;
        int PosFlecha=3;
        bool pintaHud=false;

    	//PROTAGONISTA
    	Protagonista*  prota;
    	
    	//POSICIONES ENEMIGOS
    	patrulla pos;	//Vector de posiciones para los enemigos
        Posicion *p0, *p1;

        // POsiciones Objetos
        Posicion* posA, *posF, *posB, *posC, *posT, *posP;

    	// Vectores de objetos
        vector<Alarma*> alarmas;
        vector<Objeto*> fuentes;
        vector<Comida*> comidas;
        vector<Bebida*> bebidas;
        vector<Trampa*> trampas;
        vector<Palanca*> palancas;
        vector<Puerta*> puertas;

        // Datos gestion del nivel
        int nivel;                     // Nivel en el que nos encontramos
        const int MAX_NIVEL=2;          // Maximo numero de niveles en el juego
        Posicion* salidaNivel;
        bool primeraVez;                // Controla la primera vez que se entra al nivel para la carga

    	//BLACKBOARD
    	Blackboard *b;

    	//ENEMIGOS
    	enemigosBasicos enemB;	//Vector de enemigos Basicos
    	EnemigoBasico 	*enem1;

        enemigosElites enemE;
        EnemigoElite *enemE1;

        //GRAFO PATHFINDING
        vector<NodoGrafo*> nodos;            // Contiene todos los nodos del grafo
        vector<Arista*> aristas;

    	//CAMARA
    	FCamara* cam;

    	void* Terreno;

    	//TIME AND FRAMES
        int lastFPS;
        glm::f32 Tiempo;

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
        
        Hud* hud;
        Menu* menu;
        Pausa* pausa;
        Opciones* opciones;
    private:
};

#endif // MUNDO_H
