#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <irrlicht.h>
#include <iostream>
#include "../headerfiles/Posicion.h"
#include <vector>
#include <math.h>




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
        Enemigo(IrrlichtDevice *dev, ISceneManager* smgr, vector<Posicion*> pos);

        void update(const f32 Time, vector<Posicion*> pos, float protaPosition, scene::ISceneNode *fuente, scene::ISceneNode *comida);
        void Perseguir(float enemigoX, float protaPosition);
        void ComprobarDistancia(int distanciaObjetivoX);
        void updateTiempo(const f32 Time);

        void buscarComida(scene::ISceneNode *comida);
        void buscarAgua(scene::ISceneNode *fuente);
        bool buscarDescanso();

        void actualizarHambre();
        void actualizarSed();
        void actualizarEnergia();


        //Getters y Setters

        scene::ISceneNode* getNode();
        bool getEstadoAlarma();
        bool getEstadoAvistadoProta();
        bool getEstadoPatrulla();
        vector <bool> getEstadoEstadisticas();
        f32 getVelocidad();

        void setPatrulla(bool p);
        void setAlarma(bool a);
        void setSed(f32 se);
        void setEnergia(f32 e);
        void setHambre(f32 h);
        void setSalud(f32 s);
        void setVelocidad(f32 v);
        void setPosition(vector3df v);

      

        virtual ~Enemigo();

    private:
        scene::ISceneNode * enemigo;

        core::vector3df EnemigoPosition; // VECTOR 3D CON LA POSICION DEL ENEMIGO 
        int contadorPatrulla;     // PARA SABER LA POSICION EN LA QUE SE ENCUENTRA EN LA PATRULLA
        int direccion;            // PARA SABER A LA DIRECCION QUE ESTA MIRANDO EL ENEMIGO 0 --> Izquierda, 1 --> Derecha
        IGUIEnvironment *env;
        bool encontradoAgua;      // PARA SABER SI HA ENCONTRADO AGUA 
        bool encontradoComida;    // PARA SABER SI HA ENCONTRADO COMIDA
        bool encontradoDescanso;  // PARA SABER SI HA ENCONTRADO UN SITIO PARA DESCANSAR
        f32 frameDeltaTime;




        //ESTADISTICAS
        f32 energia;
        f32 sed;
        f32 hambre;
        f32 salud;
        f32 VELOCIDAD_ENEMIGO;     // VELOCIDAD DEL ENEMIGO


        f32 velHambre;        // INDICA LA VELOCIDAD A LA QUE BAJA EL HAMBRE
        f32 velSed;           // INDICA LA VELOCIDAD A LA QUE BAJA LA SED


        // ESTADOS
        bool patrulla;            // PATRULLANDO O NO
        bool avistadoProta;       // PROTAGONISTA AVISTADO O NO
        bool alarma;              // ALARMA SONANDO O NO

        vector<bool> estadisticas;     // VECTOR DE BOOLEANOS CON LAS ESTADISTICAS DEL ENEMIGO


};

#endif // ENEMIGO_H