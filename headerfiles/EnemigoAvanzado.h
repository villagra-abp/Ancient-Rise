#ifndef ENEMIGOAVANZADO_H
#define ENEMIGOAVANZADO_H

#include "../headerfiles/Enemigo.h"
class Blackboard;
/*
Clase que define un tipo de enemigo mas avanzado que el basico con algunas mecanicas concretas, dos tipos : melee y distancia
*/
class EnemigoAvanzado : public Enemigo
{

	public:

       EnemigoAvanzado(vector<Posicion*> pos, float xlength, float pendValue, int t, const Entorno* e, Blackboard *b, b2World& world);

        void Update(Posicion* prota);
        virtual void comprobarEnergia() override;
        virtual void CreateBox(b2World& world, float X, float Y) override;

        virtual ~EnemigoAvanzado();


    private:

    	const glm::f32 ENERGIA_MAX=100.f;

};


#endif 



