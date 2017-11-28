#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H


#include <irrlicht/irrlicht.h>


using namespace irr;

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
         void setEnergia(f32 cantidad, const f32 Time);
         void movimiento(const f32 Time);



         //GETTERS Y SETTERS
         void setSalto(bool s);
         core::vector3df getPosition();
         void setPosition(core::vector3df v);
         f32 getEnergia();
         bool getSigilo();
         void setSigilo();
         void setCorrer(bool c);
         void setDireccion(int d);




    private:
        scene::ISceneNode * rec;
        f32 energia;
        bool saltando;
        bool sigilo;
        bool correr;
        int direccion;      // 0 --> Izquierda, 1 --> Derecha
        const f32 VELOCIDAD_MOVIMIENTO=90.f;
        core::vector3df protaPosition;
};

#endif // PROTAGONISTA_H
