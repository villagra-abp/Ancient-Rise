#ifndef ENEMIGO_H
#define ENEMIGO_H



#include "../headerfiles/Posicion.h"
#include "../headerfiles/Objeto.h"
//#include "../headerfiles/BehaviorTree.h"

#include <irrlicht/irrlicht.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <unistd.h>

using namespace irr;
using namespace std;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class BehaviorTree;


class Enemigo
{
    public:
        Enemigo(IrrlichtDevice *dev, ISceneManager* smgr, vector<Posicion*> pos, float xlength, float pendValue);

        void update(core::vector3df prota);
        void updateTiempo(const f32 Time);
        void buscarComida(scene::ISceneNode *comida);
        void actualizarHambre();
        void actualizarSed();
        virtual void comprobarEnergia()=0;
        bool checkInSight(core::vector3df objPos);


        /* Getters y Setters */
        f32 getVelocidad();
        f32 getSed();
        f32 getSalud();
        const f32 getVelNormal();

        int getTipo();
        scene::ISceneNode* getNode();
        bool getAvistadoProta();
        vector <Posicion*> getPosicion();
        float getXRange();
        float getYPend();
        bool getVisto();

        void setSed(f32 se);
        void setEnergia(f32 e);
        void setHambre(f32 h);
        void setSalud(f32 s);
        void setVelocidad(f32 v);
        void setPosition(vector3df v);
        void setAvistadoProta(bool a);
        void setVelHambre(f32 v);
        void setVelSed(f32 v);
        void setXRange(float xRange);
        void setYPend(float yPend);
        void setLastFacedDir(bool dirx);
      

        virtual ~Enemigo();

    protected:
        scene::ISceneNode * enemigo;

        core::vector3df EnemigoPosition;            // VECTOR 3D CON LA POSICION DEL ENEMIGO 
        int contadorPatrulla;                       // PARA SABER LA POSICION EN LA QUE SE ENCUENTRA EN LA PATRULLA
        IGUIEnvironment *env;
        bool encontradoComida;                      // PARA SABER SI HA ENCONTRADO COMIDA
        f32 frameDeltaTime;
        bool avistadoProta;
        vector<Posicion*> posPatrulla;

        const f32 VELOCIDAD_NORMAL = 15.f;          // Constante para saber cual es la velocidad normal de los enemigos que no consume energia

        BehaviorTree *comportamiento;

        /* PARA VISION */
        bool lastFacedDir;
        float visionXmax;
        float valorPendiente;
        bool visto;

        /* ESTADISTICAS DEL ENEMIGO */
        f32 energia;
        f32 sed;
        f32 hambre;
        f32 salud;
        f32 VELOCIDAD_ENEMIGO;                      // VELOCIDAD DEL ENEMIGO


        f32 velHambre;                              // INDICA LA VELOCIDAD A LA QUE BAJA EL HAMBRE
        f32 velSed;                                 // INDICA LA VELOCIDAD A LA QUE BAJA LA SED
        int tipo;                                   // Indica el tipo de enemigo ( 1 = Melee 2 = Distancia)                   



};

#endif // ENEMIGO_H
