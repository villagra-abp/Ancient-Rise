#ifndef ENEMIGO_H
#define ENEMIGO_H


#include "../headerfiles/Objeto.h"
#include "../headerfiles/GameObject.h"
#include "../headerfiles/Entorno.h"
#include "../headerfiles/Fachada.h"
#include "../headerfiles/NodoGrafo.h"


#define SCALE 30.0f

class BehaviorTree;
class Entorno;
class Proyectil;
class Blackboard;

class Enemigo : public GameObject
{
    public:
        Enemigo(vector<Posicion*> pos, float xlength, float pendValue, const Entorno* e, Blackboard *b);

        void update(Posicion* prota);
        void updateTiempo(const glm::f32 Time);
        void actualizarSed();
        void hud();
        void hudCombate();
        virtual void comprobarEnergia()=0;
        
        /* Vision del Enemigo */
        bool checkInSight(Posicion* pos);
        bool see(GameObject* o);
        bool recordarProta();
        void actualizarVistos();
        void changeLastFaceDir();

        virtual void CreateBox(b2World& world, float X, float Y)=0;

        /* Getters y Setters */
        Posicion* getPosition() const override{ return EnemigoPosition; }
        glm::f32 getVelocidad();
        glm::f32 getSed();
        glm::f32 getSalud();
        const glm::f32 getVelNormal();
        int getTipo();
        int getClaseEnemigo();
        void* getNode();
        bool getAvistadoProta();
        vector <Posicion*> getPosicion();
        float getXRange();
        float getYPend();
        bool getVisto();
        bool getLastFaceDir();
        b2Body* getBody();
        b2Vec2 getVelocidad2d();
        bool getUltDirecVisto();
        int getOrden();
        bool getDisparo();
        Objeto* getAlarmaActivar();
        bool getSaltando();
        bool getVuelta();
        bool getInterrumpido();
        glm::f32 getVelRapida();
        glm::f32 getEnergia();
        bool getRecargandoEnerg();


        void setSed(glm::f32 se);
        void setEnergia(glm::f32 e);
        void setSalud(glm::f32 s);
        void setVelocidad(glm::f32 v);
        void setPosition(Posicion* v);
        void setAvistadoProta(bool a);
        void setVelHambre(glm::f32 v);
        void setVelSed(glm::f32 v);
        void setXRange(float xRange);
        void setYPend(float yPend);
        void setLastFacedDir(bool dirx);
        void setUltDirecVisto(bool v);
        void setOrden(int o);
        void setDisparo(bool d);
        void setAlarmaActivar(Objeto *a);
        void setSaltando(bool s);
        void setInvisible();
        void setVuelta(bool v);
        void setInterrumpido(bool i);

        /* COMBATE */   
        void setCombate(bool b);
        bool getCombate();
        void setPosCombate(int n);
        int getPosCombate();
        Proyectil* getProyectil();
      

        virtual ~Enemigo();

    protected:
        void * enemigo;
        void * energy;
        void * life;
        void * flecha0;
        void * flecha1;
        //void *dep1, *dep2, *dep3, *dep4;          // Para poder ver visualmente el rango de vision de los enemigos
        
        Posicion* EnemigoPosition;                  // VECTOR 3D CON LA POSICION DEL ENEMIGO 
        int contadorPatrulla;                       // PARA SABER LA POSICION EN LA QUE SE ENCUENTRA EN LA PATRULLA
        
        bool encontradoComida;                      // PARA SABER SI HA ENCONTRADO COMIDA
        glm::f32 frameDeltaTime;

        BehaviorTree *comportamiento;               // Comportamiento del enemigo definido mediante un arbol de comportamiento (BEHAVIOR TREE)
        Blackboard *board;
        Objeto *alActivar;                          // Para saber que alarma tiene que activar el enemigo

        /* PARA LA VISION */
        bool lastFacedDir;                          // Para saber a que lado esta mirando el enemigo  (True -> Derecha / False -> Izquierda)
        float visionXmax;                           //
        float valorPendiente;                       // Valores para establecer el rango de vision de los enemigos
        bool visto;                                 // Si ha visto al prota o no
        bool direccVistoUlt;                        // Para saber por que lado vio por ultima vez al protagonista (True -> Derecha / False -> Izquierda)     
        vector<GameObject*> vistos;              

        /* ESTADISTICAS DEL ENEMIGO */
        glm::f32 energia;
        glm::f32 sed;
        glm::f32 salud;
        glm::f32 velHambre;                         // INDICA LA VELOCIDAD A LA QUE BAJA EL HAMBRE
        glm::f32 velSed;                            // INDICA LA VELOCIDAD A LA QUE BAJA LA SED
        int tipo;                                   // Indica el tipo de enemigo ( 1 = Melee 2 = Distancia) 
        int claseEnemigo;                           // Indica que clase enemigo es (1 = Basico, 2 = Avanzado, 3 = Elite )       
        const glm::f32 VELOCIDAD_NORMAL = 10.f;     // Constante para saber cual es la velocidad normal de los enemigos que no consume energia (CAMINANDO)
        const glm::f32 VELOCIDAD_RAPIDA = 20.f;     // Constante para saber cual es la velocidad que consume energia para ir mas rapido (CORRIENDO)  
        bool saltando;
        bool recargandoEnergia;


         /* BOX2D */
        b2Body* Body;
        b2BodyDef BodyDef;
        b2PolygonShape Shape;
        b2Vec2 velocidad2d;
        short GROUP_ENEMIGOS = -2;                   // PARA EVITAR QUE COLISIONEN OBJETOS DEL MISMO GRUPO

        /* PATHFINDING */
        vector<NodoGrafo*> nodos;                    // CONTIENE TODOS LOS NODOS DEL GRAFO
        vector<Posicion*> patrulla;                 // CONTIENE TODAS LAS POS DE LA PATRULLA DEL ENEMIGO
        Posicion* nodoPosition;
        bool vuelta;                                // Para saber si el enemigo esta volviendo a su patrulla o no
        bool interrupcion;                          // Si interrumpen al enemigo durante su camino de vuelta y que vuelva a calcular el camino desde donde se encuentra ahora

        /* MEMORIA */ 
        sf::Clock reloj;                            // Reloj para controlar el tiempo que tiene que estar huyendo
        int contador;                               // Para reiniciar el reloj cuando toca
        bool memoria;

        /* COMBATE */
        bool combate;                               // PARA SABER SI ESTA COMBATIENDO O NO
        int pos_combate;                            // INDICA LA POSICION DE COMBATE (1 = ARRIBA, 2 = CENTRO, 3 = ABAJO)
        bool ataca=false;                           // PROTA ATACANDO O NO
        bool disparo;                               // Para saber si tiene que disparar un proyectil o no
        Proyectil *proyectil;

         /* ENTORNO, GAMEOBJECTS */
        const Entorno *ent;
        int orden;                                  // Para saber si ha recibido una orden o no el enemigo basico (1--> Ataque, 2 --> Activar Alarma, 3->Explorar, 4->IrALarma)
        

        Fachada* fachada=fachada->getInstance();

        bool inv;
};

#endif // ENEMIGO_H
