#ifndef ENTORNO_H
#define ENTORNO_H

#include <cstdint>

class GameObject;

class Entorno {
public:
   virtual 	GameObject* getGameObject(uint8_t pos) const = 0;
};

#endif