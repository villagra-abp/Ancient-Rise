#include <irrlicht.h>
#include "../headerfiles/Protagonista.h"
#include <iostream>

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

/*
To be able to use the Irrlicht.DLL file, we need to link with the Irrlicht.lib.
We could set this option in the project settings, but to make it easy, we use a
pragma comment lib for VisualStudio. On Windows platforms, we have to get rid
of the console window, which pops up when starting a program with main(). This
is done by the second pragma. We could also use the WinMain method, though
losing platform independence then.
*/
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


class MyEventReceiver : public IEventReceiver
{
public:

    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        {
           KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
           //keyIsPressed[event.KeyInput.Key] = event.KeyInput.
        }
        /*
        Always return false by default. If you return true you tell the engine
        that you handled this event completely and the Irrlicht should not
        process it any further. So for example if you return true for all
        EET_KEY_INPUT_EVENT events then Irrlicht would not pass on key-events
        to it's GUI system.
        */
        return false;
    }

    /*
    Para saber que tecla esta pulsada
    */

    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }


    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }
    void checkInput(Protagonista *prota,const f32 Time);
    void checkSigilo(Protagonista *prota,const f32 Time);
    void checkCombate(Protagonista *prota);
    void saltar(Protagonista *p,const f32 Time, bool salta);
    void moverse(Protagonista *p,const f32 Time);
    void atacar(Protagonista *p,bool b);
    void defender(Protagonista *p,bool b);
    void ralentizar(Protagonista *p,const f32 Time);
    void sprintar(Protagonista *p,const f32 Time);
    void pos_pelea(Protagonista *p,int n);
    void pos_defensa(Protagonista *p,int n);
    void direccion(Protagonista *p,int n);
    //void checkCombate(Protagonista *prota);

private:

    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    bool keyIsPressed[KEY_KEY_CODES_COUNT];


};
