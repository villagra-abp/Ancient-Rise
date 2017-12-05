#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <irrlicht/irrlicht.h>
#include <iostream>
#include "Posicion.h"
#include <vector>



using namespace irr;
using namespace std;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class Enemigo
{
    public:
        Enemigo(IrrlichtDevice *dev, ISceneManager* smgr, Posicion *posiciones[]);
        void Patrulla(const f32 Time, Posicion *posiciones[], float protaPosition);
        void Perseguir(vector3df EnemigoPosition, float enemigoX, float protaPosition, const f32 Time);
        void ComprobarDistancia(vector3df EnemigoPosition, int distanciaObjetivoX, const f32 Time);


        //Getters y Setters

        scene::ISceneNode* getNode();
        bool getEstadoAlarma();
        bool getEstadoAvistadoProta();
        //bool [] getEstadoEstadisticas();

        void setPatrulla(bool p);
        void setSed(f32 se);
        void setEnergia(f32 e);
        void setHambre(f32 h);
        void setSalud(f32 s);
        void setVelocidad(f32 v);

        virtual ~Enemigo();

    private:
        scene::ISceneNode * enemigo;
        //Posicion *posPatrulla[];  // INDICA TODAS LAS POS DE LA PATRULLA DEL ENEMIGO
        int contadorPatrulla;     // PARA SABER LA POSICION EN LA QUE SE ENCUENTRA EN LA PATRULLA
        int direccion;            // PARA SABER A LA DIRECCION QUE ESTA MIRANDO EL ENEMIGO 0 --> Izquierda, 1 --> Derecha


        //ESTADISTICAS
        f32 energia;
        f32 sed;
        f32 hambre;
        f32 salud;
        f32 VELOCIDAD_ENEMIGO;     // VELOCIDAD DEL ENEMIGO

        // ESTADOS
        bool patrulla;            // PATRULLANDO O NO
        bool avistadoProta;       // PROTAGONISTA AVISTADO O NO
        bool alarma;              // ALARMA SONANDO O NO
        bool estadisticas[3];     // ARRAY DE BOOLEANOS CON LAS ESTADISTICAS DEL ENEMIGO

};

#endif // ENEMIGO_H
