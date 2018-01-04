#ifndef ENEMIGOBASICO_H
#define ENEMIGOBASICO_H


#include "../headerfiles/Enemigo.h"
#include "../headerfiles/BehaviorTree.h"
#include "../headerfiles/Blackboard.h"


/*
Clase que define el tipo mas basico de enemigo que puede haber, que puede ser a melee o a distancia
*/
class EnemigoBasico : public Enemigo
{
    public:
        EnemigoBasico(IrrlichtDevice *dev, ISceneManager* smgr, vector<Posicion*> pos, float xlength, float pendValue, int t, Blackboard *b);

        void Update(core::vector3df prota, Objeto* alarma);
        void AvistadoProta(core::vector3df prota, Objeto* alarma);
        void AlarmaSonando(scene::ISceneNode *alarma);
        virtual void comprobarEnergia() override;




        virtual ~EnemigoBasico();

    private:
    	Blackboard *black;

    	const f32 ENERGIA_MAX=100.f;


};

#endif // ENEMIGOBASICO_H
