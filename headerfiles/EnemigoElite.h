#ifndef ENEMIGOELITE_H
#define ENEMIGOELITE_H


#include "../headerfiles/Enemigo.h"
#include "../headerfiles/BehaviorTree.h"


/*
Clase que define el tipo de enemigo mas fuerte, con mecanicas especiales. Dos tipos : melee y caster
*/
class EnemigoElite : public Enemigo
{
    public:
         EnemigoElite(vector<Posicion*> pos, float xlength, float pendValue, int t, const Entorno* e, Blackboard *b, b2World& world);

        void Update(Posicion* prota);
        virtual void comprobarEnergia() override;
        virtual void CreateBox(b2World& world, float X, float Y) override;




        virtual ~EnemigoElite();

    private:
    	const glm::f32 ENERGIA_MAX=100.f;


};

#endif // ENEMIGOBASICO_H
