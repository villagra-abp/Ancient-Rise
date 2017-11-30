#ifndef ENEMIGOBASICO_H
#define ENEMIGOBASICO_H

#include <Enemigo.h>


class EnemigoBasico : public Enemigo
{
    public:
        EnemigoBasico(IrrlichtDevice *dev, ISceneManager* smgr, Posicion *posiciones[]);
        void comprobarComportamiento();
        void AvistadoProta();
        void AlarmaSonando();



        virtual ~EnemigoBasico();

    protected:

    private:

};

#endif // ENEMIGOBASICO_H
