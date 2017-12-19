#ifndef __IMUNDO_H__
#define __IMUNDO_H__


#include <cstdint>


class GameObject;

class IMundo
{
    public:
    	enum Dir { DLEFT, DRIGHT, DUP, DODOWN};
    	
    	//Sensor(const IMundo* e) : mundo(e) {};
    	//~Sensor() {};

    	//virtual uint8_t				getSize() const = 0;
    	virtual const GameObject* 	getGameObject(uint8_t x, uint8_t y ) const = 0;

    private:
    	
};

#endif // SENSOR_H
