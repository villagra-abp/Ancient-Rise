#ifndef ENEMIGOBASICO_H
#define ENEMIGOBASICO_H


#include "../headerfiles/Enemigo.h"

class Blackboard;
/*
Clase que define el tipo mas basico de enemigo que puede haber, que puede ser a melee o a distancia
*/
class EnemigoBasico : public Enemigo
{
    public:
        EnemigoBasico(IrrlichtDevice *dev, ISceneManager* smgr, vector<Posicion*> pos, float xlength, float pendValue, int t, const Entorno* e, Blackboard *b, b2World& world);


        void Update(Posicion* prota);
        void AlarmaSonando(scene::ISceneNode *alarma);
        virtual void comprobarEnergia() override;
        virtual void CreateBox(b2World& world, float X, float Y) override;




        virtual ~EnemigoBasico();

    private:

    	const f32 ENERGIA_MAX=100.f;


};

#endif // ENEMIGOBASICO_H
