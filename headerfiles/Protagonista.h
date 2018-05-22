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

        Protagonista();
        static Protagonista* getInstance();
        virtual ~Protagonista();

         FObjeto* getNode();
         void setNode(FObjeto* node);

         void salto(const glm::f32 Time);
         void ataque(EnemigoBasico* e);
         void movimiento(const glm::f32 Time);
         
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
         int getDireccion();
         bool getSalto();
         void setSigilo();
         void setCorrer(bool c);
         void setDireccion(int d);
         void setAtaque(bool d);
         void setEnergia(glm::f32 cantidad, const glm::f32 Time);
         void setVida(glm::f32 cantidad, const glm::f32 Time);
         void setLife(glm::f32 cantidad);
         void setEnergy(glm::f32 cantidad);
         void updateBody(b2World& world);
         bool checkVida();

         /* COMBATE */
         bool getCombate();
         void setCombate();
         void setPosCombate(int n);
         int getPosCombate();
         void checkPosCombate();
         void quitarVida(glm::f32 cantidad);

         b2Body* getBody();


    private:
    
        FObjeto* protaObjeto;
        void * rec;
        void * energy;
        void * life;
        void * flecha0;
        void * flecha1;
        glm::f32 energia;
        glm::f32 vida;
        bool saltando;
        bool sigilo;
        bool correr;
        bool estaEnSuelo;
        bool estaCayendo;
        int direccion;      // Para saber la direccion a la que esta mirando el prota (0 --> Izquierda, 1 --> Derecha, 2--> Reposo)
        glm::f32 VELOCIDAD_MOVIMIENTO=90.f;
        glm::f32 ENERGIA_MAXIMA=100.f;
        glm::f32 VIDA_MAXIMA=100.f;

        Posicion* protaPosition;
        Posicion* enemigoPosition;
        Posicion* comidaPosition;
        Posicion* trampaPosition;

        /* Animaciones */
        bool cambioAnimacion;
        int tipoSalto;              // 1 -> Normal, 2 -> Salto corriendo y 3 -> salto adelante
        sf::Clock tiempoSalto;
        int resetRelojSalto;
        
        
        /* BOX2D */
        b2Body* Body;
        b2BodyDef BodyDef;
        b2PolygonShape Shape;
        short GROUP_PLAYER = -2; 

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
