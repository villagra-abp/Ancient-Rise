#ifndef __ENEMIGOSENSOR_H__
#define __ENEMIGOSENSOR_H__

#include <Enemigo.h>
#include <Sensor.h>

class EnemigoSensor : public Enemigo
{
    public:
        EnemigoSensor(Sensor* s, IrrlichtDevice *dev, ISceneManager* smgr, Posicion *posiciones[]);
        virtual ~EnemigoSensor();
        
        virtual void Update() override;
        virtual void AvistadoProta() override;

        virtual bool isPlayer() const override { return false; };

    protected:

    private:
    	Sensor::Dir     	getSeeDir() const; 	//Direccion a la que mira este enemigo
    	const Protagonista* getProtaSeenAtPresentMovementDirection() const;

    	int8_t   	m_dir;     			// Direccion de movimiento
    	Sensor*		v_sensor; 			//Sensor para la vision
};

#endif // ENEMIGOSENSOR_H
