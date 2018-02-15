#ifndef MUNDO_H
#define MUNDO_H

//#include "../headerfiles/Protagonista.h"
//#include "../headerfiles/Posicion.h"
//#include "../headerfiles/EnemigoBasico.h"
//#include "../headerfiles/EnemigoAvanzado.h"
//#include "../headerfiles/EnemigoElite.h"
//#include "../headerfiles/Comida.h"
//#include "../headerfiles/Fuente.h"
//#include "../headerfiles/Alarma.h"
//#include "../headerfiles/Trampa.h"
//#include "../headerfiles/Bebida.h"
//#include "../headerfiles/BehaviorTree.h"
#include "../headerfiles/Entorno.h"
#include "GameObject.h"

#include "../motorsonido/headerfiles/GestorSonido.h"




class Mundo : public Entorno
{
    public:
    	//DEFINICION DE TIPOS
//    	typedef vector<Posicion*> patrulla;
//    	typedef vector<EnemigoBasico*> enemigosBasicos;
//        typedef vector<EnemigoElite*> enemigosElites;
//        typedef vector<GameObject*> GameObjects;
//        typedef vector<Objeto*> objetos;
        
    	//CONSTRUCTOR Y DESTRUCTOR

        Mundo(sf::RenderWindow* mainDevice);
        virtual ~Mundo();

        //MANEJO DE GAMEOBJECTS
        void    addGameObject   (GameObject* o);

       // virtual GameObject* getGameObject(uint8_t pos) const override;

        //UPDATERS
        void update();

        void draw();

	//EVENTS
    	void checkInput();

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

    	

    	//DEVICE
    	sf::RenderWindow* device;




        //SONIDO
        GestorSonido* sonido;
        Reverb* reverbCueva;
        Sonido* musicaBosque;


    private:
};

#endif // MUNDO_H
