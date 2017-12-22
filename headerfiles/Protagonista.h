#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H



#include <irrlicht.h>
#include <iostream>
#include "../headerfiles/Enemigo.h"
#include "../headerfiles/Comida.h"
#include "../headerfiles/Bebida.h"
#include "../headerfiles/Trampa.h"


using namespace irr;
using namespace std;


using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class Protagonista
{
    public:
        Protagonista(IrrlichtDevice *dev, ISceneManager* smgr);
        virtual ~Protagonista();

         scene::ISceneNode* getNode();

         void salto(const f32 Time);
         void ataque(const f32 Time);
         void defender(const f32 Time);
         void movimiento(const f32 Time);
         void recuperarEnergia(const f32 Time);
         void recuperarVida(const f32 Time);
         void pintarInterfaz();
         void comprobarColision(Enemigo *enemigo);
         void comprobarColision(Comida *comida);
         void comprobarColision(Bebida *bebida);
         void comprobarColision(Trampa *trampa);
         bool comprobarColision(scene::ISceneNode* nodo);
         void gravedad(const f32 Time);



         //GETTERS Y SETTERS
         void setSalto(bool s);
         core::vector3df getPosition();
         void setPosition(core::vector3df v);
         f32  getEnergia();
         f32  getVida();

         bool getSigilo();
         bool getCorrer();
         void setSigilo();
         void setCorrer(bool c);
         void setDireccion(int d);

         void setAtaquePosition(int d);
         void setDefensaPosition(int d);
         void setAtaque(bool d);
         void setDefensa(bool d);
         void setEnergia(f32 cantidad, const f32 Time);
         void setVida(f32 cantidad, const f32 Time);
         bool checkVida();





    private:
        scene::ISceneNode * rec;
        scene::ISceneNode * energy;
        scene::ISceneNode * life;
        f32 energia;
        f32 vida;
        bool saltando;
        bool sigilo;
        bool correr;
        bool ataca;
        bool defensa;
        bool estaEnSuelo;
        bool estaCayendo;
        int direccion;      // 0 --> Izquierda, 1 --> Derecha
        int ataque_position;    //0--> abajo.  1--> centro,  2-->arriba
        int defensa_position;    //0--> abajo.  1--> centro,  2-->arriba
        int cont_ataque;
        int cont_defensa;
        int cont_salto;
        int cont_recarga_enemigo;
        const f32 VELOCIDAD_MOVIMIENTO=90.f;
        core::vector3df protaPosition;
        core::vector3df enemigoPosition;
        core::vector3df comidaPosition;
        core::vector3df bebidaPosition;
        core::vector3df trampaPosition;
        core::vector3df energyPosition;
        core::vector3df nodoPosition;
        core::vector3df energyScale;
        core::vector3df lifePosition;
        core::vector3df lifeScale;

};

#endif // PROTAGONISTA_H