#ifndef ENEMIGOELITE_H
#define ENEMIGOELITE_H


#include "../headerfiles/Enemigo.h"


/*
Clase que define el tipo de enemigo mas fuerte, con mecanicas especiales. Dos tipos : melee y caster
*/
class EnemigoElite : public Enemigo
{
    public:
        EnemigoElite(IrrlichtDevice *dev, ISceneManager *smgr, vector<Posicion*> pos, float xlength, float pendValue, int t);

        void Update(core::vector3df prota, Objeto* alarma);
        virtual void comprobarEnergia() override;
        virtual void CreateBox(b2World& world, float X, float Y) override;




        virtual ~EnemigoElite();

    private:

    	const f32 ENERGIA_MAX=100.f;


};

#endif // ENEMIGOBASICO_H