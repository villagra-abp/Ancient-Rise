#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <Enemigo.h>

class IMundo;
class GameObject;

class Sensor
{
    public:
    	enum Dir { DLEFT, DRIGHT, DUP, DODOWN};
    	
    	Sensor(const IMundo* e) : mundo(e) {};
    	~Sensor() {};

    	const GameObject* see(const GameObject* g, Sensor::Dir d) const;

    private:

    	int8_t getDespX(Sensor::Dir d) const;
		int8_t getDespY(Sensor::Dir d) const;
		const GameObject* findFirstGameObject(uint8_t x, uint8_t y, int8_t dx, int8_t dy) const;

    	const IMundo *mundo;
};

#endif // SENSOR_H
