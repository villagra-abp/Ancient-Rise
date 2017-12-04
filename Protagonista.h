#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H


#include <irrlicht/irrlicht.h>
#include <iostream>


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
         void setEnergia(f32 cantidad, const f32 Time);
         void movimiento(const f32 Time);



         //GETTERS Y SETTERS
         void setSalto(bool s);
         core::vector3df getPosition();
         void setPosition(core::vector3df v);
         f32  getEnergia();
         bool getSigilo();
         void setSigilo();
         void setCorrer(bool c);
         void setDireccion(int d);
         void setAtaquePosition(int d);
         void setDefensaPosition(int d);
         void setAtaque(bool d);
         void setDefensa(bool d);
         void pintarInterfaz();




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
        int direccion;      // 0 --> Izquierda, 1 --> Derecha
        int ataque_position;    //0--> abajo.  1--> centro,  2-->arriba
        int defensa_position;    //0--> abajo.  1--> centro,  2-->arriba
        int cont_ataque;
        int cont_defensa;
        const f32 VELOCIDAD_MOVIMIENTO=90.f;
        core::vector3df protaPosition;
        core::vector3df energyPosition;
        core::vector3df energyScale;
        core::vector3df lifePosition;
        core::vector3df lifeScale;
};

#endif // PROTAGONISTA_H