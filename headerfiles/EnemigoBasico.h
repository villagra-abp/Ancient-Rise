#ifndef ENEMIGOBASICO_H
#define ENEMIGOBASICO_H


#include "../headerfiles/Enemigo.h"



class EnemigoBasico : public Enemigo
{
    public:
        EnemigoBasico(IrrlichtDevice *dev, ISceneManager* smgr, vector<Posicion*> pos);

        void Update(scene::ISceneNode *alarma);
        void AvistadoProta();
        void AlarmaSonando(scene::ISceneNode *alarma);




        virtual ~EnemigoBasico();

    protected:

    private:

};

#endif // ENEMIGOBASICO_H
