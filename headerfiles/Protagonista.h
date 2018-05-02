#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H



#include "../headerfiles/EnemigoBasico.h"
#include "../headerfiles/Comida.h"
#include "../headerfiles/Bebida.h"
#include "../headerfiles/Trampa.h"
#include "../headerfiles/GameObject.h"
#include "../headerfiles/Fachada.h"
#include "../motorsonido/headerfiles/GestorSonido.h"
#include <SFML/Graphics.hpp>

class Protagonista : public GameObject
{
    public:
        static Protagonista* getInstance();
        virtual ~Protagonista();

         void* getNode();

         void salto(const glm::f32 Time);
         void ataque(EnemigoBasico* e);
         void movimiento(const glm::f32 Time);
         void recuperarEnergia(const glm::f32 Time);
         void recuperarVida(const glm::f32 Time);
         
         void comprobarColision(EnemigoBasico *e);
         void comprobarColision(Enemigo *e);
         void comprobarColision(Objeto *comida);
         void comprobarColision(Bebida *bebida);
         void comprobarColision(Trampa *trampa);
         void gravedad(const glm::f32 Time);
         void CreateGround(b2World& world, float X, float Y,int largo);
         void CreateBox(b2World& world, float X, float Y);
         void update(Blackboard* b);
         void startClock();


         //GETTERS Y SETTERS
         virtual Posicion* getPosition() const override{ return protaPosition; }
         void setSalto(bool s);
         Posicion* getPosition();
         void setPosition(Posicion* v);
         glm::f32  getEnergia();
         glm::f32  getVida();
         bool getSigilo();
         bool getCorrer();
         int getTiempoAtaque();

         void setSigilo();
         void setCorrer(bool c);
         void setDireccion(int d);
         void setAtaque(bool d);
         void setEnergia(glm::f32 cantidad, const glm::f32 Time);
         void setVida(glm::f32 cantidad, const glm::f32 Time);
         void updateBody(b2World& world);
         bool checkVida();

         /* COMBATE */
         bool getCombate();
         void setCombate();
         void setPosCombate(int n);
         int getPosCombate();
         void checkPosCombate();
         void quitarVida(glm::f32 cantidad);




    private:
        
        Protagonista();
        
        void * rec;
        void * energy;
        void * life;
        void * flecha0;
        void * flecha1;
        glm::f32 energia=100.f;
        glm::f32 vida=100.f;
        bool saltando=false;
        bool sigilo=false;
        bool correr=false;
        bool estaEnSuelo=false;
        bool estaCayendo=true;
        int direccion=1;      // Para saber la direccion a la que esta mirando el prota (0 --> Izquierda, 1 --> Derecha)
        float ataque_position=0;    //0--> abajo.  1--> centro,  2-->arriba
        float defensa_position=0;    //0--> abajo.  1--> centro,  2-->arriba
        int cont_ataque=0;
        int cont_defensa=0;
        int cont_salto=0;
        int cont_recarga_enemigo=0;
        const glm::f32 VELOCIDAD_MOVIMIENTO=90.f;

        Posicion* protaPosition;
        Posicion* enemigoPosition;
        Posicion* comidaPosition;
        Posicion* bebidaPosition;
        Posicion* trampaPosition;
        
        
        /* BOX2D */
        b2Body* Body;
        b2BodyDef BodyDef;
        b2PolygonShape Shape;
        short GROUP_PLAYER = -1; 

       /* COMBATE */
        bool combate;                     // PARA SABER SI ESTA COMBATIENDO O NO
        int pos_combate;                 // INDICA LA POSICION DE COMBATE (1 = ARRIBA, 2 = CENTRO, 3 = ABAJO)
        bool ataca=false;               // PROTA ATACANDO O NO
        vector<EnemigoBasico*> enemB;
        sf::Clock relojAtq;
        int contAtq, timeAtq;
        
        /* SONIDO */
        GestorSonido* sonido;
        Sonido* nani;
        Sonido* omae;
        Sonido* grito;
        Sonido* risa;
        
        Fachada* fachada=fachada->getInstance();

};

#endif // PROTAGONISTA_H
